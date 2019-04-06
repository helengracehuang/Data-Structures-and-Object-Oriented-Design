#include "StudentWorld.h"
#include "GameConstants.h"

#include <string>
#include <vector>
#include <list>
#include <iostream> // defines the overloads of the << operator
#include <sstream>  // defines the type std::ostringstream

using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir), ship(nullptr)
{
    enemyDestroyed = 0;
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}

int StudentWorld::init()
{
    ship = new NachenBlaster(this);
    initializeStar(actors);
    enemyDestroyed = 0;
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    
    // Give each actor a chance to do something
    for (vector<Actor*>::iterator p = actors.begin(); p != actors.end(); p++)
    {
        if (p != actors.end() && (*p)->getLife() == true)
            (*p)->doSomething();
    }
    ship->doSomething();
    
    // Check status
    if (theNachenBlasterDiedDuringThisTick())
        return GWSTATUS_PLAYER_DIED;
    if (theNachenBlasterCompletedTheCurrentLevel())
    {
        increaseScoreAppropriately();   // incomplete
        return GWSTATUS_FINISHED_LEVEL;
    }
            
    // Remove newly-dead actors after each tick
    removeDeadGameObjects(actors);
    
    // Introduce new stars by a chance of 1/15
    addStar(actors);
    
    // Update the Game Status Line
    updateDisplayText();
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()   // incomplete
{
    // delete the vector of all the actors except for NachenBlaster
    for (vector<Actor*>::iterator p = actors.begin(); p != actors.end();)
    {
        if(p != actors.end())
        {
            delete *p;
            p = actors.erase(p);
        }
        else
            p ++;
    }
    
    // delete NachenBlaster
    if (ship != nullptr)
    {
        delete ship;
        ship = nullptr;
    }
}

bool StudentWorld::theNachenBlasterDiedDuringThisTick() const
{
    if (ship->getLife() == true)
        return false;
    return true;
}

bool StudentWorld::theNachenBlasterCompletedTheCurrentLevel() const
{
    if (enemyDestroyed >= 6 + (4 * getLevel()) )
        return true;
    return false;
}

void StudentWorld::initializeStar(vector<Actor*> & actorVector)
{
    for (int i = 0; i < 30; i++)
    {
        actors.push_back(new Star(this));
    }
}

void StudentWorld::removeDeadGameObjects(vector<Actor*> & actorVector)   // except for NachenBlaster
{
    for (vector<Actor*>::iterator p = actorVector.begin(); p != actorVector.end();)
    {
        if (p != actorVector.end() && (*p)->getLife() == false)
        {
            delete *p;
            p = actorVector.erase(p);
        }
        else
            p ++;
    }
}

void StudentWorld::addStar(vector<Actor*> & actorVector)
{
    if (randInt(1, 15) == 5)
        actors.push_back(new Star(this, VIEW_WIDTH-1));
}

void StudentWorld::increaseScoreAppropriately()
{
    // incomplete
}

void StudentWorld::updateDisplayText()
{
    ostringstream oss;
    oss << "Lives: " << getLives() << "  ";
    oss << "Health: " << 100*ship->getHP()/50 << "%  ";
    oss << "Score: " << getScore() << "  ";
    oss << "Level: " << getLevel() << "  ";
    oss << "Cabbages: " << 100*ship->getCabbages()/30 << "%  ";
    oss << "Torpedoes: " << ship->getTorpedoes();
    
    string s = oss.str();
    setGameStatText(s);
}

void StudentWorld::incrementEnemyDestroyed()
{
    enemyDestroyed ++;
}
