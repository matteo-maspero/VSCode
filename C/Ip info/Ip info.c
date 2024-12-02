#include <stdio.h>

void getIp(unsigned char *ip);
void printIp(unsigned char *ip);

char getClass(unsigned char *ip);

int main() {
	unsigned char ip[4];
	unsigned char broadcast[4];

	//	Input dell'indirizzo IP.
	printf("Inserire l'indirizzo IP: ");
	getIp(ip);

	//	Identificazione della classe dell'indirizzo IP e del
	//	numero di byte a 255 della maschera.
	char ipClass = getClass(ip);
	int mask = (ipClass - 'A' + 1);

	//	Estraiamo l'indirizzo di rete dall'IP inserito.
	for(int i = mask; i < 4; i ++)
		ip[i] = 0;

	int netsNumber = (1 << (mask * 8));
	int hostsNumber = (1 << ((4 - mask) * 8)) - 2;

	//	Calcoliamo l'indirizzo di broadcast.
	for(int i = 0; i < 4; i ++)
		if(i < mask)
			broadcast[i] = ip[i];
		else
			broadcast[i] = 255;

	//	Output delle informazioni.
	printf("\nIndirizzo di rete (classe %c): ", ipClass);
	printIp(ip);
	printf("\nIndirizzo di broadcast: ");
	printIp(broadcast);
	printf(
		"\nNumero di reti disponibili: %d"
		"\nNumero di host assegnabili: %d",
		netsNumber, hostsNumber
	);

	return 0;
}

//	Input dell'indirizzo IP.
void getIp(unsigned char *ip) {
	scanf("%hhu.%hhu.%hhu.%hhu", ip, ip + 1, ip + 2, ip + 3);
}

//	Stampa l'indirizzo IP.
void printIp(unsigned char *ip) {
	printf("%hhu.%hhu.%hhu.%hhu", ip[0], ip[1], ip[2], ip[3]);
}

//	Restituisce la classe dell'indirizzo IP in base al suo primo byte.
char getClass(unsigned char *ip) {
	if(*ip < 128)
		return 'A';

	if(*ip < 192)
		return 'B';

	if(*ip < 224)
		return 'C';

	if(*ip < 240)
		return 'D';
	
	return 'E';
}