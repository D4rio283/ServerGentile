//CODICE SERVER
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 5700

int main(int argc, char const* argv[])
{
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	char* risposta = "Buongiorno dal server!";
	
	// Creazione della socket del server
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Errore nella creazione della socket");
		exit(EXIT_FAILURE);
	}
	
	/*Opzioni della socket
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	*/
	
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	
	// Binding della socket all'indirizzo e porta specificati
	if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
		perror("Binding fallito");
		exit(EXIT_FAILURE);
	}
	
	// Server in ascolto
	if (listen(server_fd, 3) < 0) {
		perror("Listen");
		exit(EXIT_FAILURE);
	}
	
	printf("Server in ascolto sulla porta %d...\n", PORT);
	
	// Accettazione della connessione in arrivo
	if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
		perror("Accept");
		exit(EXIT_FAILURE);
	}
	
	// Lettura del messaggio dal client
	valread = read(new_socket, buffer, 1024);
	printf("Messaggio ricevuto dal client: %s\n", buffer);
	
	// Invio della risposta al client
	send(new_socket, risposta, strlen(risposta), 0);
	printf("Risposta inviata al client\n");
	
	// Chiusura del socket
	close(new_socket);
	close(server_fd);
	return 0;
}
