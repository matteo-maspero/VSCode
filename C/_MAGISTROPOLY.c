#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PLAYERS 2

/*
	CONFIG
*/

#define ROWS 9			//	amount of rows on the board
#define COLS 10			//	amount of columns on the board
#define NAME_LEN 21		//	desired length + 1 -> "...\0"

/*
	TYPES & PROTOTYPES
*/

typedef struct {
	int position;			//	position on the board
	int status;				//	-1: empty, 0: player one, 1: player two, 2: both
	char content[3];		//	default content
	char display[3];		//	what to display
} Pigeonhole;

typedef struct {
	int position;				//	position on the board
	int previousPosition;		//	last position on the board
	int turnsToSkip;			//	number of turns to skip
	char name[NAME_LEN];		//	name of the player
	char pawn;					//	pawn of the player
} Player;

void initBoard(Pigeonhole board[ROWS][COLS]);
void setDefaultContent(Pigeonhole *pigeonhole);
void printBoard(Pigeonhole board[ROWS][COLS]);

void initPlayers(Pigeonhole board[ROWS][COLS], Player players[PLAYERS], int active);
void getPlayer(Player *dest);

void startTurn(Pigeonhole board[ROWS][COLS], Player players[PLAYERS], int active);
void rollDice(int *result);
void endTurn(Player players[PLAYERS], int *active, int *gameover);

void movePlayer(Pigeonhole board[ROWS][COLS], Player *player, int active, int steps);
void clearPreviousPigeonhole(Pigeonhole board[ROWS][COLS], Player players[PLAYERS], int active);
void setupCurrentPigeonhole(Pigeonhole board[ROWS][COLS], Player players[PLAYERS], int active);
void updatePigeonhole(Pigeonhole *dest, Player players[PLAYERS]);

void checkForAction(Pigeonhole board[ROWS][COLS], Player players[PLAYERS], int active);

/*
	FUNCTIONS
*/

int main() {
	Pigeonhole board[ROWS][COLS];		//	game board
	Player players[PLAYERS];			//	players array

	int gameover = 0;					//	gameover flag
	int activePlayer = 0;				//	index of the active player
	int diceResult;						//	result of the dice roll
	
	//	setup the match for two players
	initBoard(board);
	initPlayers(board, players, activePlayer);
	srand(time(NULL));
	while(getchar() != '\n');	//	clear the input buffer

	//	start the main loop
	do {
		startTurn(board, players, activePlayer);
		printBoard(board);
		rollDice(&diceResult);
		movePlayer(board, players, activePlayer, diceResult);
		checkForAction(board, players, activePlayer);
		endTurn(players, &activePlayer, &gameover);
	} while(!gameover);

	//	print the final board and the winner
	system("cls");
	printf("[ IL VINCITORE E' %s ! ]\n", players[activePlayer].name);
	printBoard(board);
	system("pause");

	return 0;
}

void initBoard(Pigeonhole board[ROWS][COLS]) {
	int i, j;

	for(i = 0; i < ROWS; i ++) {
		for(j = 0; j < COLS; j ++) {
			board[i][j].position = (i * COLS) + j;				//	set position [0 - 89]
			board[i][j].status = -1;								//	set status to empty
			setDefaultContent(&board[i][j]);						//	set the default content
			strcpy(board[i][j].display, board[i][j].content);		//	display the default content
		}
	}
}

void setDefaultContent(Pigeonhole *pigeonhole) {
	//	implementing a pseudo-dict to optimize memory usage
	int keys[] = {6, 11, 17, 20, 25, 28, 35, 42, 49, 60, 63, 71, 78, 81, 88};
	char *values[] = {"??", "IM", "PR", "??", "??", "IM", "PR", "??", "??", "IM", "PR", "??", "??", "IM", "PR"};

	int i;

	for (i = 0; i < 15; i ++) {
		if (pigeonhole->position + 1 == keys[i]) {
			//	if the given position is a key, set content to the corresponding value
			strcpy(pigeonhole->content, values[i]);
			return;
		}
	}
	//	otherwise, set content to the position
	sprintf(pigeonhole->content, "%2d", pigeonhole->position + 1);
}

void printBoard(Pigeonhole src[ROWS][COLS]) {
	int i, j;

	//	print the heading of the game board
	printf(	"\n+----+----+----+----+----+----+----+----+----+----+\n"
			"|                  MAGISTR-OPOLY                  |\n"
			"+----+----+----+----+----+----+----+----+----+----+\n"
	);

	for(i = 0; i < ROWS; i ++) {
		for(j = 0; j < COLS; j ++)
			//	print the i-th row pigeonholes one by one
			printf("| %s ", src[i][j].display);
		//	print the bottom part of the row
		printf("|\n+----+----+----+----+----+----+----+----+----+----+\n");
	}
}

void initPlayers(Pigeonhole board[ROWS][COLS], Player players[PLAYERS], int active) {
	int i;

	for(i = 0; i < PLAYERS; i ++) {
		//	cycle through the players and get their data
		printf("[ GIOCATORE %d ]", i + 1);
		getPlayer(&players[i]);
		movePlayer(board, players, i, 0);
	}
}

void getPlayer(Player *dest) {
	dest->position = 0;				//	set the starting position
	dest->previousPosition = 0; 	//	set the previous position
	dest->turnsToSkip = 0;			//	set the number of turns to skip

	//	get the name and the pawn of the player
	printf("\n\tScegliere un nome: ");
	scanf("%s", dest->name);
	
	printf("\tScegliere una pedina: ");
	scanf("\n%c", &dest->pawn);		//	"\n%c" to avoid buffer issues
}

void startTurn(Pigeonhole board[ROWS][COLS], Player players[PLAYERS], int active) {
	system("cls");
	printf("[ TURNO DI %s ]\n\tPosizione attuale: %d\n", players[active].name, players[active].position + 1);
}

void rollDice(int *result) {
	//	wait for the player to press a key
	printf("\n\tPremere un tasto qualsiasi per lanciare il dado...");
	getchar();

	*result = (rand() % 6) + 1;		//	set *result to a random number between 1 and 6
	printf("\tRisultato del dado: %d\n", *result);
}

void endTurn(Player players[PLAYERS], int *active, int *gameover) {
	printf("\n\tPremere un tasto qualsiasi per concludere il turno...");
	getchar();

	if(players[*active].position >= 89) {
		*gameover = 1;
		return;
	}

	*active = !(*active);	
}

void movePlayer(Pigeonhole board[ROWS][COLS], Player players[PLAYERS], int active, int steps) {
	players[active].previousPosition = players[active].position;
	clearPreviousPigeonhole(board, players, active);

	if(players[active].position + steps > 89)
		players[active].position = 89;
	else
		players[active].position = players[active].position + steps;

	setupCurrentPigeonhole(board, players, active);
}

void clearPreviousPigeonhole(Pigeonhole board[ROWS][COLS], Player players[PLAYERS], int active) {
	int row = (players[active].previousPosition) / COLS;
	int col = (players[active].previousPosition) % COLS;

	if(board[row][col].status == 2)
		board[row][col].status = !active;
	else if(board[row][col].status == active)
		board[row][col].status = -1;

	updatePigeonhole(&board[row][col], players);
}

void setupCurrentPigeonhole(Pigeonhole board[ROWS][COLS], Player players[PLAYERS], int active) {
	int row = (players[active].position) / COLS;
	int col = (players[active].position) % COLS;

	if(board[row][col].status == -1)
		board[row][col].status = active;
	else if(board[row][col].status == !active)
		board[row][col].status = 2;

	updatePigeonhole(&board[row][col], players);
}

void updatePigeonhole(Pigeonhole *dest, Player players[PLAYERS]) {
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

void checkForAction(Pigeonhole board[ROWS][COLS], Player players[PLAYERS], int active) {
	
}