//
//  main.cpp
//  Project 1
//
//  Created by Xin Huang on 1/10/18.
//  Copyright © 2018 Xin Huang. All rights reserved.
//

#include <iostream>
#include <string>
#include <utility>
#include <cstdlib>
#include "Game.h"
#include "Player.h"

using namespace std;

int main()
{
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(7, 8, 25);
    
    // Play the game
    g.play();
}
