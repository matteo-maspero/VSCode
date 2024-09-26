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
void inputPlayer(Player *dest);

void printBoard(Pigeonhole *board);
void startTurn(Player *players, int active);
void rollDices(int *result);
void movePlayer(Pigeonhole *board, Player *players, int active, int steps);
void isGameover(Player *players, int active, int *gameover);
void endTurn(Player *players, int *active);

void updatePigeonhole(Pigeonhole *pigeonhole, Player *players);
int min(int a, int b);

/*
	FUNCTIONS
*/

int main() {
	Pigeonhole board[PIGEONHOLES];		//	game board
	Player players[PLAYERS];			//	players array

	int dicesResult;					//	result of the dice roll
	int active = 0;						//	index of the active player
	int gameover = 0;					//	gameover flag
	
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
			endTurn(players, &active);
			players[active].turnsToSkip --;
			continue;
		}

		rollDices(&dicesResult);
		movePlayer(board, players, active, dicesResult);
		isGameover(players, active, &gameover);

		if(gameover)
			break;

		endTurn(players, &active);
	}

	//	print the final board and the winner
	printBoard(board);
	printf(
		"[ IL VINCITORE E' '%s' ]\n"
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
		inputPlayer(players + i);
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

void inputPlayer(Player *dest) {
	//	init the attributes of the player
	dest->position = 0;
	dest->prevPosition = 0;
	dest->turnsToSkip = 0;

	//	input the name of the player
	printf("\tScegliere un nome: ");
	scanf("%s", dest->name);
	
	//	input the pawn of the player
	printf("\tScegliere una pedina: ");
	scanf("\n%c", &dest->pawn);		//	the input of the player's name leaves '\n' in the buffer, so we need to ignore it
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

	if(players[active].turnsToSkip > 0)
		//	if the player has to skip a turn, print the remaining turns to skip
		printf("\tTurno saltato: %d rimanenti.\n", players[active].turnsToSkip - 1);
	else
		printf("\tPosizione attuale: %d\n", players[active].position + 1);
}

void rollDices(int *result) {
	//	wait for the player to press a key
	printf("\tPremere invio per lanciare i dadi...");
	getchar();

	//	roll 2 dices (result: 2~12) and print the result
	*result = (rand() % 11) + 2;
	printf("\tRisultato del tiro: %d\n", *result);
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
}

void isGameover(Player *players, int active, int *gameover) {
	//	check if the active player has reached the last pigeonhole
	if(players[active].position == 89)
		*gameover = 1;
}

void endTurn(Player *players, int *active) {
	//	switch the active player
	*active = !(*active);

	printf("\tPremere invio per concludere il turno...");
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