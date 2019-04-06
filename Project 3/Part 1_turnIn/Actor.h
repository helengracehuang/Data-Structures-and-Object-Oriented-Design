#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"

class StudentWorld;   // declare the class StudentWorld for Actor to recognize it

// ====================================== class Actor ======================================
class Actor : public GraphObject
{
public:
    Actor(int a_ID, StudentWorld* world, double a_x, double a_y, int a_dir = 0, double a_size = 1.0, int a_depth = 0);
    virtual ~Actor();
    
    virtual void doSomething() = 0;   // pure virtual
    
    // accessor
    virtual bool getLife() const;
    virtual StudentWorld* getWorld() const;
    
    // mutator
    virtual void setLife(bool aliveOrNot);
    void moveToIfPossible(int x, int y);
    
private:
    // private members of Actor
    bool a_life;   // whether the actor is "alive" or "dead", e.g. a star moving off-screen (invisible) is considered "dead"
    StudentWorld* a_world;   // the current world in which this actor locates
};

// ====================================== class Star ======================================
class Star : public Actor
{
public:
    // constructor & destructor
    Star(StudentWorld* world, double s_x = randInt(0, VIEW_WIDTH-1));
    virtual ~Star();
    
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
    NachenBlaster(StudentWorld* world, double n_x = 0, double n_y = 128);
    virtual ~NachenBlaster();
    
    virtual void doSomething();
    
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
class Alien : public Actor
{
public:
    // constructor & destructor
    Alien(StudentWorld* world, int a_ID, double a_x = VIEW_WIDTH-1, double a_y = randInt(0, VIEW_HEIGHT-1));
    virtual ~Alien();
    
    //Mutator
    virtual void doSomething() = 0;   // pure virtual
    virtual void setHP(int hp);
    virtual void setTS(int ts);
    
private:
    // private members of Alien
    int a_hitPoints;
    int a_energyPoints;   // need???
    double a_travelSpeed;
};

    // ====================================== class Smallgon ======================================
    class Smallgon : public Alien
    {
    public:
        // constructor & destructor
        Smallgon(StudentWorld* world);
        virtual ~Smallgon();
        
    private:
        // private members of Smallgon
    };

    // ====================================== class Smoregon ======================================
    class Smoregon : public Alien
    {
    public:
        // constructor & destructor
        Smoregon(StudentWorld* world);
        virtual ~Smoregon();
        
    private:
        // private members of Smallgon
    };

    // ====================================== class Snagglegon ======================================
    class Snagglegon : public Alien
    {
    public:
        // constructor & destructor
        Snagglegon(StudentWorld* world);
        virtual ~Snagglegon();
        
    private:
        // private members of Smallgon
    };

// ====================================== class Goodie ======================================

// ====================================== class Projectile ======================================

// ====================================== class Explosion ======================================
#endif // ACTOR_H_
