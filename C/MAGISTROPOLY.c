#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PIGEONHOLES 90		//	amount of pigeonholes on the board
#define COLUMNS 10			//	amount of columns on the board
#define PLAYERS 2			//	number of players
#define NAME_LEN 21			//	desired length + 1 (name + '\0')

/*
	TYPES & PROTOTYPES
*/

typedef struct {
	char content[3];		//	default content
	char display[3];		//	what to display

	int position;			//	position on the board
	int status;				//	-1: empty, 0: player one, 1: player two, 2: both
} Pigeonhole;

typedef struct {
	char name[NAME_LEN];	//	name of the player
	char pawn;				//	pawn of the player

	int position;			//	position on the board
	int prevPosition;		//	previous position on the board
	int turnsToSkip;		//	number of turns to skip
} Player;

void initBoard(Pigeonhole *board);
void initPlayers(Pigeonhole *board, Player *players);

void setContent(Pigeonhole *dest);
void inputPlayer(Player *players, int i);

void printBoard(Pigeonhole *board);
void startTurn(Player *players, int active);
void rollDices(int *result1, int *result2);
void movePlayer(Pigeonhole *board, Player *players, int active, int steps);

void doStuff(Pigeonhole *board, Player *players, int active);
void pickImprevisto(Pigeonhole *board, Player *players, int active);
void pickProbabilita(Pigeonhole *board, Player *players, int active);

int isGameover(Player *players, int active);
void endTurn(Player *players, int *active);

void updatePigeonhole(Pigeonhole *pigeonhole, Player *players);
int min(int a, int b);

/*
	FUNCTIONS
*/

int main() {
	Pigeonhole board[PIGEONHOLES];		//	game board
	Player players[PLAYERS];			//	players array

	int result1, result2;				//	results of the dices roll
	int active = 0;						//	index of the active player
	
	//	setup match
	initBoard(board);
	initPlayers(board, players);
	srand(time(NULL));					//	seed the random number generator
	while(getchar() != '\n');			//	clear the input buffer

	//	start the main loop
	while(1) {
		printBoard(board);
		startTurn(players, active);

		//	if the player has to skip this turn, end it and decrease the counter
		if(players[active].turnsToSkip > 0) {
			players[active].turnsToSkip --;

			printf("\tTurno saltato: %d rimanenti.\n", players[active].turnsToSkip);
			endTurn(players, &active);
			continue;
		}

		rollDices(&result1, &result2);
		movePlayer(board, players, active, result1 + result2);

		printBoard(board);
		doStuff(board, players, active);

		if(isGameover(players, active))
			break;

		endTurn(players, &active);
	}

	//	print the final board and the winner
	printBoard(board);
	printf(
		"\n[ IL VINCITORE E' '%s' ]\n"
		"\tPremere invio per uscire...", players[active].name
	);
	getchar();

	return 0;
}

void initBoard(Pigeonhole *board) {
	int i;

	for(i = 0; i < PIGEONHOLES; i ++) {
		board[i].position = i;							//	set position [0 - 89]
		board[i].status = -1;							//	set status to empty

		setContent(board + i);							//	set the default content
		strcpy(board[i].display, board[i].content);		//	display the default content
	}
}

void initPlayers(Pigeonhole *board, Player *players) {
	int i;

	for(i = 0; i < PLAYERS; i ++) {
		//	cycle through the players and input their data
		printf("[ GIOCATORE %d ]\n", i + 1);
		inputPlayer(players, i);
	}

	//	set the players' starting positions
	board[0].status = 2;
	updatePigeonhole(board, players);
}

void setContent(Pigeonhole *dest) {
	//	implementing a pseudo-dict to optimize memory usage
	int keys[] = {5, 10, 16, 19, 24, 27, 34, 41, 48, 59, 62, 70, 77, 80, 87};
	char *values[] = {"??", "IM", "PR", "??", "??", "IM", "PR", "??", "??", "IM", "PR", "??", "??", "IM", "PR"};

	int i;

	for (i = 0; i < 15; i ++) {
		if (dest->position == keys[i]) {
			//	if the given position is a key, set content to the corresponding value
			strcpy(dest->content, values[i]);
			return;
		}
	}

	//	otherwise, set content to the position
	sprintf(dest->content, "%2d", dest->position + 1);
}

void inputPlayer(Player *players, int i) {
	//	init the attributes of the player
	players[i].position = 0;
	players[i].prevPosition = 0;
	players[i].turnsToSkip = 0;

	//	input the name of the player
	printf("\tScegliere un nome: ");

	while(1) {
		scanf("%s", players[i].name);

		//	breaks the loop if the name is available
		if(i == 0 || strcmp(players[1].name, players[0].name) != 0)
			break;

		printf("\tQuesto nome e' gia' stato scelto. Sceglierne un altro: ");
	}
	
	//	input the pawn of the player
	printf("\tScegliere una pedina: ");

	while(1) {
		scanf("\n%c", &players[i].pawn);		//	the input of the player's name leaves '\n' in the buffer, so we need to ignore it

		//	breaks the loop if the pawn is available
		if(i == 0 || players[1].pawn != players[0].pawn)
			break;

		printf("\tQuesta pedina e' gia' statascelta. Sceglierne un'altra: ");
	}
}

void printBoard(Pigeonhole *board) {
	int i;

	//	clear the console and print the heading of the game board
	system("cls");
	printf(
		"+----+----+----+----+----+----+----+----+----+----+\n"
		"|                  MAGISTR-OPOLY                  |\n"
		"+----+----+----+----+----+----+----+----+----+----+\n"
	);

	for(i = 0; i < PIGEONHOLES; i ++) {
		//	print row's pigeonholes one by one
		printf("| %s ", board[i].display);

		//	once all pigeonholes are printed, print the bottom part of the row
		if((i + 1) % COLUMNS == 0)
			printf(
				"|\n"
				"+----+----+----+----+----+----+----+----+----+----+\n"
			);
	}
}

void startTurn(Player *players, int active) {
	printf("\n[ TURNO DI '%s' ]\n", players[active].name);
	printf("\tPosizione attuale: %d\n", players[active].position + 1);
}

void rollDices(int *result1, int *result2) {
	//	wait for the player to press a key
	printf("\tPremere invio per lanciare i dadi...");
	getchar();

	//	roll 2 dices (result: 2~12) and print the result
	*result1 = (rand() % 6) + 1;
	*result2 = (rand() % 6) + 1;

	printf("\tRisultato del tiro: [%d] [%d] -> %d\n", *result1, *result2, *result1 + *result2);
}

void movePlayer(Pigeonhole *board, Player *players, int active, int steps) {
	Pigeonhole *prev;
	Pigeonhole *new;

	//	update the active player's previous position
	players[active].prevPosition = players[active].position;
	players[active].position = min(players[active].position + steps, 89);

	//	shortcuts to the previous and new pigeonholes
	prev = board + players[active].prevPosition;
	new = board + players[active].position;

	/*
		update the previous pigeonhole's status
		if only the active player is on the pigeonhole, set it to empty
		if both players are on the pigeonhole, remove the active player's pawn but keep the other player's pawn
	*/
	if(prev->status == active)
		prev->status = -1;
	else
		prev->status = !active;

	/*
		update the new pigeonhole's status
		if the pigeonhole is empty, add only the active player's pawn
		if the oter player is on the pigeonhole, add both players' pawns
	*/
	if(new->status == -1)
		new->status = active;
	else
		new->status = 2;

	//	update both pigeonholes' display
	updatePigeonhole(prev, players);
	updatePigeonhole(new, players);

	printf("\tLa posizione finale e' %d.\n", players[active].position + 1);
	getchar();		//	wait for the player to press enter
}

void doStuff(Pigeonhole *board, Player *players, int active) {
	int dices1, dices2;

	switch(players[active].position) {
		case 10: case 27: case 59: case 80:
			pickImprevisto(board, players, active);
			break;
		case 16: case 34: case 62: case 87:
			pickProbabilita(board, players, active);
			break;
		case 5:
			printf(
				"\n\n\tPalestra: devi fare 100 piegamenti perche' sei arrivato in ritardo!\n"
				"\tSei costretto a saltare il prossimo turno.\n"
			);

			players[active].turnsToSkip = 1;
			break;
		case 19:
			printf(
				"\n\n\tLaboratorio di informatica: un tuo programma ha craccato il database della scuola!\n"
				"\tTira nuovamente i dadi, ma sta volta tornerai indietro.\n"
			);

			rollDices(&dices1, &dices2);
			movePlayer(board, players, active, (dices1 + dices2) * -1);
			break;
		case 24:
			printf(
				"\n\n\tLaboratorio di chimica: Hai riprodotto la fusione nucleare durante l'ora di lezione!\n"
				"\tTira nuovamente i dadi.\n"
			);

			rollDices(&dices1, &dices2);
			movePlayer(board, players, active, (dices1 + dices2));
			break;
		case 41:
			printf(
				"\n\n\tLaboratorio telecomunicazioni: hai fatto saltare in aria la board!\n"
				"\tSei costretto a saltare i prossimi due turni.\n"
			);

			players[active].turnsToSkip = 2;
			break;
		case 48:
			printf(
				"\n\n\tPalestra: hai vinto la gara di istituto di Triathlon!\n"
				"\tTira due volte i dadi, avanzerai di tante celle quanto vale la loro somma.\n"
			);

			rollDices(&dices1, &dices2);
			int tot = dices1 + dices2;

			rollDices(&dices1, &dices2);
			movePlayer(board, players, active, (dices1 + dices2 + tot));
			break;
		case 70:
			printf(
				"\n\n\tLaboratorio di sistemi e reti: ti sei messo in contatto con Marte!\n"
				"\tTira nuovamente i dadi.\n"
			);

			rollDices(&dices1, &dices2);
			movePlayer(board, players, active, (dices1 + dices2));
			break;
		case 77:
			printf(
				"\n\n\tLaboratorio di fisica: hai inventato la pozione della felicita'!\n"
				"\tTira nuovamente i dadi, ma sta volta tornerai indietro.\n"
			);

			rollDices(&dices1, &dices2);
			movePlayer(board, players, active, (dices1 + dices2) * -1);
	}
}

void pickImprevisto(Pigeonhole *board, Player *players, int active) {
	int card = rand() % 3 + 1;
	int dices1, dices2;

	switch(card) {
		case 1:
			printf(
				"\n\n\tImprevisto: Sei in bilico sui debiti!\n"
				"\tTira i dadi se esce pari avanza del numero uscito altrimenti torna indietro.\n"
			);

			rollDices(&dices1, &dices2);
			int tot = dices1 + dices2;

			if(tot % 2)
				tot *= -1;

			movePlayer(board, players, active, tot);
			break;
		case 2:
			printf(
				"\n\n\tImprevisto: Forse ti interrogano di informatica!\n"
				"\tTira i dadi se esce 9 (il tuo numero) stai fermo un turno.\n"
			);

			rollDices(&dices1, &dices2);
			
			if(dices1 + dices2 == 9)
				players[active].turnsToSkip = 1;

			break;
		case 3:
			printf(
				"\n\n\tImprevisto: Verifica a sorpresa!\n"
				"\tTira i dadi se due numeri escono in coppia torni indietro del valore ottenuto.\n"
			);

			rollDices(&dices1, &dices2);

			if(dices1 == dices2)
				movePlayer(board, players, active, -(dices1 + dices2));
	}
}

void pickProbabilita(Pigeonhole *board, Player *players, int active) {
	int card = rand() % 3 + 1;
	int dices1, dices2;

	switch(card) {
		case 1:
			printf(
				"\n\n\tProbabilita': Devi correre dal dentista!\n"
				"\tStai fermo un turno.\n"
			);

			players[active].turnsToSkip = 1;
			break;
		case 2:
			printf(
				"\n\n\tProbabilita': Il corso di intelligenza artificiale a cui sei iscritto e' slittato!\n"
				"\tTira nuovamente i dadi.\n"
			);

			rollDices(&dices1, &dices2);
			movePlayer(board, players, active, (dices1 + dices2));
			break;
		case 3:
			printf(
				"\n\n\tProbabilita': La prof di italiano oggi non c'e' ed esci prima!\n"
				"\tTira i dadi e avanza della meta' del risultato.\n"
			);

			rollDices(&dices1, &dices2);
			movePlayer(board, players, active, (dices1 + dices2) / 2);
	}
}

int isGameover(Player *players, int active) {
	//	check if the active player has reached the last pigeonhole
	if(players[active].position == 89)
		return 1;

	return 0;
}

void endTurn(Player *players, int *active) {
	//	switch the active player
	*active = !(*active);

	printf("\n\n\tPremere invio per concludere il turno...");
	getchar();
}

void updatePigeonhole(Pigeonhole *pigeonhole, Player *players) {
	/*
		if the pigeonhole's status is "empty", set the display to the default content
		if the pigeonhole's status is "both", set the display to both players' pawns
		else, set the display to the player's pawn
	*/
	if(pigeonhole->status == -1)
		strcpy(pigeonhole->display, pigeonhole->content);
	else if(pigeonhole->status == 2)
		sprintf(pigeonhole->display, "%c%c", players[0].pawn, players[1].pawn);
	else
		sprintf(pigeonhole->display, " %c", players[pigeonhole->status].pawn);
}

int min(int a, int b) {
	//	returns the smallest of the two given numbers
	return a < b ? a : b;
}