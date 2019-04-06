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
    
    // mutators
    // ...run only in init()
    virtual void initializeStar(vector<Actor*> & actorVector);
    // ...run at each tick
    virtual void removeDeadGameObjects(vector<Actor*> & actorVector);
    virtual void addStar(vector<Actor*> & actorVector);
    virtual void increaseScoreAppropriately();
    virtual void updateDisplayText();
    // ...whenever called
    virtual void incrementEnemyDestroyed();
    
private:
    vector<Actor*> actors;
    NachenBlaster* ship;
    int enemyDestroyed;
};

#endif // STUDENTWORLD_H_
