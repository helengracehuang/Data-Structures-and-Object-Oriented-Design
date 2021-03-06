//
//  Map.cpp
//  Homework 1
//
//  Created by Xin Huang on 1/21/18.
//  Copyright © 2018 Xin Huang. All rights reserved.
//

#include "Map.h"

Map::Map()         // Create an empty map (i.e., one with no key/value pairs)
{
    m_size = 0;
}

bool Map::empty() const  // Return true if the map is empty, otherwise false.
{
    return (m_size == 0);
}

int Map::size() const    // Return the number of key/value pairs in the map.
{
    return m_size;
}

bool Map::insert(const KeyType& key, const ValueType& value)
// If key is not equal to any key currently in the map, and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that either the key is already in the map, or the map has a fixed
// capacity and is full).
{
    if (contains(key))
        return false;
    if (m_size >= DEFAULT_MAX_ITEMS)
        return false;
    else
    {
        m_array[m_size].m_key = key;
        m_array[m_size].m_value = value;
        m_size ++;
        return true;
    }
}

bool Map::update(const KeyType& key, const ValueType& value)
// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// Otherwise, make no change to the map and return false.
{
    for (int i = 0; i < m_size; i++)
        if (key == m_array[i].m_key)
        {
            m_array[i].m_value = value;
            return true;
        }

    return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// If key is not equal to any key currently in the map and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that the key is not already in the map and the map has a fixed
// capacity and is full).
{
    if (update(key, value))
        return true;
    return (insert(key, value));
}

bool Map::erase(const KeyType& key)
// If key is equal to a key currently in the map, remove the key/value
// pair with that key from the map and return true.  Otherwise, make
// no change to the map and return false.
{
    for (int i = 0; i < m_size; i++)
        if (key == m_array[i].m_key)
        {
            for (int k = i; k < m_size-1; k++)
                m_array[k] = m_array[k+1];
            m_size --;
            return true;
        }
    return false;
}

bool Map::contains(const KeyType& key) const
// Return true if key is equal to a key currently in the map, otherwise
// false.
{
    for (int i = 0; i < m_size; i++)
        if (key == m_array[i].m_key)
            return true;
    return false;
}

bool Map::get(const KeyType& key, ValueType& value) const
// If key is equal to a key currently in the map, set value to the
// value in the map that that key maps to, and return true.  Otherwise,
// make no change to the value parameter of this function and return
// false.

{
    for (int i = 0; i < m_size; i++)
        if (key == m_array[i].m_key)
        {
            value = m_array[i].m_value;
            return true;
        }
    
    return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
// If 0 <= i < size(), copy into the key and value parameters the
// key and value of one of the key/value pairs in the map and return
// true.  Otherwise, leave the key and value parameters unchanged and
// return false.  (See below for details about this function.)

{
    if (i >= 0 && i < size())
    {
        key = m_array[i].m_key;
        value = m_array[i].m_value;
        return true;
    }
    else
        return false;
}

void Map::swap(Map& other)
// Exchange the contents of this map with the other one.
{
    Map temp = *this;
    *this = other;
    other = temp;
}
