#include<iostream>
#include <cstring>
#include <unistd.h>
#include <vector>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <net/ethernet.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <poll.h>

using namespace std;
//nping --tcp --dest-ip 192.168.1.1 --dest-port 80
void clientDetails(struct sockaddr_in client_addr){
	char client_ip[INET_ADDRSTRLEN];
	if (inet_ntop(AF_INET,&client_addr.sin_addr,client_ip,INET_ADDRSTRLEN)==NULL){
		perror("inet_ntop");
		return;
	}
	cout<<"Client Details"<<endl;
	cout<<"client sin_family "<<client_addr.sin_family <<endl;
    cout<<"client sin_port "<<client_addr.sin_port <<endl;
	cout<<"client sin_addr.s_addr "<<client_addr.sin_addr.s_addr<<endl;
	cout<<client_ip<<endl;
	return;
}
int main(){
	int server_fd = socket(AF_INET, SOCK_STREAM,0);
	if (server_fd<0){
		perror("socket creation failed");
		return -1;
	}
    struct sockaddr_in server_addr{};
	socklen_t server_len = sizeof(server_addr);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(6969);
	server_addr.sin_addr.s_addr=INADDR_ANY;

	if (bind(server_fd,(struct sockaddr*) &server_addr,server_len)<0){
		perror("binding socket failed");
		return -1;
	}
	cout<<"server is listening on port 6969"<<endl;

	if (listen(server_fd,5)<0){
		perror("listening failed");
	}

    vector<struct pollfd> fds;

    fds.push_back({server_fd,POLLIN,0});

    cout<<"events to look for "<<fds[0].events<<endl;
    cout<<"events returned "<<fds[0].revents<<endl; 

    while(true){
        int num_desc=poll(fds.data(),size(fds),100000);
        if (num_desc<0){
            perror("poll error");
            return 0;
        }
        for(int i=0;i<size(fds);i++){
            if (fds[i].revents & POLLIN){
                if (fds[i].fd==server_fd){
                    cout<<"server file descriptor\n";
                    struct sockaddr_in client_addr{};
	                socklen_t client_len = sizeof(server_addr);
                    int client_fd=accept(server_fd,(struct sockaddr*)&client_addr,&client_len);
	                if (client_fd<0){
		                perror("accept socket failed");
		                break;
	                }
                    fds.push_back({client_fd,POLLIN,0});
                }
                else {
                    // data that has been sent from the client.
                    cout<<"client file descriptor\n";  
                    int tot=0;
                    char buffer[1024]={};
                    while(true){
                        int n=read(fds[i].fd,buffer,sizeof(buffer));
                        if (n>0){
                            tot+=n;
                        }
                        else if (n==0){
                            cout<<"client have completed sending data"<<endl;
                            fds[i].revents=0;
                            close(fds[i].fd);
                            fds.erase(fds.begin()+i);
                            i--;
                            break;
                        }
                        else if (n<0){
                            perror("error in reading data from client");
                            break;
                        }
                    }
                    cout<<"size of the buffer reached to the server is "<<tot<<endl;             
                }
            }
        }
        cout<<"number of descriptors that their events they are waiting for have occured "<<num_desc<<endl;
    }

    

	
    /*
	
	const char* buffer_to_send="hello from the server";
	int bytes_sent = write(client_fd,buffer_to_send,strlen(buffer_to_send)); 
	if (bytes_sent>0){
		cout<<buffer_to_send<<" is sent !"<<endl; 
	}
	else {
		perror("data was not sent to the client");
		return -1;
	}
	clientDetails(client_addr);

    */
	close(server_fd);	
	return 0;
}

