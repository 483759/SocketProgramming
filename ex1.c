#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	int fd1, fd2, sd1, sd2;
	printf("getdtablesize() = %d\n", getdtablesize());

	fd1 = open("/etc/passwd", O_RDONLY, 0);
	printf("/etc/passwd's file descriptor = %d\n",fd1);

	sd1 = socket(AF_INET, SOCK_STREAM, 0);
	printf("stream socket descriptor = %d\n", sd1);

	sd2 = socket(AF_INET, SOCK_DGRAM, 0);
	printf("datagram socket descriptor = %d\n", sd2);

	fd2 = open("/etc/hosts", O_RDONLY, 0);
	printf("/etc/hosts's file descriptor = %d\n", fd2);

	close(fd2);
	close(fd1);
	close(sd2);
	close(sd1);

	return 0;
}
