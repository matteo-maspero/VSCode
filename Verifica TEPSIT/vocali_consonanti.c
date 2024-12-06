#include <stdio.h>
#include <string.h>
#define LENGTH 64

int main() {
	char string[LENGTH];
	printf("Inserisci una stringa (max %d caratteri): ", LENGTH);
	fgets(string, LENGTH, stdin);
	strlwr(string);

	int vocali = 0;
	int consonanti = 0;

	for (int i = 0; string[i] != '\0'; i ++) {
		if(string[i] < 'a' || string[i] > 'z')
			continue;

		switch(string[i]) {
			case 'a': case 'e': case 'i': case 'o': case 'u':
				vocali ++;
				break;
			default:
				consonanti ++;
				break;
		}
	}

	printf(
		"Vocali: %d\n"
		"Consonanti: %d\n",
		vocali, consonanti
	);

	return 0;
}