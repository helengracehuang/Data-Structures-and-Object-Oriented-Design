//
//  main.cpp
//  Project 2
//
//  Created by Xin Huang on 1/25/18.
//  Copyright © 2018 Xin Huang. All rights reserved.
//

// Map.cpp

#include "Map.h"
#include <iostream>

Map::Map()         // Create an empty map (i.e., one with no key/value pairs)
{
    m_size = 0;
    head = nullptr;
    tail = nullptr;
}

Map::Map(const Map& src)   // copy operator
{
    m_size = 0;
    head = nullptr;
    tail = nullptr;   // initialize
    
    for (int i = 0; i < src.size(); i ++)
    {
        KeyType key;
        ValueType value;
        
        src.get(i, key, value);   // "copy" the values of src to temporary variables key and value
        insert(key, value);       // insert the value of key and value to the new Map
    }
}

Map& Map::operator = (const Map& rhs)   // assignment operator
{
    if (this != &rhs)    // check aliasing
    {
        Map temp(rhs);   // construct a temporary Map temp that copies rhs
        swap(temp);      // swap the value of temp with this object
        /*
         m_Node* p = head;
         while (p != nullptr)
         {
             m_Node *n = p->next;
             delete p;
             p = n;
         }
         m_size = 0;
         head = nullptr;
         tail = nullptr;
         for (int i = 0; i < rhs.size(); i++)
         {
             KeyType key;
             ValueType val;
             rhs.get(i, key, val);
             insert(key, val);
         }
        */
    }
    
    return *this;
}

Map::~Map()   // destructor
{
    m_Node* p = head;
    while (p != nullptr)
    {
        m_Node *n = p->next;    //set n to next node
        delete p;    //Delete node p
        p = n;       //progress by setting p to the next node
    }
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

    m_Node* newNode = new m_Node;
    newNode->pair.m_key = key;
    newNode->pair.m_value = value;
    
    if(empty())   // check empty to avoide tail or head being nullptr
    {
        head = newNode;
        tail = newNode;
        m_size ++;
        
        newNode->next = nullptr;
        newNode->previous = nullptr;
        
        return true;
    }
    
    newNode->next = nullptr;
    newNode->previous = tail;   // add newNode to the end of the linked list
    tail->next = newNode;
    
    tail = newNode;             // update tail
    
    m_size ++;
    
    return true;

}

bool Map::update(const KeyType& key, const ValueType& value)
// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// Otherwise, make no change to the map and return false.
{
    m_Node* p = head;
    for (; p != nullptr && p->pair.m_key != key; p = p->next)
        ;
    if (p != nullptr)
    {
        p->pair.m_value = value;
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
    if (empty())
        return false;
    
    m_Node* p = head;
    for (; p != nullptr && p->pair.m_key != key; p = p->next)
        ;
    if (p != nullptr)
    {
        if (m_size == 1)
        {
            head = nullptr;
            tail = nullptr;
        }
        else if (p == head)              // if head pointer
        {
            head = p->next;              // sets next to head
            head->previous = nullptr;    // changes previous to nullptr
        }
        else if (p == tail)              // if tail pointer
        {
            tail = p->previous;          // sets previous to tail
            tail->next = nullptr;        // changes next to nullptr
        }
        else                             // normal case
        {
            p->previous->next = p->next;
            p->next->previous = p->previous;
        }
        
        delete p;
        m_size --;
        return true;
    }
    
    return false;
}

bool Map::contains(const KeyType& key) const
// Return true if key is equal to a key currently in the map, otherwise
// false.
{
    m_Node* p = head;
    for (; p != nullptr && p->pair.m_key != key; p = p->next)
        ;
    if (p != nullptr)
        return true;
    return false;
}

bool Map::get(const KeyType& key, ValueType& value) const
// If key is equal to a key currently in the map, set value to the
// value in the map that that key maps to, and return true.  Otherwise,
// make no change to the value parameter of this function and return
// false.

{
    m_Node* p = head;
    for (; p != nullptr && p->pair.m_key != key; p = p->next)         // traverses p to the appropriate position
        ;
    if (p != nullptr)
    {
        value = p->pair.m_value;                                      // gets the value of value
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
    if (i >= 0 && i < size())    // check if i is in bound
    {
        m_Node* p = head;
        for (int k = 0; k < i; k++)
            p = p->next;         // traverses p to the appropriate position
        
        key = p->pair.m_key;
        value = p->pair.m_value; // gets the value of key and value from m_key and m_value
        
        return true;
    }
    
    return false;
}

void Map::swap(Map& other)
// Exchange the contents of this map with the other one.
{
    // swap size:
    int tempSize = size();
    m_size = other.size();
    other.m_size = tempSize;
    
    // swap head:
    m_Node* tempHead = head;
    head = other.head;
    other.head = tempHead;
    
    // swap tail:
    m_Node* tempTail = tail;
    tail = other.tail;
    other.tail = tempTail;
}

bool combine(const Map& m1, const Map& m2, Map& result)
{
    Map temp1 = m1;
    result.swap(temp1);
    bool ret = true;
    
    for (int k = 0; k < m2.size(); k++)
    {
        KeyType key;
        ValueType value2;                 // create temporary key2 and value2
        m2.get(k, key, value2);           // copy key2 and value2 from m2
        if (!result.contains(key))
            result.insert(key, value2);
        else
        {
            ValueType value1;
            m1.get(key, value1);
            if (value2 != value1)  // m1 and m2 have same key but different values
            {
                ret = false;
                result.erase(key);
            }
        }
    }
    return ret;
}

void subtract(const Map& m1, const Map& m2, Map& result)
{
    Map temp1 = m1;
    result.swap(temp1);
    
    for (int k = 0; k < m2.size(); k++)
    {
        KeyType key;
        ValueType value;            // create temporary key2 and value2
        m2.get(k, key, value);     // copy key2 and value2 from m2
        if (result.contains(key))
            result.erase(key);
    }
}
