#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MYPORT 3490

int main(int argc, char** argv)
{
	//TODO: Use a symbolic constant to create a UDP socket for parameter 'type' of system call socket. Use 'man 2 socket' to learn the appropriate constant.
	int sockfd = socket(PF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(MYPORT);

	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) < 0)
	{
		printf("\n inet_pton error occured\n");
		return 1;
	}

	char reply[100];
	char msg[100];
	int cont = 1;
	do
	{
		printf("Enter message to send to client: \n");
		fgets(reply, 100, stdin);
		if(strncmp(reply, "end", 3) == 0)
		{
			cont = 0;
		}
		//TODO: Use an appropriate system call that sends a message from buffer 'msg' back to the client. Use documentation at: https://www.man7.org/linux/man-pages/man2/sendto.2.html
		sendto(sockfd, reply, strlen(reply) + 1, 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
		unsigned int addr_len = sizeof(struct sockaddr);

		//TODO: Use an appropriate system call that waits for the message and puts it into buffer 'reply'. Use documentation at: https://www.man7.org/linux/man-pages/man2/recvfrom.2.html
		recvfrom(sockfd, msg, 100, 0, (struct sockaddr *)&serv_addr, &addr_len);
		printf("Message from server: %s\n", msg);
	} while(cont);

	close(sockfd);

}
