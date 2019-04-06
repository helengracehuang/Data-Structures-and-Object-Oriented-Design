#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"

class StudentWorld;   // mention the class StudentWorld for Actor to recognize it

// ====================================== class Actor ======================================
class Actor : public GraphObject
{
public:
    Actor(int ID, StudentWorld* world, double x, double y, int dir = 0, double size = 1.0, int depth = 0, int sourceID = -1);
    virtual ~Actor();
    
    // pure virtual function
    virtual void doSomething() = 0;
    
    // accessor
    virtual bool getLife() const;
    virtual StudentWorld* getWorld() const;
    virtual int getID() const;
    virtual int getSourceID() const;
    virtual bool collide(int x1, int y1, int r1, int x2, int y2, int r2) const;
    
    // mutator
    virtual void setLife(bool aliveOrNot);
    virtual bool moveToIfPossible(double x, double y);
    virtual bool checkWithinBoundary();
    virtual void sufferDamage(int damageHP);   // null
    virtual bool alienDie(int boostScore);     // null
    
private:
    // private members of Actor
    bool a_life;   // whether an actor is visible, e.g. a star moving off-screen (invisible) is "dead"
    StudentWorld* a_world;   // the current world in which this actor locates
    int a_ID;     // to keep track of enemyNum etc.
    int a_sourceID;   // the source from which the torpedo if fired, -1 if it's not a torpedo
};

// ====================================== class Star ======================================
class Star : public Actor
{
public:
    // constructor & destructor
    Star(StudentWorld* world, double x = randInt(0, VIEW_WIDTH-1));
    virtual ~Star();
    
    // mutator
    virtual void doSomething();
    
private:
    // private members of Star (none)
};

// ====================================== class NachenBlaster ======================================
                                     // INCOMPLETE NachenBlaster
class NachenBlaster : public Actor
{
public:
    // constructor & destructor
    NachenBlaster(StudentWorld* world, double x = 0, double y = 128);
    virtual ~NachenBlaster();
    
    // mutator
    virtual void doSomething();
    virtual void sufferDamage(int damageHP);   // decrease HP
    virtual void increaseHP(int amount);       // increase HP
    virtual void increaseTorpedoes(int amount);   // increase # of torpedoes (Torpedo Goodie)
    
    // accessor
    virtual int getHP() const;
    virtual int getCabbages() const;
    virtual int getTorpedoes() const;
    
private:
    // private members of NachenBlaster
    int n_hitPoints;
    int n_cabbageEnergyPoints;
    int n_flatulenceTorpedoes;
};

// ====================================== class Alien ======================================
                                     // INCOMPLETE Alien
class Alien : public Actor
{
public:
    // constructor & destructor
    Alien(StudentWorld* world, int ID, double x = VIEW_WIDTH-1, double y = randInt(0, VIEW_HEIGHT-1));
    virtual ~Alien();
    
    // mutator
    virtual void doSomething() = 0;   // pure virtual, can't be instantiated
    virtual void setHP(int HP);
    virtual void setTS(double ts);
    virtual bool checkAlive();   // check if HP > 0, if false set "dead"
    virtual int changeFlightPlan();   // change flight plan if necessary, return flight plan
    virtual void alienMove();   // move according to the flight plan
    virtual bool alienShoot(bool shoot, bool SpeedUp);   // shoot a projectile due to chance
    virtual bool alienDie(int boostScore);   // increment player's point, set "dead", play sound effect, introduce explosion
    virtual bool shipCollision(int shipDamage);   // check if alien ship collides with the nachenblaster
    virtual bool projectileCollision();   // check if alien ship collides with any projectile
    virtual void sufferDamage(int damageHP);   // decrease HP of alien
    virtual void dropGoodie() = 0;   // pure virtual, drop goodie if necessary
    
    // accessor
    
private:
    // private members of Alien
    int a_hitPoints;
    double a_travelSpeed;
    int a_flightPlan;
        // due left: 1
        // up and left: 2
        // down and left: 3
    int a_flightPlanLength;
        // random int from 1 to 32
};

    // ================================== class Smallgon ==================================
    class Smallgon : public Alien
    {
    public:
        // constructor & destructor
        Smallgon(StudentWorld* world);
        virtual ~Smallgon();
        
        //mutator
        virtual void doSomething();
        virtual void dropGoodie();
        
    private:
        // private members of Smallgon
    };

    // ================================== class Smoregon ==================================
    class Smoregon : public Alien
    {
    public:
        // constructor & destructor
        Smoregon(StudentWorld* world);
        virtual ~Smoregon();
        
        // mutator
        virtual void doSomething();
        virtual void dropGoodie();
        
    private:
        // private members of Smallgon
    };

    // ================================== class Snagglegon ==================================
    class Snagglegon : public Alien
    {
    public:
        // constructor & destructor
        Snagglegon(StudentWorld* world);
        virtual ~Snagglegon();
        
        // mutator
        virtual void doSomething();
        virtual void dropGoodie();
        
    private:
        // private members of Smallgon
    };

// ====================================== class Goodie ======================================
class Goodie : public Actor
{
public:
    // constructor & destructor
    Goodie(StudentWorld* world, int ID, double x, double y);
    virtual ~Goodie();
    
    // mutator
    virtual void doSomething() = 0;   // pure virtual, can't be instantiated
    virtual bool pickedUp();   // check if the goodie is picked up, increment player's point, set "dead", play sound effect
    virtual bool checkWithinBoundary();   // override Actor's check by checking both x and y
};

    // ================================== class RepairGoodie ==================================
    class RepairGoodie : public Goodie
    {
    public:
        // constructor & destructor
        RepairGoodie(StudentWorld* world, double x, double y);
        virtual ~RepairGoodie();
        
        //mutator
        virtual void doSomething();
        
    private:
        // private members of RepairGoodie
    };

    // ================================ class ExtraLifeGoodie ================================
    class ExtraLifeGoodie : public Goodie
    {
    public:
        // constructor & destructor
        ExtraLifeGoodie(StudentWorld* world, double x, double y);
        virtual ~ExtraLifeGoodie();
        
        // mutator
        virtual void doSomething();
        
    private:
        // private members of ExtraLifeGoodie
    };

    // ============================ class FlatulenceTorpedoGoodie ============================
    class FlatulenceTorpedoGoodie : public Goodie
    {
    public:
        // constructor & destructor
        FlatulenceTorpedoGoodie(StudentWorld* world, double x, double y);
        virtual ~FlatulenceTorpedoGoodie();
        
        // mutator
        virtual void doSomething();
        
    private:
        // private members of FlatulenceTorpedoGoodie
    };

// ====================================== class Projectile ======================================
class Projectile : public Actor
{
public:
    // constructor & destructor
    Projectile(StudentWorld* world, int ID, double x, double y, double dir = 0, int sourceID = -1);
    virtual ~Projectile();
    
    // mutator
    virtual void doSomething() = 0;   // pure virtual, can't be instantiated
    virtual bool hitAlien(int damage);   // collides with alien
    virtual bool hitShip(int damage);   // collides with nachenblaster
};

    // =================================== class Cabbage ===================================
    class Cabbage : public Projectile
    {
    public:
        // constructor & destructor
        Cabbage(StudentWorld* world, double x, double y);
        virtual ~Cabbage();
        
        //mutator
        virtual void doSomething();
        
    private:
        // private members of Cabbage
    };

    // ==================================== class Turnip ====================================
    class Turnip : public Projectile
    {
    public:
        // constructor & destructor
        Turnip(StudentWorld* world, double x, double y);
        virtual ~Turnip();
        
        // mutator
        virtual void doSomething();
        
    private:
        // private members of Turnip
    };

    // ========================== class FlatulenceTorpedoProjectile ==========================
    class FlatulenceTorpedoProjectile : public Projectile
    {
    public:
        // constructor & destructor
        FlatulenceTorpedoProjectile(StudentWorld* world, double x, double y, double dir, int sourceID);
        virtual ~FlatulenceTorpedoProjectile();
        
        // mutator
        virtual void doSomething();
        
    private:
        // private members of FlatulenceTorpedoProjectile
    };

// ====================================== class Explosion ======================================
class Explosion : public Actor
{
public:
    // constructor & destructor
    Explosion(StudentWorld* world, double x, double y);
    virtual ~Explosion();
    
    // mutator
    virtual void doSomething();
    
private:
    // private members of Explosion
    int e_tick;
    double e_currentSize;
};
    
#endif // ACTOR_H_
