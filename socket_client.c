#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>

#define CLIENT_IP "127.0.0.1"
#define CLIENT_PORT 5000

int main(){
	int client_socket;
	struct sockaddr_in server_address;
	unsigned char Buff[250];
	int check;

	client_socket = socket(PF_INET, SOCK_STREAM, 0);
	//클라이언트 소켓 생성
	
	if(client_socket==-1){
		printf("Client Socket ERROR");
		exit(0);
	}
	bzero((char*)&server_address, sizeof(server_address));

	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(CLIENT_PORT);
	server_address.sin_addr.s_addr = inet_addr(CLIENT_IP);
	//family -> 소켓 생성시 지정한 프로토콜에 맞춰줌
	//port -> 클라이언트 포트번호
	//addr -> IP주소 저장

	if(connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address))==-1){
	//서버와 연결 설정을 위한 connect 호출
		printf("Connect ERROR");
		exit(0);
	}

	printf("\nclient socket=[%d]\n\n", client_socket);

	while(1){
		check=read(client_socket, Buff, sizeof(Buff));
		if(client_socket==-1){	//서버쪽에서 연결이 중지 될 때
			printf("Disconnection Check\n");
			close(client_socket);
			break;
		}
		Buff[sizeof(Buff)]='\0';
		printf(">> %s\n", Buff);
	}
	close(client_socket);

	return 0;
}
