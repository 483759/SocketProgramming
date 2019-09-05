#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <errno.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5000
#define MAX_SEND_SIZE 100

int main(){
	int server_socket;
	unsigned int size;

	int toClient;
	char message[15];
	struct sockaddr_in server_address;
	struct sockaddr_in Client;

	server_socket=socket(PF_INET, SOCK_STREAM, 0);
	//서버 소켓 생성(인터넷 프로토콜, TCP사용)

	if(server_socket==-1){	//소켓 생성 실패시
		printf("Cannot Create Socket\n");
		exit(0);
	}

	memset(&server_address, 0x00, sizeof(server_address));
	server_address.sin_family=AF_INET;
	server_address.sin_port=htons(SERVER_PORT);
	server_address.sin_addr.s_addr=inet_addr(SERVER_IP);
	//family -> 소켓 생성시 지정한 프로토콜에 맞춰줌
	//port -> 서버 포트번호
	//addr -> IP주소 저장

	if(bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address))==-1){
	//생성한 소켓과 자신의 소켓 주소 바인딩
		printf("bind() ERROR\n");
		exit(0);
	}

	if(listen(server_socket, 3)==-1){
	//listen을 이용하여 수동 대기모드 진입
		printf("listen() ERROR");
		exit(0);
	}

	size = sizeof(server_address);
	toClient=accept(server_socket, (struct sockaddr*)&Client, &size);
	//클라이언트와 연결 설정 성공시 소켓 반환

	if(toClient<0){
		printf("accept ERROR");
	}

	printf("\nserver_socket=[%d]\n\n", server_socket);
	printf("\nclient_socket=[%d]\n\n", toClient);
	//소켓번호 출력

	while(1){
		//클라이언트와 에코 통신
		printf(">>");
		fgets(message, MAX_SEND_SIZE, stdin);
		if(message[0]=='q'){
			close(server_socket);
			close(toClient);
			break;
		}
		message[sizeof(message)]='\0';
		write(toClient, message, sizeof(message));
	}
	close(server_socket);
	close(toClient);
	//소켓 연결 해제

	return 0;
}
