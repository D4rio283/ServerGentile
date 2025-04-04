//CODICE CLIENT 
#include <arpa/inet.h> 
#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h> 

#define PORT 5700 

int main(int argc, char const* argv[]) 
{     
	int status, valread, client_fd;     
	struct sockaddr_in serv_addr;     
	char* ciao = "Buongiorno dal client!";     
	char buffer[1024] = { 0 };     
	

	if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {         
		printf("\n Errore nella creazione della socket!! \n");         
		return -1;     
	}     
	

	serv_addr.sin_family = AF_INET;     
	serv_addr.sin_port = htons(PORT);     
	

	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {         
		printf("\nIndirizzo non valido/ indirizzo non supportato \n");         
		return -1;     
	}     
	
	if ((status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {         
		printf("\nConnessione fallita \n");         
		return -1;     
	}     
	
	send(client_fd, ciao, strlen(ciao), 0);     
	printf("Messaggio di saluto inviato\n");     
	valread = read(client_fd, buffer, 1024 - 1);      
	printf("%s\n", buffer);     
	
	close(client_fd);     
	return 0; 
}
