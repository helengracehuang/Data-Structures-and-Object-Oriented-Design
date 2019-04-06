//
//  testCarMap.cpp
//  Homework 1
//
//  Created by Xin Huang on 1/21/18.
//  Copyright © 2018 Xin Huang. All rights reserved.
//


#include "CarMap.h"
#include <iostream>
#include <cassert>

using namespace std;

int main()
{
    //Test cases for CarMap(), addCar(), gas(), addGas(), useGas(), fleetSize(), print()
    CarMap c;
    
    assert(c.fleetSize() == 0);
    c.addCar("A");
    assert(c.addGas("A", 5.1));
    c.addCar("B");
    c.addGas("B", 4.3);
    assert(c.addCar("C") && c.addCar("D"));
    c.addGas("C", 4.3);
    assert(!c.addGas("D", -1));
    c.addCar("E");
    assert(c.fleetSize() == 5);
    assert(c.gas("A") == 5.1  && c.gas("C") == 4.3  && c.gas("E") == 0  && c.gas("F") == -1);
    assert(!c.useGas("K", 1.23) && !c.useGas("A", -2.1) && c.useGas("B", .66));
    double fX = c.gas("B");
    assert(c.gas("B") == fX);
    assert(!c.addGas("B", -.66) && c.gas("B") == fX);
    c.print();
    
    cout << "SUPER!" << endl;
}

