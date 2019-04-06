//
//  investment.cpp
//  Homework 3
//
//  Created by Xin Huang on 2/7/18.
//  Copyright © 2018 Xin Huang. All rights reserved.
//

// Your declarations and implementations would go here
class Investment
{
public:
    Investment(string name, int price);
    virtual ~Investment();
    virtual string name() const;
    virtual bool fungible() const;
    virtual int purchasePrice() const;
    virtual string description() const = 0;
private:
    string m_name;
    int m_price;
};

Investment::Investment(string name, int price)
:m_name(name), m_price(price) {}

Investment::~Investment() {}

string Investment::name() const
{
    return m_name;
}

int Investment::purchasePrice() const
{
    return m_price;
}

bool Investment::fungible() const
{
    return false;
}

class Painting: public Investment
{
public:
    Painting(string name, int price);
    virtual ~Painting();
    virtual string description() const;
};

Painting::Painting(string name, int price)
:Investment(name, price) {}

Painting::~Painting()
{
    cout << "Destroying " << name() << ", " << "a painting" << endl;
}

string Painting::description() const
{
    return "painting";
}

class Stock: public Investment
{
public:
    Stock(string name, int price, string description);
    virtual ~Stock();
    virtual bool fungible() const;
    virtual string description() const;
private:
    string m_description;
};

Stock::Stock(string name, int price, string description)
:Investment(name, price), m_description(description) {}

Stock::~Stock()
{
    cout << "Destroying " << name() << ", " << "a stock holding" << endl;
}

bool Stock::fungible() const
{
    return true;
}

string Stock::description() const
{
    return "stock trading as " + m_description;
}

class House: public Investment
{
public:
    House(string name, int price);
    virtual ~House();
    virtual string description() const;
};

House::House(string name, int price)
:Investment(name, price) {}

House::~House()
{
    cout << "Destroying the house " << name() << endl;
}

string House::description() const
{
    return "house";
}


