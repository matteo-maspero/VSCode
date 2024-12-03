#include <iostream>
using namespace std;

int main() {
	int somma = 0;

	while(1) {
		int n;
		cout << "Inserisci un numero (n < 0 per terminare): ";
		cin >> n;

		if(n < 0)
			break;

		somma += n;
	}

	cout << "La somma dei numeri inseriti vale: " << somma;
	return 0;
}