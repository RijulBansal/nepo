#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<sys/socket.h>
int main()
{
	int sock,len;
	char str1[100],str2[100];
	struct sockaddr_in serv;
	bzero(str1,100);
	bzero(str2,100);
	bzero(&serv,sizeof(serv));
	sock=socket(AF_INET,SOCK_DGRAM,0);
	serv.sin_family=AF_INET;
	serv.sin_port=htons(12348);
	serv.sin_addr.s_addr=INADDR_ANY;
	len=sizeof(serv);
	int reuse=1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,(char *)&reuse, sizeof(reuse));
	bind(sock, (struct sockaddr *)&serv, sizeof(serv));
	while(1)
	{
	//fgets(str2,100,stdin);
	//sendto(sock,str2,strlen(str1),0,(struct sockaddr *)&serv,len);
	recvfrom(sock,str2,100,0,(struct sockaddr *)&serv,&len);
	printf("Received data is: %s",str2);
	bzero(str2,100);
	}
	close(sock);	
}