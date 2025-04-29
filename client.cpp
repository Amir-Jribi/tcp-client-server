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
	int client_fd = socket(AF_INET, SOCK_STREAM,0);
	if (client_fd<0){
		perror("socket creation failed");
		return -1;
	}
    struct sockaddr_in server_addr{};
    socklen_t server_len = sizeof(server_addr);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(6969);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1"); //10.43.22.55 
    
    if (connect(client_fd,(struct sockaddr*)&server_addr,server_len)<0){
        perror("failing in connection");
        return -1;
    }
    char buf[1024]={};
    int from_server=read(client_fd,buf,sizeof(buf));
    if (from_server>0){
        cout<<"data is reached the client"<<endl;
    }
    else {
        perror("data was not reached to the client");
        return -1;
    }

    char buffer[1024]={};
    for(int j=0;j<1024;j++){
        buffer[j]='a';
    }
    int send_bytes=0;
    for(int i=0;i<1000;i++){
        int n=write(client_fd,buffer,strlen(buffer));
        if (n<0){
            perror("error in sending a message");
            return -1;
        }
        else {
            send_bytes+=n;
            continue;
        }
    }
    cout<<"number of bytes that was sent from the client is "<<send_bytes<<endl;

    

    /*
    const char* buffer="hello world";
    int n=send(client_fd,buffer,strlen(buffer),0);
    if (n<0){
        perror("error in sending a message");
        return -1;
    }
    else {
        cout<<"number of bytes that was sent from the client is "<<n<<endl;
    }
    */
	close(client_fd);
	return 0;
}

