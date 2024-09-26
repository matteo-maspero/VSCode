#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PIGEONHOLES 90
#define PLAYERS 2

/*
	CONFIG
*/

#define COLUMNS 10		//	amount of columns on the board
#define NAME_LEN 21		//	desired length increased of 1 (name + '\0')

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
void inputPlayer(Player *dest);

void startTurn(Pigeonhole *board, Player *players, int active);
void printBoard(Pigeonhole *board);
void rollDices(int *result);
void movePlayer(Pigeonhole *board, Player *players, int active, int steps);
void isGameover(Player *players, int active, int *gameover);
void endTurn(Player *players, int *active);

void clearPreviousPigeonhole(Pigeonhole *board, Player *players, int active);
void setupCurrentPigeonhole(Pigeonhole *board, Player *players, int active);
void updatePigeonhole(Pigeonhole *dest, Player *players);

/*
	FUNCTIONS
*/

int main() {
	Pigeonhole board[PIGEONHOLES];		//	game board
	Player players[PLAYERS];			//	players array

	int active = 0;						//	index of the active player
	int diceResult;						//	result of the dice roll
	int gameover = 0;					//	gameover flag
	
	//	setup the match for two players
	initBoard(board);
	initPlayers(board, players);
	srand(time(NULL));

	//	start the main loop
	do {
		printBoard(board);
		startTurn(board, players, active);

		rollDices(&diceResult);
		movePlayer(board, players, active, diceResult);
		checkForAction(board, players, active);

		isGameover(players, active, &gameover);
		endTurn(players, &active);
	} while(!gameover);

	//	print the final board and the winner
	printf("[ IL VINCITORE E' %s ! ]\n", players[active].name);
	printBoard(board);
	system("pause");

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
		//	cycle through the players and get their data
		printf("[ GIOCATORE %d ]\n", i + 1);
		getPlayer(&players[i]);
		movePlayer(board, players, i, 0);
	}
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
	sprintf(dest->content, "%2d", dest->position);
}

void inputPlayers(Player *dest) {
	//	init the attributes of the player
	dest->position = 0;
	dest->prevPosition = 0;
	dest->turnsToSkip = 0;

	//	get the name and the pawn of the player
	printf("\tScegliere un nome: ");
	scanf("%s", dest->name);
	
	printf("\tScegliere una pedina: ");
	scanf("%c", &dest->pawn);		//	"\n%c" to avoid buffer issues
}

void startTurn(Pigeonhole *board, Player *players, int active) {
	printf(	"[ TURNO DI %s ]\n"
			"\tPosizione attuale: %d\n", players[active].name, players[active].position + 1
	);
}

void printBoard(Pigeonhole *board) {
	int i;

	system("cls");
	//	print the heading of the game board
	printf(	"+----+----+----+----+----+----+----+----+----+----+\n"
			"|                  MAGISTR-OPOLY                  |\n"
			"+----+----+----+----+----+----+----+----+----+----+\n"
	);

	for(i = 0; i < PIGEONHOLES; i ++) {
		//	print the row's pigeonholes one by one
		printf("| %s ", board[i].display);

		//	once all the pigeonholes are printed, print the bottom part of the row
		if((i + 1) % COLUMNS == 0)
			printf("|\n+----+----+----+----+----+----+----+----+----+----+\n");
	}
}

void rollDices(int *result) {
	//	wait for the player to press a key
	printf("\tPremere invio per lanciare i dadi...");
	getchar();

	*result = (rand() % 11) + 2;		//	set *result to a random number between 2 and 12 (2 dices)
	printf("\tRisultato del tiro: %d\n", *result);
}

void movePlayer(Pigeonhole *board, Player *players, int active, int steps) {
	players[active].prevPosition = players[active].position;
	clearPreviousPigeonhole(board, players, active);

	if(players[active].position + steps > 89)
		players[active].position = 89;
	else
		players[active].position = players[active].position + steps;

	setupCurrentPigeonhole(board, players, active);
}

void isGameover(Player *players, int active, int *gameover) {
	if(players[active].position == 89)
		*gameover = 1;
}

void endTurn(Player *players, int *active) {
	*active = !(*active);

	printf("\n\tPremere un tasto qualsiasi per concludere il turno...");
	getchar();
}

/*
void clearPreviousPigeonhole(Pigeonhole *board, Player *players, int active) {
	int row = (players[active].prevPosition) / COLS;
	int col = (players[active].prevPosition) % COLS;

	if(board[row][col].status == 2)
		board[row][col].status = !active;
	else if(board[row][col].status == active)
		board[row][col].status = -1;

	updatePigeonhole(&board[row][col], players);
}

void setupCurrentPigeonhole(Pigeonhole *board, Player *players, int active) {
	int row = (players[active].position) / COLS;
	int col = (players[active].position) % COLS;

	if(board[row][col].status == -1)
		board[row][col].status = active;
	else if(board[row][col].status == !active)
		board[row][col].status = 2;

	updatePigeonhole(&board[row][col], players);
}

void updatePigeonhole(Pigeonhole *dest, Player *players) {
	switch (dest->status) {
		case -1:
			strcpy(dest->display, dest->content);
			break;
		case 0: case 1:
			sprintf(dest->display, " %c", players[dest->status].pawn);
			break;
		case 2:
			sprintf(dest->display, "%c%c", players[0].pawn, players[1].pawn);
	}
}
*/