//
//  Game.hpp
//  Project 1
//
//  Created by Xin Huang on 1/10/18.
//  Copyright © 2018 Xin Huang. All rights reserved.
//

#ifndef Game_h
#define Game_h

#include "City.h"
#include "globals.h"

int decodeDirection(char dir);

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nFlatulans);
    ~Game();
    
    // Mutators
    void play();
    
private:
    City* m_city;
};

#endif /* Game_h */
