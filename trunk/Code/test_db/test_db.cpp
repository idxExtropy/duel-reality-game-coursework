#include "globals.h"
#include "test_db.h"


//Sprite  testSprites[4];
//User    testUsers[3];
//Unit    testUnits[3];


Database::Database()
{
    cout << "Database constructor ...\n";

    dummySprite = new Sprite;
    dummyUser = new User;
    dummyUnits = new Unit[MAX_UNITS];

    generateSprites();
    testGenerateUsers();
}

Database::~Database()
{
    cout << "Database destructor ...\n";
}

void Database::addSprite(Sprite *sprite)
{
    spriteList << sprite;
}


int Database::spriteCount()
{
    return spriteList.count();
}


QString Database::spriteName(int index) const
{
    return spriteList[index]->name;
}


Sprite Database::loadSprite(QString &spriteName)
{
    int i;

    for (i = 0; i < spriteList.count(); i++)
        if (spriteList[i]->name == spriteName)
            return *spriteList[i];

    return *dummySprite;
}


//User Database::addUser(QString &userName)
void Database::addUser(QString &userName)
{
    User *newUser;
    
    newUser->name = userName;
    userList << newUser;
    
    //return *userList.last();
}


int Database::userCount()
{
    return userList.count();
}


QString Database::userName(int index) const
{
    return userList[index]->name;
}


User Database::loadUser(QString &userName)
{
    int i;

    for (i = 0; i < userList.count(); i++)
        if (userList[i]->name == userName)
            return *userList[i];

    return *dummyUser;
}


void Database::saveUnits(QString &userName, Unit *units)
{
    int i;
    int j;

    for (i = 0; i < userList.count(); i++)
    {
        if (userList[i]->name == userName)
        {
            for (j = 0; j < MAX_UNITS; j++)
                userList[i]->units[j] = units[j];
        }
    }
}


Unit *Database::loadUnits(QString &userName)
{
    int i;

    for (i = 0; i < userList.count(); i++)
        if (userList[i]->name == userName)
            return &(userList[i]->units[0]);

    return &(dummyUnits[0]);
}

void Database::generateSprites()
{
    int i;
    Sprite testSprites[MAX_SPRITES];

    testSprites[0].name = "Wizard";
    testSprites[0].pixMap.load("sprites/wizard.png");
    testSprites[0].AP = 8;
    testSprites[0].HP = 8;
    testSprites[0].range = 8;

    testSprites[1].name = "Monk";
    testSprites[1].pixMap.load("sprites/buddhist.png");
    testSprites[1].AP = 6;
    testSprites[1].HP = 6;
    testSprites[1].range = 6;

    testSprites[2].name = "Bard";
    testSprites[2].pixMap.load("sprites/bard.png");
    testSprites[2].AP = 4;
    testSprites[2].HP = 4;
    testSprites[2].range = 4;

    testSprites[3].name = "Desert Soldier";
    testSprites[3].pixMap.load("sprites/desertsoldier.png");
    testSprites[3].AP = 4;
    testSprites[3].HP = 6;
    testSprites[3].range = 8;

    for (i = 0; i < MAX_SPRITES; i++)
        addSprite(&testSprites[i]);
}


void Database::testGenerateUsers()
{
    User    testUsers[4];

    addUser("Tom");
    testUsers[0].playerName = ;
    testUsers[0].experiencePoints = 2;
    testUsers[0].units[0].status = UNIT_OK;

    units[0].name = "Wizard";
    units[0].attackPower = 2;
    units[0].hitPoints = 2;
    units[0].attackRange = 2;


}


/*

void TestGenerateUsers(void)
{
    testUsers[0].playerName = "Tom";
    testUsers[0].experiencePoints = 2;
    testUsers[0].units[0].status = UNIT_OK;

    units[0].name = "Wizard";
    units[0].attackPower = 2;
    units[0].hitPoints = 2;
    units[0].attackRange = 2;
    SaveUserUnits(units[0].name, &units);*/
    
    /*testUsers[0].units[0].name = "Wizard";
    testUsers[0].units[0].attackPower = 2;
    testUsers[0].units[0].hitPoints = 2;
    testUsers[0].units[0].attackRange = 2;*/
/*
    testUsers[1].playerName = "Dick";
    testUsers[1].experiencePoints = 4;
    testUsers[1].units[0].status = UNIT_OK;
    testUsers[1].units[0].name = "Monk";
    testUsers[1].units[0].attackPower = 4;
    testUsers[1].units[0].hitPoints = 4;
    testUsers[1].units[0].attackRange = 4;
    testUsers[1].units[2].status = UNIT_OK;
    testUsers[1].units[2].name = "Desert Soldier";
    testUsers[1].units[2].attackPower = 6;
    testUsers[1].units[2].hitPoints = 6;
    testUsers[1].units[2].attackRange = 6;

    testUsers[2].playerName = "Harry";
    testUsers[2].experiencePoints = 4;
    testUsers[2].units[0].status = UNIT_OK;
    testUsers[2].units[0].name = "Bard";
    testUsers[2].units[0].attackPower = 2;
    testUsers[2].units[0].hitPoints = 4;
    testUsers[2].units[0].attackRange = 6;
    testUsers[2].units[1].status = UNIT_OK;
    testUsers[2].units[1].name = "Wizard";
    testUsers[2].units[1].attackPower = 6;
    testUsers[2].units[1].hitPoints = 4;
    testUsers[2].units[1].attackRange = 2;    
    testUsers[2].units[0].status = UNIT_DEAD;
}
*/
