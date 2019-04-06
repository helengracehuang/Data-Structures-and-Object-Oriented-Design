#include <cmath>
#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

// ====================================== class Actor ======================================
// constructor & destructor
Actor::Actor(int ID, StudentWorld* world, double x, double y, int dir, double size, int depth, int sourceID) : GraphObject(ID, x, y, dir, size, depth), a_life(true), a_ID(ID), a_sourceID(sourceID)
{
    a_world = world;
}

Actor::~Actor()
{
    a_life = false;
}

// mutator
void Actor::setLife(bool aliveOrNot)
{
    a_life = aliveOrNot;
}

bool Actor::moveToIfPossible(double x, double y)
{
    if (x < VIEW_WIDTH && y < VIEW_HEIGHT && x >= 0 && y >= 0)   // if the destination is within boundary
    {
        moveTo(x, y);
        return true;
    }
    return false;
}

bool Actor::checkWithinBoundary()   // check if x currently within boundary, if false set "dead"
{
    if (getX() >= 0 && getX() < VIEW_WIDTH)
        return true;
    setLife(false);
    return false;
}

void Actor::sufferDamage(int damageHP)   // null
{}

bool Actor::alienDie(int boostScore)   // null
{
    return false;
}

// accessor
bool Actor::getLife() const
{
    return a_life;
}

StudentWorld* Actor::getWorld() const
{
    return a_world;
}

int Actor::getID() const
{
    return a_ID;
}

int Actor::getSourceID() const
{
    return a_sourceID;
}

bool Actor::collide(int x1, int y1, int r1, int x2, int y2, int r2) const
{
    if (sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)) < .75 * (r1 + r2))
        return true;
    return false;
}

// ====================================== class NachenBlaster ======================================
// constructor & destructor
NachenBlaster::NachenBlaster(StudentWorld* world, double x, double y)
: Actor(IID_NACHENBLASTER, world, x, y, 0, 1.0, 0), n_hitPoints(50), n_cabbageEnergyPoints(30), n_flatulenceTorpedoes(0)
{
}

NachenBlaster::~NachenBlaster()
{
    setLife(false);
}

// mutator
void NachenBlaster::doSomething()
{
    // check alive
    if (n_hitPoints <= 0)
    {
        setLife(false);
        return;
    }
    
    int tempKey;
    if (getWorld()->getKey(tempKey))   // if the user tap a key
    {
        switch(tempKey)
        {
            case KEY_PRESS_SPACE:
                if (n_cabbageEnergyPoints >= 5)
                {
                    getWorld()->addActor(IID_CABBAGE, getX() + 12, getY());
                    getWorld()->playSound(SOUND_PLAYER_SHOOT);
                    n_cabbageEnergyPoints -= 5;
                }
                break;
            case KEY_PRESS_TAB:
                if (n_flatulenceTorpedoes >= 1)
                {
                    getWorld()->addActor(IID_TORPEDO, getX() + 12, getY(), 0, IID_NACHENBLASTER);
                    getWorld()->playSound(SOUND_TORPEDO);
                    n_flatulenceTorpedoes -= 1;
                }
                break;
            // in case of directional keys, update location by six pixels
            case KEY_PRESS_LEFT:
                moveToIfPossible(getX() - 6, getY());
                break;
            case KEY_PRESS_RIGHT:
                moveToIfPossible(getX() + 6, getY());
                break;
            case KEY_PRESS_UP:
                moveToIfPossible(getX(), getY() + 6);
                break;
            case KEY_PRESS_DOWN:
                moveToIfPossible(getX(), getY() - 6);
                break;
        }
    }
    
    // ...incomplete (COLLISION)...
    
    // at the end of the tick, increment the number of cabbage
    if (n_cabbageEnergyPoints < 30)
        n_cabbageEnergyPoints += 1;
}

void NachenBlaster::sufferDamage(int damageHP)
{
    n_hitPoints -= damageHP;
    getWorld()->playSound(SOUND_BLAST);
}

void NachenBlaster::increaseHP(int amount)   // but never exceed 50
{
    n_hitPoints += amount;
    if (n_hitPoints >= 50)
        n_hitPoints = 50;
}

void NachenBlaster::increaseTorpedoes(int amount)
{
    n_flatulenceTorpedoes += amount;
}

// accessor
int NachenBlaster::getHP() const
{
    return n_hitPoints;
}

int NachenBlaster::getCabbages() const
{
    return n_cabbageEnergyPoints;
}

int NachenBlaster::getTorpedoes() const
{
    return n_flatulenceTorpedoes;
}

// ====================================== class Star ======================================
// constructor & destructor
Star::Star(StudentWorld* world, double x)
: Actor(IID_STAR, world, x, randInt(0, VIEW_HEIGHT-1), 0, double(randInt(5, 50))/100, 3)
{
}

Star::~Star()
{
    setLife(false);
}

// mutator
void Star::doSomething()
{
    if(!moveToIfPossible(getX()-1, getY()))   // move by 1
        setLife(false);   // set the star "dead" to be deleted by StudentWorld
}

// ====================================== class Alien ======================================
// constructor & destructor
Alien::Alien(StudentWorld* world, int ID, double x, double y)
: Actor(ID, world, x, y, 0, 1.5, 1), a_flightPlanLength(0)
{}

Alien::~Alien()
{
    setLife(false);
}

// mutator
void Alien::setTS(double ts)
{
    a_travelSpeed = ts;
}

void Alien::setHP(int HP)
{
    a_hitPoints = HP;
}

bool Alien::checkAlive()   // check alive, if false set "dead"
{
    if (a_hitPoints <= 0)
    {
        setLife(false);
        return false;
    }
    return true;
}

int Alien::changeFlightPlan()   // check current flight plan, change if necessary
{
    int y = getY();
    if (a_flightPlanLength <= 0 || y >= VIEW_HEIGHT-1 || y <= 0)
    {
        if (y >= VIEW_HEIGHT-1)
            a_flightPlan = 3;
        else if (y <= 0)
            a_flightPlan = 2;
        else   // if flight plan length <= 0
            a_flightPlan = randInt(1, 3);   // set random direction
        a_flightPlanLength = randInt(1, 32);   // set random flight plan length
    }
        
    return a_flightPlan;
}

void Alien::alienMove()
{
    int x = getX();
    int y = getY();
    switch (a_flightPlan)
    {
        case 1:   // due left
            moveTo(x - a_travelSpeed, y);
            break;
        case 2:   // up and left
            moveTo(x - a_travelSpeed, y + a_travelSpeed);
            break;
        case 3:   // down and left
            moveTo(x - a_travelSpeed, y - a_travelSpeed);
            break;
    }
    a_flightPlanLength --;
}

bool Alien::alienShoot(bool shoot, bool speedUp)
{
    int ship_x = getWorld()->getShip()->getX();
    int ship_y = getWorld()->getShip()->getY();
    int alien_x = getX();
    int alien_y = getY();
    int distance_y = alien_y - ship_y;
    if (ship_x < alien_x && distance_y >= -4 && distance_y <= 4)
    {
        if (shoot)
        {
            // let each alien handles the object by themselves
                // Smallgon & Smoregon: call a new turnip object (<-14px) and pass to StudentWorld
                // Snagglegon: call a new topedo object (<-14px) and pass to StudentWorld
            return true;   // do nothing else
        }
        else if (speedUp)
        {
            a_flightPlan = 1;   // sets travel direction to due left
            a_flightPlanLength = VIEW_WIDTH;
            a_travelSpeed = 5.0;
        }
    }
    return false;
}

bool Alien::alienDie(int boostScore)   // override Actor's AlienDie
{
    if (!checkAlive())   // check alive and set death if necessary
    {
        int x = getX();
        int y = getY();
        getWorld()->increaseScore(boostScore);     // increases player's score
        getWorld()->playSound(SOUND_DEATH);        // sound effect
        getWorld()->addActor(IID_EXPLOSION, x, y); // introduce Explosion
        getWorld()->incrementEnemyDestroyed();     // increment # of enemy destroyed to keep track
        dropGoodie();                              // drop goodie if necessary
        return true;
    }
    return false;
}

bool Alien::shipCollision(int shipDamage)   // check if alien ship collides with the nachenblaster
{
    if (collide(getX(), getY(), getRadius(), getWorld()->getShip()->getX(), getWorld()->getShip()->getY(), getWorld()->getShip()->getRadius()))
    {
        getWorld()->getShip()->sufferDamage(shipDamage);
        a_hitPoints = 0;   // alien's HP becomes 0
        return true;
    }
    return false;
}

bool Alien::projectileCollision()   // check if alien ship collides with any projectile
{
    vector<Actor*> v = getWorld()->getActors();
    for (vector<Actor*>::iterator p = v.begin(); p != v.end(); p ++)
    {
        if (p != v.end())
        {
            if ((*p)->getID() == IID_CABBAGE && collide(getX(), getY(), getRadius(), (*p)->getX(), (*p)->getY(), (*p)->getRadius()))   // collides with a cabbage
            {
                (*p)->setLife(false);   // set the status of this cabbage to "dead"
                sufferDamage(2);
                return true;
            }
            else if ((*p)->getID() == IID_TORPEDO && (*p)->getSourceID() == IID_NACHENBLASTER && collide(getX(), getY(), getRadius(), (*p)->getX(), (*p)->getY(), (*p)->getRadius()))
                // collides with a torpedo fired from a nachenblaster
            {
                (*p)->setLife(false);   // set the status of this torpedo to "dead"
                sufferDamage(8);
                return true;
            }
        }
    }
    return false;
}

void Alien::sufferDamage(int damageHP)
{
    a_hitPoints -= damageHP;
    if (a_hitPoints > 0)
        getWorld()->playSound(SOUND_BLAST);
}

// accessor (none)

    // =================================== class Smallgon ===================================
    // constructor & destructor
    Smallgon::Smallgon(StudentWorld* world)
    : Alien(world, IID_SMALLGON)
    {
        setHP(5 * (1 + (world->getLevel() - 1) * .1));
        setTS(2.0);
    }

    Smallgon::~Smallgon()
    {
        setLife(false);
    }

    // mutator
    void Smallgon::doSomething()
    {
        // check alive && within boundary
        if (!checkAlive() || !checkWithinBoundary())
            return;   // do nothing else
        
        // check collision
        if (!shipCollision(5))
            projectileCollision();
        if (alienDie(250))
            return;   // do nothing else
        
        // change flight plan if necessary
        changeFlightPlan();
        
        // shoot due to chance, if alien shoots then does nothing else
        bool smallgon_shoot = (randInt(1, ((20 / getWorld()->getLevel()) + 5)) == 1);
        if(alienShoot(smallgon_shoot, false))
        {
            getWorld()->playSound(SOUND_ALIEN_SHOOT);
            getWorld()->addActor(IID_TURNIP, getX() - 14, getY());
            return;   // do nothing else
        }
        
        // move correspondingly
        alienMove();
        
        // check collision again
        if (!shipCollision(5))
            projectileCollision();
        if (alienDie(250))
            return;   // do nothing else
    }

    void Smallgon::dropGoodie()
    { /* Smallgons don't drop goodie! */ }

    // =================================== class Smoregon ===================================
    // constructor & destructor
    Smoregon::Smoregon(StudentWorld* world)
    : Alien(world, IID_SMOREGON)
    {
        setHP(5 * (1 + (world->getLevel() - 1) * .1));
        setTS(2.0);
    }

    Smoregon::~Smoregon()
    {
        setLife(false);
    }

    // mutator
    void Smoregon::doSomething()
    {
        // check alive && within boundary
        if (!checkAlive() || !checkWithinBoundary())
            return;
        
        // check collision
        if (!shipCollision(5))
            projectileCollision();
        if (alienDie(250))
            return;   // do nothing else
        
        // change flight plan if necessary
        changeFlightPlan();
        
        // shoot due to chance, if alien shoots then does nothing else
        bool smoregon_shoot = (randInt(1, ((20 / getWorld()->getLevel()) + 5)) == 1);
        bool smoregon_speedUp = (randInt(1, ((20 / getWorld()->getLevel()) + 5)) == 1);
        if(alienShoot(smoregon_shoot, smoregon_speedUp))
        {
            getWorld()->playSound(SOUND_ALIEN_SHOOT);
            getWorld()->addActor(IID_TURNIP, getX() - 14, getY());
            return;   // do nothing else
        }
        
        // move correspondingly
        alienMove();
        
        // check collision again
        if (!shipCollision(5))
            projectileCollision();
        if (alienDie(250))
            return;   // do nothing else
    }

    void Smoregon::dropGoodie()
    {
        if (randInt(1, 3) == 1)   // drop goodie by chance 1/3
        {
            if (randInt(1, 2) == 1)
                getWorld()->addActor(IID_REPAIR_GOODIE, getX(), getY());   // Repair Goodie
            else
                getWorld()->addActor(IID_TORPEDO_GOODIE, getX(), getY());   // Flatulence Torpedo Goodie
        }
    }

    // =================================== class Snagglegon ===================================
    // constructor & destructor
    Snagglegon::Snagglegon(StudentWorld* world)
    : Alien(world, IID_SNAGGLEGON)
    {
        setHP(10 * (1 + (world->getLevel() - 1) * .1));
        setTS(1.75);
    }

    Snagglegon::~Snagglegon()
    {
        setLife(false);
    }

    // mutator
    void Snagglegon::doSomething()
    {
        // check alive && within boundary
        if (!checkAlive() || !checkWithinBoundary())
            return;
        
        // check collision
        if (!shipCollision(15))
            projectileCollision();
        if (alienDie(1000))
            return;   // do nothing else
        
        // change flight plan if necessary
        changeFlightPlan();
        
        // shoot due to chance, if alien shoots then does nothing else
        bool snagglegon_shoot = (randInt(1, ((15 / getWorld()->getLevel()) + 10)) == 1);
        if(alienShoot(snagglegon_shoot, false))
        {
            getWorld()->playSound(SOUND_TORPEDO);
            getWorld()->addActor(IID_TORPEDO, getX() - 14, getY(), 180, IID_SNAGGLEGON);
            return;   // do nothing else
        }
        
        // move correspondingly
        alienMove();
        
        // check collision again
        if (!shipCollision(15))
            projectileCollision();
        if (alienDie(1000))
            return;   // do nothing else
    }

    void Snagglegon::dropGoodie()
    {
        if (randInt(1, 6) == 1)   // drop goodie by chance 1/6
            getWorld()->addActor(IID_LIFE_GOODIE, getX(), getY());   // Extra Life goodie
    }

// ====================================== class Goodie ======================================
// constructor & destructor
Goodie::Goodie(StudentWorld* world, int ID, double x, double y)
: Actor(ID, world, x, y, 0, .5, 1)
{}

Goodie::~Goodie()
{
    setLife(false);
}

// mutator
bool Goodie::pickedUp()
{
    if (collide(getX(), getY(), getRadius(), getWorld()->getShip()->getX(), getWorld()->getShip()->getY(), getWorld()->getShip()->getRadius()))   // collides with a nachenblaster
        {
            getWorld()->increaseScore(100);
            getWorld()->playSound(SOUND_GOODIE);
            setLife(false);
            return true;
        }
    return false;
}

bool Goodie::checkWithinBoundary()   // check if x and y currently within boundary, if false set "dead"
{
    if (getX() >= 0 && getY() >= 0)
        return true;
    setLife(false);
    return false;
}

    // ================================== class RepairGoodie ==================================
    // constructor & destructor
    RepairGoodie::RepairGoodie(StudentWorld* world, double x, double y)
    : Goodie(world, IID_REPAIR_GOODIE, x, y)
    {}

    RepairGoodie::~RepairGoodie()
    {
        setLife(false);
    }

    //mutator
    void RepairGoodie::doSomething()
    {
        // check status
        if (!getLife() || !checkWithinBoundary())
            return;   // do nothing else
        
        // check collision
        if (pickedUp())
        {
            getWorld()->getShip()->increaseHP(10);   // increase HP by 10!
            return;
        }
        
        // move and rotate
        if(!moveToIfPossible(getX() - .75, getY() - .75))
        {
            setLife(false);
            return;
        }
        setDirection(getDirection() + 20);
        
        // check collision again
        if (pickedUp())
        {
            getWorld()->getShip()->increaseHP(10);   // increase HP by 10!
            return;
        }
    }

    // ================================ class ExtraLifeGoodie ================================
    // constructor & destructor
    ExtraLifeGoodie::ExtraLifeGoodie(StudentWorld* world, double x, double y)
    : Goodie(world, IID_LIFE_GOODIE, x, y)
    {}

    ExtraLifeGoodie::~ExtraLifeGoodie()
    {
        setLife(false);
    }

    //mutator
    void ExtraLifeGoodie::doSomething()
    {
        // check status
        if (!getLife() || !checkWithinBoundary())
            return;   // do nothing else
        
        // check collision
        if (pickedUp())
        {
            getWorld()->incLives();   // extra life!
            return;
        }
        
        // move and rotate
        if(!moveToIfPossible(getX() - .75, getY() - .75))
        {
            setLife(false);
            return;
        }
        setDirection(getDirection() + 20);
        
        // check collision again
        if (pickedUp())
        {
            getWorld()->incLives();   // extra life!
            return;
        }
    }

    // ============================ class FlatulenceTorpedoGoodie ============================
    // constructor & destructor
    FlatulenceTorpedoGoodie::FlatulenceTorpedoGoodie(StudentWorld* world, double x, double y)
    : Goodie(world, IID_TORPEDO_GOODIE, x, y)
    {}

    FlatulenceTorpedoGoodie::~FlatulenceTorpedoGoodie()
    {
        setLife(false);
    }

    //mutator
    void FlatulenceTorpedoGoodie::doSomething()
    {
        // check status
        if (!getLife() || !checkWithinBoundary())
            return;   // do nothing else
        
        // check collision
        if (pickedUp())
        {
            getWorld()->getShip()->increaseTorpedoes(5);   // increase # of Topedoes by 5!
            return;
        }
        
        // move and rotate
        if(!moveToIfPossible(getX() - .75, getY() - .75))
        {
            setLife(false);
            return;
        }
        setDirection(getDirection() + 20);
        
        // check collision again
        if (pickedUp())
        {
            getWorld()->getShip()->increaseTorpedoes(5);   // increase # of Topedoes by 5!
            return;
        }
    }

// ====================================== class Projectile ======================================
// constructor & destructor
Projectile::Projectile(StudentWorld* world, int ID, double x, double y, double dir, int sourceID)
: Actor(ID, world, x, y, dir, .5, 1, sourceID)
{}

Projectile::~Projectile()
{
    setLife(false);
}

// mutator
bool Projectile::hitAlien(int damage)
{
    vector<Actor*> v = getWorld()->getActors();
    for (vector<Actor*>::iterator p = v.begin(); p != v.end(); p ++)
    {
        if (p != v.end() && (*p)->getID() >= 1 && (*p)->getID() <= 3  && collide(getX(), getY(), getRadius(), (*p)->getX(), (*p)->getY(), (*p)->getRadius()))   // collides with any alien
        {
            (*p)->sufferDamage(damage);
            int ID = (*p)->getID();
            if (ID == IID_SMALLGON || ID == IID_SMOREGON)        // Smallgon & Smoregon
                (*p)->alienDie(250);
            else if (ID == IID_SNAGGLEGON)              // Snagglegon
                (*p)->alienDie(1000);
            setLife(false);
            return true;
        }
    }
    return false;
}

bool Projectile::hitShip(int damage)
{
    if (collide(getX(), getY(), getRadius(), getWorld()->getShip()->getX(), getWorld()->getShip()->getY(), getWorld()->getShip()->getRadius()))   // collides with nachenblaster
    {
        getWorld()->getShip()->sufferDamage(damage);
        setLife(false);
        return true;
    }
    return false;
}

    // ================================== class Cabbage ==================================
    // constructor & destructor
    Cabbage::Cabbage(StudentWorld* world, double x, double y)
    : Projectile(world, IID_CABBAGE, x, y)
    {}

    Cabbage::~Cabbage()
    {
        setLife(false);
    }

    //mutator
    void Cabbage::doSomething()
    {
        // check status
        if (!getLife() || !checkWithinBoundary())
            return;   // do nothing else
        
        // check collision
        if (hitAlien(2))
            return;
        
        // move and rotate
        if(!moveToIfPossible(getX() + 8, getY()))
        {
            setLife(false);
            return;
        }
        setDirection(getDirection() + 20);
        
        // check collision again
        if (hitAlien(2))
            return;
    }

    // ================================ class Turnip ================================
    // constructor & destructor
    Turnip::Turnip(StudentWorld* world, double x, double y)
    : Projectile(world, IID_TURNIP, x, y)
    {}

    Turnip::~Turnip()
    {
        setLife(false);
    }

    //mutator
    void Turnip::doSomething()
    {
        // check status
        if (!getLife() || !checkWithinBoundary())
            return;   // do nothing else
        
        // check collision
        if (hitShip(2))
            return;
        
        // move and rotate
        if (!moveToIfPossible(getX() - 6, getY()))
        {
            setLife(false);
            return;
        }
        setDirection(getDirection() + 20);
        
        // check collision again
        if (hitShip(2))
            return;
        
    }

    // ========================== class FlatulenceTorpedoProjectile ==========================
    // constructor & destructor
    FlatulenceTorpedoProjectile::FlatulenceTorpedoProjectile(StudentWorld* world, double x, double y, double dir, int sourceID)
    : Projectile(world, IID_TORPEDO, x, y, dir, sourceID)
    {}

    FlatulenceTorpedoProjectile::~FlatulenceTorpedoProjectile()
    {
        setLife(false);
    }

    //mutator
    void FlatulenceTorpedoProjectile::doSomething()
    {
        // check status
        if (!getLife() || !checkWithinBoundary())
            return;   // do nothing else
        // check collision & move & check collision again
        if (getSourceID() == IID_NACHENBLASTER)
        {
            if (hitAlien(8))   // check collision
                return;
            if (!moveToIfPossible(getX() + 8, getY()))   // move
            {
                setLife(false);
                return;
            }
            if (hitAlien(8))   // check collision again
                return;
        }
        else if (getSourceID() == IID_SNAGGLEGON)
        {
            if (hitShip(8))   // check collision
                return;
            if(!moveToIfPossible(getX() - 8, getY()))   // move
            {
                setLife(false);
                return;
            }
            if (hitShip(8))   // check collision again
                return;
        }
    }

// ====================================== class Explosion ======================================
// constructor & destructor
Explosion::Explosion(StudentWorld* world, double x, double y)
: Actor(IID_EXPLOSION, world, x, y, 0, 1, 0)
{
    e_tick = 4;
    e_currentSize = 1;
}

Explosion::~Explosion()
{
    setLife(false);
}

//mutator
void Explosion::doSomething()
{
    setSize(1.5 * e_currentSize);
    e_tick --;
    if (e_tick <= 0)
        setLife(false);
}
