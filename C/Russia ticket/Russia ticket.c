#include <stdio.h>

int main() {
    unsigned int x;

    // Prendiamo in input un numero a 6 cifre.
    do {
        printf("Inserire un numero a 6 cifre: ");
        scanf("%u", &x);
    } while (x < 100000 || x > 999999);

    // Dividiamo il numero in 2 metà.
    int a = x / 1000;
    int b = x % 1000;

    // Calcoliamo la somma delle cifre di ciascuna metà.
    int sum_a = a / 100 + a / 10 % 10 + a % 10;
    int sum_b = b / 100 + b / 10 % 10 + b % 10;

    // Controllo e stampa.
    if (sum_a == sum_b)
        printf(
            "%d, %d, %d | %d, %d, %d -> %d\n",
            a / 100, a / 10 % 10, a % 10,
            b / 100, b / 10 % 10, b % 10,
            sum_a
        );
    else
        printf("Non sei fortunato\n");

    return 0;
}