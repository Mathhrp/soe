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

int main()
{
	int file;
	char *filename = "/dev/i2c-1"; /*barramento que será utilizado*/
	int addr = 0x68; /*endereço do dispositivo*/
	char rtc_data[8]; /*buffer para acessar os dados*/

	if ((file = open(filename, O_RDWR)) < 0) {
	    /*não foi possível acessar o arquivo*/
	}

	if (ioctl(file, I2C_SLAVE, addr) < 0) {
		/*não foi possível acessar o dispositivo*/
	}
	/*Exemplo: Configurando o RTC para 18/05/2017 21:20:00*/

	rtc_data[0] = 0; //a escrita ocorrerá a partir do endereço 0
	rtc_data[1] = 0x00; //seconds
	rtc_data[2] = 0x20; //minutes
	rtc_data[3] = 0x19; //hours
	rtc_data[4] = 0x05; //day
	rtc_data[5] = 0x18; //date
	rtc_data[6] = 0x05; //month
	rtc_data[7] = 0x17; //year

	for(int i =0;i<8;i++)
	{
		printf("valor rtc : %c",rtc_data[7-i]);
	}
	if (write(file,rtc_data,8) != 8) {
		/*A operação não foi realizada com sucesso*/
	}

	close(file);

	return 0;
}
