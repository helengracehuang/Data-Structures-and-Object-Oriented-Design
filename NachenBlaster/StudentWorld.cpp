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

// constructor & destructor
StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir), ship(nullptr)
{
    enemyDestroyed = 0;
    enemyNum = 0;
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}

// fundamental functions
int StudentWorld::init()
{
    ship = new NachenBlaster(this);
    initializeStar();
    enemyDestroyed = 0;   // reset
    enemyNum = 0;         // reset
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // Give each actor a chance to do something
    for (vector<Actor*>::iterator p = actors.begin(); p != actors.end(); p++)
    {
        if (p != actors.end() && (*p)->getLife() == true)
            (*p)->doSomething();
    }
    ship->doSomething();
    
    // Check status
    if (theNachenBlasterDiedDuringThisTick())
    {
        // decrease the total lives of NachenBlaster
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    if (theNachenBlasterCompletedTheCurrentLevel())
    {
        increaseScoreAppropriately();   // ?
        return GWSTATUS_FINISHED_LEVEL;
    }
            
    // Remove newly-dead actors after each tick
    removeDeadGameObjects();
    
    // Introduce new stars by a chance of 1/15
    addStar();
    
    // Introduce new aliens per necessary
    addAlien();
    
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
    
    // delete NachenBlaster, set ship to NULL to AVOID dangling pointer or deleting repeatedly
    if (ship != nullptr)
    {
        delete ship;
        ship = nullptr;
    }
}

// accessors
bool StudentWorld::theNachenBlasterDiedDuringThisTick() const
{
    if (ship->getLife() == true)
        return false;
    return true;
}

bool StudentWorld::theNachenBlasterCompletedTheCurrentLevel() const
{
    if (enemyDestroyed >= 6 + (4 * getLevel()))
        return true;
    return false;
}

NachenBlaster* StudentWorld::getShip() const
{
    return ship;
}

vector<Actor*> StudentWorld::getActors() const
{
    return actors;
}

// mutators
void StudentWorld::initializeStar()
{
    for (int i = 0; i < 30; i++)
    {
        actors.push_back(new Star(this));
    }
}

void StudentWorld::removeDeadGameObjects()
{
    for (vector<Actor*>::iterator p = actors.begin(); p != actors.end();)
    {
        if (p != actors.end() && (*p)->getLife() == false)
        {
            if ((*p)->getID() >= 1 && (*p)->getID() <= 3)
                enemyNum --;   // decrement enemyNum to keep track of # of current enemy
            delete *p;
            p = actors.erase(p);
        }
        else
            p ++;
    }
}

void StudentWorld::addStar()
{
    if (randInt(1, 15) == 5)
        actors.push_back(new Star(this, VIEW_WIDTH-1));
}

void StudentWorld::addAlien()
{
    int currentLevel = getLevel();
    int T = 6 + ( 4 * currentLevel);
    int R = T - enemyDestroyed;
    int M = 4 + (.5 * currentLevel);
    
    if (enemyNum < R && enemyNum < M)   // add an alien if necessary
    {
        int S1 = 60;
        int S2 = 20 + 5 * currentLevel;
        int S3 = 5 + 10 * currentLevel;
        int S = S1 + S2 + S3;
        int randomN = randInt(1, S);
        // add corresponding alien according to chance
        if (randomN <= S1)
            actors.push_back(new Smallgon(this));
        else if (randomN <= S1 + S2)
            actors.push_back(new Smoregon(this));
        else
            actors.push_back(new Snagglegon(this));
        
        enemyNum ++;   // increment the enemyNum to keep track of number of current enemy
    }
}

void StudentWorld::addActor(int ID, int x, int y, double dir, int sourceID)
{
    switch (ID)
    {
        // projectiles
        case IID_TURNIP:
            actors.push_back(new Turnip(this, x, y));
            break;
        case IID_CABBAGE:
            actors.push_back(new Cabbage(this, x, y));
            break;
        case IID_TORPEDO:
            actors.push_back(new FlatulenceTorpedoProjectile(this, x, y, dir, sourceID));
            break;
        // goodies
        case IID_REPAIR_GOODIE:
            actors.push_back(new RepairGoodie(this, x, y));
            break;
        case IID_LIFE_GOODIE:
            actors.push_back(new ExtraLifeGoodie(this, x, y));
            break;
        case IID_TORPEDO_GOODIE:
            actors.push_back(new FlatulenceTorpedoGoodie(this, x, y));
            break;
        // explosion
        case IID_EXPLOSION:
            actors.push_back(new Explosion(this, x, y));
            break;
    }
}

void StudentWorld::increaseScoreAppropriately()
{
    // ???
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
