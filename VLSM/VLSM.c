#include <stdio.h>
#include <stdlib.h>

//	@brief Must be a constant string and at least "2".
#define MAX_SUBNETS "128"

//	@brief Sequence of 8 bits.
typedef unsigned char Byte;

//	@brief Sequence of 32 bits.
typedef unsigned int Word, uint;

typedef struct {
	Word address;
	Word mask;
	Word gateway;
	Word firstHost;
	Word broadcast;
	Word lastHost;
} Subnet;

//	Input handlers.

Word inputAddress(const char *prompt);
uint inputUInt(const char *prompt, uint min, uint max);
void inputSizes(uint *sizes, uint count);

//	Weird conversions Byte-Word.

Word bytesToWord(Byte *bytes);
Byte *wordToBytes(Word word);

//	Utils.

char getClassFromAddress(Word address);
Word getMaskFromClass(char ipClass);
int compareForQSort(const void *a, const void *b);
void computeSubnets(Subnet *subnets, uint *sizes, uint count, Word poolAddress);
uint ceilXToPowerOf2(uint x);

//	Functions to increment/decrement the given address.

Word addToAddress(Word address, uint value);
Word subtractFromAddress(Word address, uint value);

int main() {
	Word poolAddress;
	char poolClass;
	Word poolMask;
	uint subnetCount;

	poolAddress = inputAddress("Inserisci l'indirizzo di rete della pool: ");
	poolClass = getClassFromAddress(poolAddress);
	poolMask = getMaskFromClass(poolClass);

	subnetCount = inputUInt("Inserisci il numero di subnet: (2, "MAX_SUBNETS") ", 2, atoi(MAX_SUBNETS));
	uint sizes[subnetCount];
	inputSizes(sizes, subnetCount);
	
	Subnet subnets[subnetCount];
	computeSubnets(subnets, sizes, subnetCount, poolAddress);

	return 0;
}

//	Input handlers.

Word inputAddress(const char *prompt) {
	Byte bytes[4];
	printf(prompt);
	/*
		Why Fill Backwards?
		The reason for filling the array backwards is due to the way memory is interpreted.
		In a little-endian system (which is common in many architectures), the least
		significant byte is stored at the lowest memory address. By filling the array
		backwards, the bytes are placed in the correct order for the Word type when the
		memory is reinterpreted.
	*/
	while(scanf("%hhu.%hhu.%hhu.%hhu", bytes + 3, bytes + 2, bytes + 1, bytes) != 4) {
		printf("Input non valido, riprova: ");
		while(getchar() != '\n');
	}

	return bytesToWord(bytes);
}

uint inputUInt(const char *prompt, uint min, uint max) {
	uint result;
	printf(prompt);

	while(!scanf("%u", &result) || min < max && (result < min || result > max))
		printf("Input non valido, riprova: ");

	return result;
}

void inputSizes(uint *sizes, uint count) {
	uint i;

	for(i = 0; i < count; ++i) {
		printf("Sottorete %u:\n", i + 1);
		//	Another bit hack, unsigned int -1 expands to the maximum value on 32 bits (which we can assume as INF).
		sizes[i] = ceilXToPowerOf2(inputUInt("\tDimensione: ", 1, -1));
	}
	//	We need to sort the subnets in descending order.
	qsort(sizes, count, sizeof(uint), compareForQSort);
}

//	Weird conversions Byte-Word.

Word bytesToWord(Byte *bytes) {
	//	Evil bit/memory hack.
	return *((Word*) bytes);
}

Byte *wordToBytes(Word word) {
	Byte *bytes = (Byte*) malloc(4 * sizeof(Byte));
	//	Another evil bit/memory hack.
	*bytes = *((Byte*) &word);
	return bytes;
}

//	Utils.

char getClassFromAddress(Word address) {
	//	We only need to check the first 8 bits.
	address = address >> 24;

	if(address < 128)
		return 'A';
	if(address < 192)
		return 'B';
	if(address < 224)
		return 'C';

	printf("Errore: le classi D ed E non sono supportate.\n");
	exit(1);
}

Word getMaskFromClass(char ipClass) {
	if(ipClass == 'A')
		return 0xFF000000;
	if(ipClass == 'B')
		return 0xFFFF0000;
	//	We don't need to check anymore, since the only possible value is now 'C'.
	return 0xFFFFFF00;
}

//	Comapre callback for qsort.
int compareForQSort(const void *a, const void *b) {
	return *(uint*) a < *(uint*) b;
}

void computeSubnets(Subnet *subnets, uint *sizes, uint count, Word poolAddress) {
	uint i;
	Word address = poolAddress;

	for(i = 0; i < count; ++i) {
		subnets[i].address = address;
		subnets[i].mask = ~(sizes[i] - 1);
		subnets[i].gateway = addToAddress(address, 1);
		subnets[i].firstHost = addToAddress(address, 2);
		//	Add the size of the subnet here to easily compute the next addresses.
		address = addToAddress(address, sizes[i]);
		subnets[i].broadcast = subtractFromAddress(address, 1);
		subnets[i].lastHost = subtractFromAddress(address, 2);
	}
}

uint ceilXToPowerOf2(uint x) {
	uint pow = 1;

	while(pow < x + 2)
		pow = pow << 1;

	return pow;
}

//	Functions to increment/decrement the given address.

Word addToAddress(Word address, uint value) {
	if(address + value < address) {
		printf("Errore: l'aggiunta ha causato overflow.\n");
		exit(1);
	}

	return address + value;
}

Word subtractFromAddress(Word address, uint value) {
	if(address - value > address) {
		printf("Errore: la sottrazione ha causato underflow.\n");
		exit(1);
	}

	return address - value;
}