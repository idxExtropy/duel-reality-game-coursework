
 /////////////Josh Kilgore
/// 
#include <stdlib.h>
#include "board.h"
#include "global.h" 

Board::Board()

mBoard.resize(BOARD_X*BOARD_Y);

void BOARD::copy(BOARD* src) //copies contents of board except for view & sprites.... THIS IS WHERE DUMP TO DB WILL HAPPEN?
{
 mBoard.duplicate(src->mBoard);  //DEEP COPY!!
 mRunning = src->mRunning;
 mNextPlayer = src->mNextPlayer;
 mMoveCounter = src->mMoveCounter;
}
void Board::resetBoard()    //establishes pristine board: \par
{
mBoard.fill(PLAYER_EMPTY);
mRunning = false;
mMoveCounter = 0;
int player = PLAYER_1;
for (int i=0; i<NUMPIECESFROMSETINGS; i++)
int x, y;
 do
 {
x= random(BOARD_X-2)+1; //adjust for positioning of pieces
y = random(BOARD_Y-2)+1;
 }
 while (getPiece(x,y) != PLAYER_EMPTY);
 setPiece(x,y,player);
if (player == PLAYER_1) player = player2;
else player = Player_1;
}


void Board::switchPlayer() //switches between players
{
if (mNextPlayer == PLAYER_1) {mNextPlayer=PLAYER_2;}
else {mNextPlayer = PLAYER1;}
}

void Board::setPiece(int x, int y, int player)  //puts piece on given coord of board
{
mBoard.at(x+BOARD_X*y) = player;
emit signalSetPiece(x,y,player);
}
int Board::isGameOver()'\par
{
//METHOD TO CHECK IF GAME END CONDITION MET AND WHETHER WIN? / LOSS? 
if ai units all dead - > win
if player untis dead -> lose
}


bool Board::isValidMove(int px,int py);  //checks if space is empty\par
{
if getPiece(px,py)==PLAYER_EMPTY)  {return true;}
return false;
}

bool BOARD::movePlayer(int px, int py)
if (!isValidMove(px,py)) {return false;}
setPiece(px,py,mNextPlayer);
emit signalMove(px,py,mNextPlayer);
addMoveCounter(1);

if (isGameOver())
{
 setRunning(false);
}
 else
{
switchPlayer();
 return true;
}

long Board::random(long max)
{
	double r = (double) rand()/(double) RAND_MAX;
 return (long) (r&max);
}

}
 