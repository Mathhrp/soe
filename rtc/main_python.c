#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <strings.h>
#include <arpa/inet.h>
#include <stdio_ext.h>
#include <pthread.h>

#define BUF 1000
#define PORTACLIENT 9998
#define PORTASRV 9999
#define STOP_INPUT "SAIR"

int main(int argc, char *argv[])
{
	int meusocket, numbytes, operacao, cont = 0;
	struct sockaddr_in local_addr;
	struct sockaddr_in server_addr;
	socklen_t addr_size;
	char entradas[BUF], aux[BUF];
	char ip[] = "127.0.0.1";

	// Estrutura de Rede - Client
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(PORTACLIENT);
	local_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(local_addr.sin_zero),8);

	// Ligacao da camada de Aplicacao com a camada de Rede
	meusocket = socket(AF_INET, SOCK_DGRAM, 0);
	bind(meusocket, (struct sockaddr *) &local_addr, sizeof( struct sockaddr));

	//Envia mensagem
	//printf("Digite o IP do Servidor Python \n");
	//scanf("%s", ip);

	// Estrutura de Rede - Server
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORTASRV);
	server_addr.sin_addr.s_addr = inet_addr(ip);
	bzero(&(server_addr.sin_zero), 8);

	while (1) {

		// Aqui vi o código do RTC
  
  	numbytes = sendto(meusocket, entradas, sizeof(entradas), 0, (struct sockaddr *) &server_addr, sizeof(struct sockaddr));
  	printf("enviado %d bytes para %s, com a msg: %s \n", numbytes, inet_ntoa(server_addr.sin_addr), entradas);
  }

	close(meusocket);
	exit(EXIT_SUCCESS);
}