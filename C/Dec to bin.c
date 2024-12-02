#include <stdio.h>

int main() {
    // Il nostro intero positivo rappresentato su 8 bit.
    unsigned char x;

    //  Prendiamo x in input specificandone il formato %hhu (non %c) in modo da
    //  assegnargli il valore desiderato invece che il suo corrispettivo in ascii.
    printf("Inserire un numero: [0; 255] ");
    scanf("%hhu", &x);

    //  Ora, per ogni cifra k, dobbiamo calcolare l'AND bit a bit tra x e una maschera
    //  che abbia tutti i bit a 0 tranne il suo k-esimo (che vale 1). Bisogna poi
    //  shiftare il risultato di k posizioni a destra per ottenere il valore desiderato.
    printf(
        "Il numero in binario e': %d%d%d%d%d%d%d%d",
        (x & 0b10000000) >> 7,
        (x & 0b1000000) >> 6,
        (x & 0b100000) >> 5,
        (x & 0b10000) >> 4,
        (x & 0b1000) >> 3,
        (x & 0b100) >> 2,
        (x & 0b10) >> 1,
        (x & 0b1)
    );
}