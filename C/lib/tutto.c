#include <stdlib.h>
#include <stdio.h>

typedef int DATO;

typedef struct s_nodo
{
    DATO dato;
    struct s_nodo *next;
} NODO;

typedef NODO *LISTA;

/*
***********************************************************************
                                    INSERIMENTI
***********************************************************************
*/

LISTA insInTesta(LISTA l, DATO dato);           // Inserisce un nodo all'inizio della lista.
LISTA insInMezzo(LISTA l, DATO dato, int idx);  // Inserisce un nodo alla posizione specificata.
LISTA insInCoda(LISTA l, DATO dato);            // Inserisce un nodo alla fine della lista.
LISTA insOrdinato(LISTA l, DATO dato, int dir); // Inserisce un nodo in modo ordinato.

/*
***********************************************************************
                                    RIMOZIONI
***********************************************************************
*/

LISTA rimuoviInTesta(LISTA l);          // Rimuove il nodo in testa alla lista.
LISTA rimuoviInMezzo(LISTA l, int idx); // Rimuove un nodo dalla posizione specificata.
LISTA rimuoviInCoda(LISTA l);           // Rimuove l'ultimo nodo della lista.
LISTA rimuoviSeDato(LISTA l, DATO d);   // Rimuove il nodo contenente un dato specifico.

/*
***********************************************************************
                                    UTILITIES
***********************************************************************
*/

void stampa(LISTA l);                   // Stampa tutti i nodi della lista.
int ComparaListe(LISTA l1, LISTA l2);   // Confronta due liste.
int trova(LISTA l, DATO dato, int dir); // Trova l'indice del primo nodo maggiore/minore del dato.
LISTA riempiOrd(LISTA l);               // Riempie la lista con valori in ordine crescente.
LISTA riempiACaso(LISTA l);             // Riempie la lista con valori casuali.
LISTA inverti(LISTA l);                 // Inverte la lista.
LISTA concatena(LISTA l1, LISTA l2);    // Concatena due liste.

/*
***********************************************************************
                                    ORDINAMENTO
***********************************************************************
*/

LISTA ordinaCresc(LISTA l); // Ordina la lista in ordine crescente.
LISTA ordinaDecr(LISTA l);  // Ordina la lista in ordine decrescente.

/*
***********************************************************************
                                    MANIPOLAZIONE
***********************************************************************
*/

LISTA rimuoviDuplicati(LISTA l);                       // Rimuove i nodi duplicati dalla lista.
LISTA sottolista(LISTA l, int inizio, int fine);       // Crea una sottolista.
NODO *trovaCentro(LISTA l);                            // Trova il nodo centrale della lista.
int Lunghezza(LISTA l);                                // Restituisce la lunghezza della lista.
void liberaLista(LISTA l);                             // Libera la memoria di tutti i nodi della lista.
LISTA ruotaDestra(LISTA l, int k);                     // Ruota la lista di k posizioni a destra.
LISTA ruotaSinistra(LISTA l, int k);                   // Ruota la lista di k posizioni a sinistra.
LISTA duplicaLista(LISTA l);                           // Crea una copia della lista.
LISTA mergeListeOrdinato(LISTA l1, LISTA l2, int dir); // Unisce due liste ordinate.
LISTA swapNodi(LISTA l, int idx1, int idx2);           // Scambia i nodi a due indici specificati.
/*
***********************
*******************************************************************************************************
                                        INSERIMENTI
*******************************************************************************************************
***********************
*/

/**
 * @brief Inserisce un nuovo nodo in testa alla lista.
 *
 * Questa funzione crea un nuovo nodo, lo inizializza con il dato fornito
 * e lo inserisce all'inizio della lista collegata.
 *
 * @param l La lista a cui aggiungere il nuovo nodo.
 * @param dato Il dato da inserire nel nuovo nodo.
 * @return La nuova lista con il nodo aggiunto in testa.
 */
LISTA insInTesta(LISTA l, DATO dato)
{
    LISTA tmp = (LISTA)malloc(sizeof(NODO));
    tmp->dato = dato;
    tmp->next = l;
    return tmp;
}

/**
 * @brief Inserisce un nuovo nodo in una lista collegata in una posizione specifica.
 *
 * Questa funzione inserisce un nuovo nodo contenente il dato specificato
 * nella posizione indicata dall'indice nella lista collegata.
 * Se la lista è vuota o l'indice è 1, il nuovo nodo viene inserito in testa.
 *
 * @param l La lista collegata in cui inserire il nuovo nodo.
 * @param dato Il dato da inserire nel nuovo nodo.
 * @param idx La posizione (indice) in cui inserire il nuovo nodo (1-based).
 * @return La lista collegata aggiornata con il nuovo nodo inserito.
 */
LISTA insInMezzo(LISTA l, DATO dato, int idx)
{
    if (l == NULL || idx == 1)
    {
        // Se la lista è vuota o l'indice è 1, inserisci in testa
        return insInTesta(l, dato);
    }

    LISTA puntatemp = l;
    LISTA tmp = (LISTA)malloc(sizeof(NODO));
    tmp->dato = dato;

    // Trova la posizione giusta per inserire l'elemento
    int c = 1;
    while (puntatemp->next != NULL && c < idx - 1)
    {
        puntatemp = puntatemp->next;
        ++c;
    }

    // Inserisci l'elemento in mezzo
    tmp->next = puntatemp->next;
    puntatemp->next = tmp;

    return l;
}

/**
 * @brief Inserisce un nuovo nodo in coda alla lista.
 *
 * Questa funzione prende una lista esistente e un dato, e inserisce un nuovo nodo contenente il dato
 * alla fine della lista. Se la lista è vuota (NULL), la funzione chiama `insInTesta` per inserire il
 * nodo come primo elemento della lista.
 *
 * @param l La lista a cui aggiungere il nuovo nodo.
 * @param dato Il dato da inserire nel nuovo nodo.
 * @return La lista aggiornata con il nuovo nodo in coda.
 */
LISTA insInCoda(LISTA l, DATO dato)
{
    if (l == NULL)
    {
        return insInTesta(l, dato);
    }

    LISTA puntatemp = l;
    LISTA tmp = (LISTA)malloc(sizeof(NODO));
    tmp->dato = dato;
    tmp->next = NULL;

    while (puntatemp->next != NULL)
    {
        puntatemp = puntatemp->next;
    }
    puntatemp->next = tmp;
    return l;
}
/**
 * @brief Inserisce un elemento in una lista ordinata.
 *
 * La funzione `insOrdinato` inserisce un nuovo elemento nella lista `l` mantenendo l'ordine specificato.
 *
 * @param l La lista in cui inserire l'elemento.
 * @param dato Il valore del nuovo elemento da inserire.
 * @param dir La direzione dell'ordinamento: 1 per ordine crescente, 0 per ordine decrescente.
 *
 * @return La lista con il nuovo elemento inserito.
 *
 * La funzione utilizza `insInTesta` per inserire l'elemento in testa alla lista se la lista è vuota
 * o se l'elemento deve essere inserito in testa per mantenere l'ordine. Altrimenti, attraversa la lista
 * per trovare la posizione corretta e inserisce l'elemento in quella posizione.
 */
LISTA insOrdinato(LISTA l, DATO dato, int dir)
{
    if (l == NULL || (dir == 1 && l->dato >= dato) || (dir == 0 && l->dato <= dato))
    {
        return insInTesta(l, dato);
    }

    LISTA pointer = l;

    // Attraversa la lista e trova la posizione giusta
    if (dir == 1)
    { // Ordine crescente
        while (pointer->next != NULL && pointer->next->dato < dato)
        {
            pointer = pointer->next;
        }
    }
    else
    { // Ordine decrescente
        while (pointer->next != NULL && pointer->next->dato > dato)
        {
            pointer = pointer->next;
        }
    }

    // Inserisci dopo il puntatore
    pointer->next = insInTesta(pointer->next, dato);

    return l;
}

/*
***********************
*******************************************************************************************************
                                        RIMOZIONI
*******************************************************************************************************
***********************
*/

/**
 * @brief Rimuove il nodo in testa alla lista.
 *
 * Questa funzione rimuove il primo nodo della lista collegata e ritorna
 * la nuova testa della lista. Se la lista è vuota, ritorna NULL.
 *
 * @param l Puntatore alla testa della lista.
 * @return LISTA Puntatore alla nuova testa della lista, o NULL se la lista era vuota.
 */
LISTA rimuoviInTesta(LISTA l)
{
    if (l == NULL)
    {
        // Se la lista è vuota, ritorna NULL
        return NULL;
    }
    LISTA tmp = l; // Nodo temporaneo per memorizzare l'attuale testa
    l = l->next;   // Aggiorna la testa della lista al prossimo nodo
    free(tmp);     // Libera la memoria del vecchio nodo di testa
    return l;      // Ritorna la nuova testa della lista
}

/**
 * @brief Rimuove un nodo dalla lista in una posizione specificata.
 *
 * Questa funzione rimuove un nodo dalla lista collegata in una posizione specificata dall'indice `idx`.
 * Se l'indice è 0, la lista originale viene restituita senza modifiche.
 * Se la lista è vuota o se si vuole rimuovere la testa, viene chiamata la funzione `rimuoviInTesta`.
 *
 * @param l La lista collegata da cui rimuovere il nodo.
 * @param idx L'indice del nodo da rimuovere (1-based).
 * @return La lista aggiornata con il nodo rimosso.
 */
LISTA rimuoviInMezzo(LISTA l, int idx)
{
    if (idx == 0)
    {
        return l;
    }
    if (l == NULL || idx == 1)
    {
        // Se la lista è vuota o se si vuole rimuovere la testa
        return rimuoviInTesta(l);
    }

    LISTA puntatemp = l;
    int i;

    // Trova il nodo precedente a quello che si vuole rimuovere
    for (i = 1; puntatemp != NULL && i < idx - 1; i++)
    {
        puntatemp = puntatemp->next;
    }

    // Se puntatemp è NULL o puntatemp->next è NULL, l'indice è fuori portata
    if (puntatemp == NULL || puntatemp->next == NULL)
    {
        return l;
    }

    LISTA nodoDaRimuovere = puntatemp->next; // Nodo da rimuovere
    puntatemp->next = nodoDaRimuovere->next; // Salta il nodo da rimuovere
    free(nodoDaRimuovere);                   // Libera la memoria del nodo

    return l; // Ritorna la lista aggiornata
}

/**
 * @brief Rimuove l'ultimo nodo dalla lista.
 *
 * Questa funzione rimuove l'ultimo nodo dalla lista collegata passata come argomento.
 * Se la lista è vuota, non viene effettuata alcuna operazione.
 * Se la lista contiene un solo nodo, questo viene rimosso e la lista diventa vuota.
 *
 * @param l Puntatore alla testa della lista.
 * @return LISTA Puntatore alla testa della lista aggiornata.
 */
LISTA rimuoviInCoda(LISTA l)
{
    if (l == NULL)
    {
        // Se la lista è vuota, non c'è nulla da rimuovere
        return l;
    }

    if (l->next == NULL)
    {
        // Se c'è solo un nodo, rimuoviamo la testa
        free(l);
        return NULL;
    }

    LISTA puntatemp = l;

    // Trova il nodo precedente all'ultimo
    while (puntatemp->next->next != NULL)
    {
        puntatemp = puntatemp->next;
    }

    // Puntiamo il nodo precedente a NULL e liberiamo l'ultimo nodo
    free(puntatemp->next);
    puntatemp->next = NULL;

    return l; // Ritorna la lista aggiornata
}

/**
 * @brief Rimuove il primo nodo che contiene il dato specificato dalla lista.
 *
 * Questa funzione cerca il primo nodo nella lista che contiene il dato specificato
 * e lo rimuove. Se il dato si trova nel primo nodo, viene utilizzata la funzione
 * rimuoviInTesta per rimuoverlo. Se il dato non è presente nella lista, la funzione
 * ritorna la lista invariata.
 *
 * @param l La lista da cui rimuovere il nodo.
 * @param d Il dato da rimuovere dalla lista.
 * @return La lista aggiornata con il nodo rimosso, o la lista invariata se il dato non è presente.
 */
LISTA rimuoviSeDato(LISTA l, DATO d)
{
    if (l == NULL)
    {
        // Se la lista è vuota, non c'è nulla da rimuovere
        return l;
    }

    // Se il dato da rimuovere si trova nel primo nodo
    if (l->dato == d)
    {
        return rimuoviInTesta(l); // Usa la funzione rimuoviInTesta per rimuovere il primo nodo
    }

    LISTA puntatemp = l;

    // Trova il nodo precedente a quello con il dato da rimuovere
    while (puntatemp->next != NULL && puntatemp->next->dato != d)
    {
        puntatemp = puntatemp->next;
    }

    // Se non abbiamo trovato il dato (cioè siamo arrivati alla fine della lista)
    if (puntatemp->next == NULL)
    {
        return l; // Il dato non è presente, ritorna la lista invariata
    }

    // Se abbiamo trovato il dato, rimuoviamo il nodo successivo
    LISTA nodoDaRimuovere = puntatemp->next;
    puntatemp->next = nodoDaRimuovere->next; // Saltiamo il nodo da rimuovere
    free(nodoDaRimuovere);                   // Liberiamo la memoria del nodo

    return l; // Ritorna la lista aggiornata
}

/*
***********************
*******************************************************************************************************
                                        UTILITIES
*******************************************************************************************************
***********************
*/

void stampa(LISTA l)
{
    while (l != NULL)
    {
        printf("%d", l->dato);
        if (l->next != NULL)
        {
            printf(" -> ");
        }
        l = l->next;
    }
    printf("\n");
}

int ComparaListe(LISTA l1, LISTA l2)
{
    if (l1 == NULL || l2 == NULL)
    {
        if (l1 == l2)
        {
            return 1;
        }
        return 0;
    }

    while (l1 != NULL && l2 != NULL)
    {
        if (l1->dato != l2->dato)
        {
            return 0; // Le liste sono diverse
        }
        l1 = l1->next;
        l2 = l2->next;
    }
    if (l1 != l2)
    {
        return 0;
    }
    return 1;
}

int trova(LISTA l, DATO dato, int dir)
{
    if (l == NULL)
    {
        return -1;
    }

    LISTA p = l;
    int c = 0;

    if (dir == 1)
    { // Ordine crescente: trova il primo elemento maggiore di dato
        while (p != NULL)
        {
            if (p->dato > dato)
            {
                return c;
            }
            p = p->next;
            ++c;
        }
    }
    else
    { // Ordine decrescente: trova il primo elemento minore di dato
        while (p != NULL)
        {
            if (p->dato < dato)
            {
                return c;
            }
            p = p->next;
            ++c;
        }
    }

    return -1; // Se non viene trovato alcun elemento
}

LISTA riempiOrd(LISTA l)
{
    int i = 0;
    for (i = 0; i < 10; i++)
    {
        l = insInTesta(l, i);
    }
    return l;
}

LISTA riempiACaso(LISTA l)
{
    int i;
    for (i = 0; i < 10; i++)
    {
        int randomValue = rand() % 100; // Genera un valore casuale tra 0 e 99
        l = insInTesta(l, randomValue);
    }
    return l;
}

LISTA inverti(LISTA l)
{
    LISTA prev = NULL;
    LISTA curr = l;
    LISTA next = NULL;

    while (curr != NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    return prev;
}

LISTA concatena(LISTA l1, LISTA l2)
{
    if (l1 == NULL)
    {
        return l2;
    }

    LISTA p = l1;
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = l2;

    return l1;
}

LISTA ordinaCresc(LISTA l)
{
    if (l == NULL || l->next == NULL)
    {
        return l;
    }

    LISTA a = l;
    LISTA b = l->next;

    while (b != NULL)
    {
        if (a->dato > b->dato)
        {
            DATO temp = a->dato;
            a->dato = b->dato;
            b->dato = temp;
        }
        a = a->next;
        b = b->next;
    }

    return l;
}

LISTA ordinaDecr(LISTA l)
{
    if (l == NULL || l->next == NULL)
    {
        return l;
    }

    LISTA a = l;
    LISTA b = l->next;

    while (b != NULL)
    {
        if (a->dato < b->dato)
        {
            DATO temp = a->dato;
            a->dato = b->dato;
            b->dato = temp;
        }
        a = a->next;
        b = b->next;
    }

    return l;
}

LISTA rimuoviDuplicati(LISTA l)
{
    if (l == NULL || l->next == NULL)
    {
        return l;
    }

    LISTA p = l;
    while (p->next != NULL)
    {
        if (p->dato == p->next->dato)
        {
            LISTA temp = p->next;
            p->next = p->next->next;
            free(temp);
        }
        else
        {
            p = p->next;
        }
    }

    return l;
}

/**
 * @brief Crea una sottolista a partire da una lista esistente.
 *
 * Questa funzione prende una lista esistente e crea una nuova lista
 * contenente gli elementi compresi tra gli indici specificati (inizio incluso, fine escluso).
 *
 * @param l La lista originale da cui estrarre la sottolista.
 * @param inizio L'indice di inizio (inclusivo) della sottolista.
 * @param fine L'indice di fine (esclusivo) della sottolista.
 * @return Una nuova lista contenente gli elementi tra gli indici specificati,
 *         oppure NULL se la lista originale è NULL, o se gli indici non sono validi.
 */
LISTA sottolista(LISTA l, int inizio, int fine)
{
    if (l == NULL || inizio < 0 || fine < inizio)
    {
        return NULL;
    }

    LISTA p = l;
    int i = 0;
    LISTA nuovaLista = NULL;

    while (p != NULL)
    {
        if (i >= inizio && i < fine)
        {
            nuovaLista = insInCoda(nuovaLista, p->dato);
        }
        p = p->next;
        i++;
    }

    return nuovaLista;
}

LISTA trovaCentro(LISTA l)
{
    if (l == NULL)
    {
        return NULL;
    }

    LISTA lento = l;
    LISTA veloce = l;

    while (veloce != NULL && veloce->next != NULL)
    {
        lento = lento->next;
        veloce = veloce->next->next;
    }

    return lento;
}

int Lunghezza(LISTA l)
{
    int count = 0;
    LISTA p = l;

    while (p != NULL)
    {
        count++;
        p = p->next;
    }

    return count;
}

void liberaLista(LISTA l)
{
    LISTA temp;
    while (l != NULL)
    {
        temp = l;
        l = l->next;
        free(temp);
    }
}
/**
 * Ruota una lista collegata di k posizioni.
 *
 * @param l La lista collegata da ruotare.
 * @param k Il numero di posizioni di rotazione.
 * @return La nuova testa della lista ruotata.
 *
 * La funzione ruota una lista collegata di k posizioni. Se la lista è vuota
 * o se k è minore o uguale a 0, la funzione restituisce la lista originale.
 * La funzione calcola la lunghezza della lista e riduce k per evitare
 * rotazioni extra. Se k è 0 dopo la riduzione, la funzione restituisce la
 * lista originale. Altrimenti, la funzione trova il nuovo nodo di testa
 * dopo la rotazione, separa la lista in due parti e collega la seconda parte
 * alla prima per ottenere la lista ruotata.
 */

LISTA ruotaDestra(LISTA l, int k)
{
    if (l == NULL || k <= 0)
    {
        return l;
    }

    int len = Lunghezza(l);
    k = k % len; // Riduce k per evitare rotazioni extra

    if (k == 0)
    {
        return l;
    }

    LISTA p = l;
    int i;

    for (i = 1; i < len - k; i++)
    {
        p = p->next;
    }

    LISTA nuovaTesta = p->next;
    p->next = NULL;

    LISTA temp = nuovaTesta;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = l;
    return nuovaTesta;
}

LISTA ruotaSinistra(LISTA l, int k)
{
    if (l == NULL || k <= 0)
    {
        return l;
    }

    int len = Lunghezza(l);
    k = k % len; // Riduce k per evitare rotazioni extra

    if (k == 0)
    {
        return l;
    }

    LISTA p = l;
    int i;

    for (i = 1; i < k; i++)
    {
        p = p->next;
    }

    LISTA nuovaTesta = p->next;
    p->next = NULL;

    LISTA temp = nuovaTesta;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = l;
    return nuovaTesta;
}

LISTA duplicaLista(LISTA l)
{
    if (l == NULL)
    {
        return NULL;
    }

    LISTA nuovaLista = NULL;
    LISTA p = l;

    while (p != NULL)
    {
        nuovaLista = insInCoda(nuovaLista, p->dato);
        p = p->next;
    }

    return nuovaLista;
}
/**
 * @brief Unisce due liste ordinate in una lista ordinata.
 *
 * Questa funzione prende due liste ordinate, `l1` e `l2`, e le unisce in una singola lista ordinata.
 * La direzione dell'ordinamento è determinata dal parametro `dir`.
 *
 * @param l1 La prima lista ordinata da unire.
 * @param l2 La seconda lista ordinata da unire.
 * @param dir La direzione dell'ordinamento: 1 per ordine crescente, 0 per ordine decrescente.
 * @return La lista risultante dall'unione delle due liste ordinate.
 **/
LISTA mergeListeOrdinato(LISTA l1, LISTA l2, int dir)
{
    LISTA risultato = NULL;

    while (l1 != NULL && l2 != NULL)
    {
        if ((dir == 1 && l1->dato <= l2->dato) || (dir == 0 && l1->dato >= l2->dato))
        {
            risultato = insInCoda(risultato, l1->dato);
            l1 = l1->next;
        }
        else
        {
            risultato = insInCoda(risultato, l2->dato);
            l2 = l2->next;
        }
    }

    while (l1 != NULL)
    {
        risultato = insInCoda(risultato, l1->dato);
        l1 = l1->next;
    }

    while (l2 != NULL)
    {
        risultato = insInCoda(risultato, l2->dato);
        l2 = l2->next;
    }

    return risultato;
}

/**
 * @brief Scambia i nodi di una lista collegata agli indici specificati.
 *
 * Questa funzione prende una lista collegata e due indici, e scambia i dati
 * contenuti nei nodi agli indici specificati. Se gli indici sono uguali o la
 * lista è vuota, la funzione restituisce la lista senza modifiche.
 *
 * @param l La lista collegata.
 * @param idx1 Il primo indice.
 * @param idx2 Il secondo indice.
 * @return La lista collegata con i nodi scambiati, se gli indici sono validi.
 */
LISTA swapNodi(LISTA l, int idx1, int idx2)
{
    if (idx1 == idx2 || l == NULL)
    {
        return l;
    }

    LISTA p1 = l, p2 = l;
    int i;

    for (i = 0; i < idx1 && p1 != NULL; i++)
    {
        p1 = p1->next;
    }

    for (i = 0; i < idx2 && p2 != NULL; i++)
    {
        p2 = p2->next;
    }

    if (p1 != NULL && p2 != NULL)
    {
        DATO temp = p1->dato;
        p1->dato = p2->dato;
        p2->dato = temp;
    }

    return l;
}