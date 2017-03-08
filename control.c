#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc,char* argv[]){
	char buf=0;
	int tmp;
	int fd;
	struct sockaddr_in addr;
	int sock=socket(PF_INET,SOCK_STREAM,0);
	if(sock==-1){
		printf("socket error!\n");
	}
	int flag=1;
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&flag,sizeof(flag));
	addr.sin_family=PF_INET;
	addr.sin_addr.s_addr=inet_addr(argv[1]);
	addr.sin_port=htons(atoi(argv[2]));

	if(bind(sock,(struct sockaddr*)&addr,sizeof(addr))!=-1){
		printf("bind ok\n");
	}

	if(listen(sock,10)!=-1){
		printf("listen ok\n");
	}

	int connect_fd=accept(sock,NULL,NULL);
	if(connect_fd<0){
		printf("connect_fd fail\n");
	}
	printf("user connect：%d\n",connect_fd);
	fd=open("dev/baodev",O_RDWR);
	if(-1==fd){
		perror("open error\n"),exit(-1);
	}
	printf("open ok!\n");

	while(1){
		tmp=read(connect_fd,&buf,1);
		
		if(tmp!=0){
			printf("read ok!\n");
			write(fd,&buf,1);
		
		}
	}
	return 0;

}
