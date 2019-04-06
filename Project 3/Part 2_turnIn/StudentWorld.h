#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "Actor.h"
#include "GameWorld.h"
#include <string>
#include <vector>

using namespace std;

class StudentWorld : public GameWorld
{
public:
    // constructor & destructor
    StudentWorld(std::string assetDir);
    virtual ~StudentWorld();
    
    // fundamental functions
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    // accessors
    // ...status check
    virtual bool theNachenBlasterDiedDuringThisTick() const;
    virtual bool theNachenBlasterCompletedTheCurrentLevel() const;
    // ...whenever called
    virtual NachenBlaster* getShip() const;
    virtual vector<Actor*> getActors() const;
    
    // mutators
    // ...only in init()
    virtual void initializeStar();
    // ...at each tick
    virtual void removeDeadGameObjects();
    virtual void addStar();
    virtual void addAlien();
    virtual void addActor(int ID, int x, int y, double dir = 0, int sourceID = -1);
    virtual void increaseScoreAppropriately();
    virtual void updateDisplayText();
    // ...whenever called
    virtual void incrementEnemyDestroyed();
    
private:
    vector<Actor*> actors;
    NachenBlaster* ship;
    int enemyDestroyed;   // number of ships destroyed at current level
    int enemyNum;   // current number of alien ships
};

#endif // STUDENTWORLD_H_
