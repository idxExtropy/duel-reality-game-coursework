#include "mechanics.h"
#define MAXTEAMS 2
#define PLAYER1 1

// Global classes.
extern GLWidget *glWidget;

//constructor
mechanics::mechanics(QObject *parent) :
    QObject(parent)
{

}
//Destructor
mechanics::~mechanics()
{
}
///////////////////////////////////////////////////BATTLE ACTIVE///////////////////////////
//Returns whether a battle is active
bool mechanics::isBattle()
 {
     return battleRunning;
 }

//Allows game to set condition of whether a battle is running
void mechanics::setBattleRunning(bool battle)
{
    battleRunning = battle;
}

//Called at Start of a Battle
void mechanics::startBattle()
{
    setBattleRunning(true);
    emit signalBattleStart();
}

void mechanics::endBattle()
{
    setBattleRunning(false);
}

//////////////////////////////////////////////////////MOVE///////////////////////////////////////
//Move Function, from Slot Move
void mechanics::move()
{
        mechanics::getPending();
        mechanics::getGridCellSelected();
        if(isValidMove(FocusUnit->actionPoints, FocusUnit->movementRate, FocusUnit->hLocation, FocusUnit->vLocation, targetx, targety))
        {
        FocusUnit->hLocation=targetx;
        FocusUnit->vLocation=targety;
        FocusUnit->actionPoints-=FocusUnit->movementRate;
        }
}

//Determines Whether a move is valid
bool mechanics::isValidMove(int actionpoints, int moverate, int hLoc, int vLoc,int x,int y)
{
if(!mechanics::isOccupied(x, y))
        {
        if (isSufficientAP(actionpoints, moverate))
        {
                if((vLoc==y)||(hLoc==x))
                {
                        if(((abs(vLoc-y))<=1)&&((abs(hLoc-x))<=1))
                        {
                        return (true);
                        }
                }
                return(false);
        }
        return (false);

}
return (false);
}

//Determines if a space is occupied
bool mechanics::isOccupied(int x, int y)  ///DOUBLECHECK
{

    if (glWidget->battleMap.gridCell[x][y].isUnit)
        {
        return (true);
        }
       else return false;
}

//Returns whether Unit has enough Action Points to Move/act
bool mechanics::isSufficientAP(int a, int b)
{
        if(a>=b)
        {
        return true;
        }
        else return false;
}
////////////////////////////////////////////////ATTACK////////////////////////////////////////////////
void mechanics::attack()
{
    mechanics::getPending();
    mechanics::getGridCellSelected();
    Unit *a= mechanics::getUnit(targetx,targety);
    Unit *Target = a;

        if(isValidAttack(FocusUnit->actionPoints, FocusUnit->movementRate, FocusUnit->hLocation, FocusUnit->vLocation, FocusUnit->attackRange, targetx, targety))
        {
        Target->hitPoints-=FocusUnit->attackPower;
        if(Target->hitPoints<=0)
          {
          Target->status= UNIT_DEAD;
            }
        mechanics::isGameOver();
        }

}
//Determines Whether an attack is valid
bool mechanics::isValidAttack(int actionpoints, int moverate, int hLoc, int vLoc, int atkrange, int x, int  y)
{
if(mechanics::isOccupied(x, y))
       {
        if (isSufficientAP(actionpoints, moverate))
        {
                if((vLoc==y)||(hLoc==x))
                {
                        if(((abs(vLoc-y))<=atkrange)&&((abs(hLoc-x))<=atkrange))
                        {
                        return (true);
                        }
                }
                return(false);
        }
        return (false);
}
return (false);
}
///*
// if there is a unit with isPending=true, loads FocusUnit pointer to address of that unit - called by move/attack
bool mechanics::getPending()
{
    for(int x=0;x<=glWidget->battleMap.cellsTall;x++)
    {
        for(int y=0;y<=glWidget->battleMap.cellsWide;y++)
        {
          if(glWidget->battleMap.gridCell[x][y].unit->isPending)
          {
          FocusUnit=glWidget->battleMap.gridCell[x][y].unit;
          return true;
          }
          return (false);
        }
    }return (false);
}

Unit *mechanics::getUnit(int x, int y)
     {
        return glWidget->battleMap.gridCell[y][x].unit;    //vLoc, HLoc order in glwidget.cpp
     }

/////////////////////////////////////////////////////////////FOCUS////////////////////

//// Set's which unit that the player is moving that turn
//// needs another signal slot - used at start of player 1 turn
/////////////////////////////////////////////
//
//finds which gridCell is selected, passes coordinates to targetx & target y
bool mechanics::getGridCellSelected() //2D array of pointers of type gridBox
{
    int *ip1 = &targetx;
    int *ip2 = &targety;
        for(int x=0;x<=glWidget->battleMap.cellsTall;x++)
        {
         for(int y=0;y<=glWidget->battleMap.cellsWide;y++)
         {
                if(glWidget->battleMap.gridCell[x][y].isSelected)
                {
                        *ip1=x;
                        *ip2=y;
                        return (true);

                }
               return (false);
         }
        }return (false);
}
//////////////////////////////////////////////////TURNS//////////////////////////////////////////////
////executes when passed ENDTURN SIGNAL
////deselect focus unit?
////
//
//void mechanics::endTurn()
//{
//        //mechanics::switchPlayer();
//}
//

////
//
////////////////////////////////////////////////GAMEOVER//////////////////////////////////
bool mechanics::isGameOver()
{
    int deadcount=0;
    for(int x=0;x<=glWidget->battleMap.cellsTall;x++)
    {
     for(int y=0;y<=glWidget->battleMap.cellsWide;y++)
     {
           if(glWidget->battleMap.gridCell[x][y].unit->status==UNIT_DEAD&&glWidget->battleMap.gridCell[x][y].unit->team==USER_UNIT)
           {
                    deadcount++;
                if (deadcount ==4)
                {
                    emit SignalP2Win();
                  //mechanics::EndBattle();
                    return true;
                }
            }

            if (glWidget->battleMap.gridCell[x][y].unit->status==UNIT_DEAD&&glWidget->battleMap.gridCell[x][y].unit->team==AI_UNIT)
            {
                    deadcount++;
                if (deadcount ==4)
                 {
                 emit SignalP1Win();
                 //mechanics::EndBattle();
                 return true;
                 }
            }
            else
                deadcount=0;
                return false;
        }
    }
    return false;
}
////////////////////////////////////////////////////AI/////////////////////////////////////
 void mechanics::startAI()
{

    //AI myAI;
   //bool result = myAI.getmove(px,py);
     // if(result){move(Unit *UnitPointer,int x, int y);
     //mechanics::isGameOver();

}