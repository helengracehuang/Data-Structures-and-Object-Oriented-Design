//
//  CarMap.cpp
//  Homework 1
//
//  Created by Xin Huang on 1/21/18.
//  Copyright © 2018 Xin Huang. All rights reserved.
//

#include "CarMap.h"

using namespace std;

/* The words for and while must not appear in CarMap.h or CarMap.cpp, except in the implementation of CarMap::print if you wish. The characters [ (open square bracket) and * must not appear in CarMap.h or CarMap.cpp, except in comments if you wish. You do not have to change std::string to KeyType and double to ValueType in CarMap.h and CarMap.cpp if you don't want to (since unlike Map, which is designed for a wide variety of key and value types, CarMap is specifically designed to work with strings and doubles). In the code you turn in, CarMap's member functions must not call Map::dump.
 */

CarMap::CarMap()       // Create an empty car map.
{
    Map m_map;
}

bool CarMap::addCar(KeyType license)
// If a car with the given license plate is not currently in the map,
// and there is room in the map, add an entry for that car recording
// that it has 0 gallons of gas in it, and return true.  Otherwise,
// make no change to the map and return false.
{
    if (m_map.insert(license, 0))
        return true;
    return false;
}

double CarMap::gas(KeyType license) const
// If a car with the given license plate is in the map, return the
// number of gallons of gas in its tank; otherwise, return -1.
{
    ValueType temp_value;
    if (m_map.get(license, temp_value))
        return temp_value;
    return -1;
}

bool CarMap::addGas(KeyType license, ValueType gallons)
// If no car with the given license plate is in the map or if
// gallons is negative, make no change to the map and return
// false.  Otherwise, increase the number of gallons of gas in the
// indicated car by the gallons parameter and return true.
{
    if (gallons >= 0 && gas(license) >= 0)
    {
        if (m_map.update(license, gas(license) + gallons))
            return true;
    }
    return false;
}

bool CarMap::useGas(KeyType license, ValueType gallons)
// If no car with the given license plate is in the map or if
// gallons is negative or if gallons > gas(), make no change to the
// map and return false.  Otherwise, decrease the number of gallons
// of gas in the indicated car by the gallons parameter and return
// true.
{
    if (gallons < 0 || gallons > gas(license))
        return false;
    m_map.update(license, gas(license) - gallons);
    return true;
}

int CarMap::fleetSize() const  // Return the number of cars in the CarMap.
{
    return m_map.size();
}

void CarMap::print() const
// Write to cout one line for every car in the map.  Each line
// consists of the car's license plate, followed by one space,
// followed by the number of gallons in that car's tank.  Write
// no other text.
{
    KeyType temp_license;
    ValueType temp_gallons;
    for (int i = 0; i < fleetSize(); i ++)
    {
        m_map.get(i, temp_license, temp_gallons);
        cout << temp_license << " " << temp_gallons << endl;
    }
}
