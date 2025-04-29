#include<bits/stdc++.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <net/ethernet.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
using namespace std;
//nping --tcp --dest-ip 192.168.1.1 --dest-port 80
int main(){
	 
	// int socket(int domain, int type, int protocol);
	// SOCK_RAW        Provides raw network protocol access.
	// AF_PACKET    Low-level packet interface
	// int raw_socket=socket(AF_PACKET,SOCK_RAW,htons(ETH_P_ALL));
	// (send,recv) (write,read)
	int server_fd = socket(AF_INET, SOCK_STREAM,0);
	if (server_fd<0){
		perror("socket creation failed");
		return -1;
	}
    struct sockaddr_in server_addr{},client_addr{};
    socklen_t client_len = sizeof(client_addr);
	socklen_t server_len = sizeof(server_addr);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(6969);
	server_addr.sin_addr.s_addr=INADDR_ANY;

    //connect(server_fd,&addr,sizeof(addr));
	//bind , listen , accept
	if (bind(server_fd,(struct sockaddr*) &server_addr,server_len)<0){
		perror("binding socket failed");
		return -1;
	}
	cout<<"server is listening on port 6969"<<endl;

	if (listen(server_fd,5)<0){
		perror("listening failed");
	}
	


	int client_fd=accept(server_fd,(struct sockaddr*)&client_addr,&client_len);
	if (client_fd<0){
		perror("accept socket failed");
		return -1;
	}
	const char* buffer_to_send="hello from the server";
	int bytes_sent = write(client_fd,buffer_to_send,strlen(buffer_to_send)); 
	//The argument sockfd is the file descriptor of the sending socket.
	if (bytes_sent>0){
		cout<<buffer_to_send<<" is sent !"<<endl; 
	}
	else {
		perror("data was not sent to the client");
		return -1;
	}
	int tot=0;
	char buffer[1024]={};
	while(true){
		int n=read(client_fd,buffer,sizeof(buffer));
		if (n>0){
			tot+=n;
			//cout<<"message was received from the client"<<" "<<buffer<<endl;
			//cout<<"size of the buffer reached to the server is "<<n<<endl;
		}
		else {
			break;
			//cout<<"message was not received from the client"<<endl;
		}
	}

	cout<<"size of the buffer reached to the server is "<<tot<<endl;
	


	//const char *inet_ntop(int af, const void *src,char *dst, socklen_t size);
	char client_ip[INET_ADDRSTRLEN];
	if (inet_ntop(AF_INET,&client_addr.sin_addr,client_ip,INET_ADDRSTRLEN)==NULL){
		perror("inet_ntop");
		return -1;
	}
	cout<<"accepting the client connection"<<endl;
	cout<<"client sin_family "<<client_addr.sin_family <<endl;
    cout<<"client sin_port "<<client_addr.sin_port <<endl;
	cout<<"client sin_addr.s_addr "<<client_addr.sin_addr.s_addr<<endl;
	cout<<client_ip<<endl;

	close(server_fd);

	close(client_fd);


	
	return 0;
}

