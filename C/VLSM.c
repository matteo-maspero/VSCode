#include <stdio.h>
#include <stdlib.h>

//	@brief 8-bit size value.
typedef unsigned char Byte;

//	@brief 32-bit size value.
typedef unsigned int Word, uint;

/*
	@brief Generic subnet's configuration structure.
	@param address The address of the subnet;
	@param gateway The gateway of the subnet;
	@param broadcast The broadcast address of the subnet;
	@param mask The mask of the subnet.
*/
typedef struct {
	Word address;
	Word gateway;
	Word broadcast;
	Word mask;
} Subnet;

/*
	@brief Reads an IP address from the user.
	@param prompt The prompt to print on console;
	@return The read IP address.
*/
Word getIpAddress(const char *prompt);

/*
	@brief Gets the classe of an IP address.
	@param address The IP address to analyze;
	@return Either 'A', 'B', 'C' or 0 if the address is not handled.
*/
char getclasseFromAddress(Word address);

/*
	@brief Reads an array of unsigned integers from the user.
	@param groups The array to fill;
	@param nGroups The number of elements to read.
*/
void inputGroups(uint *groups, uint nGroups);

/*
	@brief Reads an unsigned integer from the user.
	@param prompt The prompt to print on console;
	@return The read unsigned integer.
*/
uint getUnsignedInt(const char *prompt);

/*
	@brief Compares two unsigned integers.
	@param *a Pointer to the first integer;
	@param *b Pointer to the second integer;
	@return Whenever *a is smaller then *b.
*/
int compare(const void *a, const void *b);

/*
	@brief Computes the configuration of the subnets.
	@param subnets The array of subnets to fill;
	@param pool The pool of IP addresses;
	@param classe The classe of the IP addresses;
	@param groups The array of hosts for each subnet;
	@param nGroups The number of subnets.
*/
void computeSubnets(Subnet *subnets, Word pool, uint *groups, uint nGroups);

/*
	@brief Prints an IP address.
	@param address The address to print.
*/
void printAddress(Word address);

/*
	@brief Rounds up a value to the next power of two.
	@param value The value to round up;
	@return The rounded up value.
*/
uint roundUpToPowerOfTwo(uint value);

int main() {
	Word pool;
	uint nGroups;
	char classe;

	//	Get the data that will be analyzed to compute the subnets' configuration.
	pool = getIpAddress("Inserisci l'indirizzo del pool di IP: ");
	nGroups = getUnsignedInt("Inserisci il numero di subnet: ");
	classe = getclasseFromAddress(pool);
	
	uint groups[nGroups];
	inputGroups(groups, nGroups);
	qsort(groups, nGroups, sizeof(uint), compare);

	//	Compute the subnets' configuration.
	Subnet subnets[nGroups];
	computeSubnets(subnets, pool, groups, nGroups);

	//	Print the subnets' configuration.
	for(uint i = 0; i < nGroups; i++) {
		printf("\nSubnet %u:\n", i + 1);
		printf("Indirizzo: ");
		printAddress(subnets[i].address);
		printf("\nGateway: ");
		printAddress(subnets[i].gateway);
		printf("\nBroadcast: ");
		printAddress(subnets[i].broadcast);
		printf("\nMaschera: ");
		printAddress(subnets[i].mask);
		printf("\n");
	}

	printf("\n");
	getchar();
	return 0;
}

Word getIpAddress(const char *prompt) {
	Word address;
	Byte b0, b1, b2, b3;
	char buffer[16];
	printf(prompt);

	while( !scanf("%s", buffer) )
		printf("Indirizzo non valido, riprova: ");

	sscanf(buffer, "%hhu.%hhu.%hhu.%hhu", &b0, &b1, &b2, &b3);
	address = (b0 << 24) + (b1 << 16) + (b2 << 8) + b3;
	return address;
}

char getclasseFromAddress(Word address) {
	//	We only need to analyze the first byte.
	address = address >> 24;

	if(address < 128)
		return 'A';
	if(address < 192)
		return 'B';
	if(address < 224)
		return 'C';
	return 0;
}

void inputGroups(uint *groups, uint nGroups) {
	for(uint i = 0; i < nGroups; i++)
		groups[i] = getUnsignedInt("Inserisci il numero di host per la subnet: ");
}

uint getUnsignedInt(const char *prompt) {
	uint value;
	printf(prompt);

	while( !scanf("%u", &value) )
		printf("Valore non valido, riprova: ");
	
	return value;
}

int compare(const void *a, const void *b) {
	return *(uint*)a < *(uint*)b;
}

void computeSubnets(Subnet *subnets, Word pool, uint *groups, uint nGroups) {
	for(uint i = 0; i < nGroups; i++) {
		subnets[i].address = pool;
		subnets[i].gateway = pool + 1;
		pool = pool + roundUpToPowerOfTwo(groups[i]);
		subnets[i].broadcast = pool - 1;
		subnets[i].mask = 0xFFFFFFFF - (roundUpToPowerOfTwo(groups[i]) - 1);
	}
}

void printAddress(Word address) {
	Byte b0, b1, b2, b3;
	b0 = address >> 24;
	b1 = (address >> 16) & 0xFF;
	b2 = (address >> 8) & 0xFF;
	b3 = address & 0xFF;
	printf("%hhu.%hhu.%hhu.%hhu", b0, b1, b2, b3);
}

uint roundUpToPowerOfTwo(uint value) {
	uint power = 1;

	while(power < value)
		power = power << 1;

	return power;
}