#include <stdio.h>

/**
	@brief Legge e restituisce un intero da stdin. Permette di specificare un intervallo di valori validi (min > max per saltare).
	@param prompt Messaggio di richiesta da stampare a video.
	@param min Valore minimo accettato.
	@param max Valore massimo accettato.
	@return L'intero letto da stdin.
*/
int readInt(const char* prompt, int min, int max);

int main() {
	int a, b;

	a = readInt("Inserisci il primo numero: ", 1, 0);
	b = readInt("Inserisci il secondo numero: ", 1, 0);
	printf("La somma dei due numeri è: %d\n", a + b);

	return 0;
}

int readInt(const char* prompt, int min, int max) {
	int dest;
	printf(prompt);

	while(1) {
		if(scanf("%d", &dest) != 1) {
			printf("L'input non è valido. Riprova: ");
			while(getchar() != '\n');
			continue;
		}

		if(min > max)
			return dest;

		if(dest > min && dest < max)
			return dest;

		printf("L'input deve essere compreso tra %d e %d. Riprova: ", min, max);
	}

	return dest;
}