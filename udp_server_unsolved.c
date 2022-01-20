#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>

#define MYPORT 3490

int main(int argc, char** argv)
{

	int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0)
	{
		perror("socked creation failed");
		exit(1);
	}

	struct sockaddr_in my_addr;
	my_addr.sin_family = PF_INET;
	my_addr.sin_port = htons(MYPORT);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(my_addr.sin_zero), 8);

	if(bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr_in)) < 0)
	{
		perror("bind");
		exit(1);
	}

	char msg[100];


	char *reply = "Message received!";
	int cont = 1;
	while(cont)
	{
		struct sockaddr_in client_addr;
		unsigned int addr_len = sizeof(struct sockaddr);

		//TODO: Use an appropriate system call that waits for the message and puts it into buffer 'reply'. Use documentation at: https://www.man7.org/linux/man-pages/man2/recvfrom.2.html
		recvfrom(sockfd, msg, 100, 0, (struct sockaddr *)&client_addr, &addr_len);
		printf("Message from client: %s\n", msg);

		//TODO: Use an appropriate system call that sends a message from buffer 'msg' back to the client. Use documentation at: https://www.man7.org/linux/man-pages/man2/sendto.2.html
		sendto(sockfd, reply, strlen(reply) + 1, 0, (struct sockaddr *)&client_addr, addr_len);
		if(strncmp(msg, "end", 3) == 0)
		{
			cont = 0;
		}
	}
	close(sockfd);
}
