#include "provided.h"
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>

using namespace std;

class TranslatorImpl
{
public:
    TranslatorImpl();
    bool pushMapping(string ciphertext, string plaintext);   // O(N+L)
    bool popMapping();   // O(L)
    string getTranslation(const string& ciphertext) const;
private:
    vector<map<char, char>> m_mappingTable;
    vector<set<char>> m_set;
    map<char, char> m_curr;
    set<char> s_curr;
    int pushN;
    int popN;
};

TranslatorImpl::TranslatorImpl()
{
    map<char, char> m;
    for (int i = 0; i < 26; i ++)
        m['a'+i] = '?';
    m_mappingTable.push_back(m);
    m_set.push_back(s_curr);  // empty
    m_curr = m;
    pushN = 0;
    popN = 0;
}

bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)   // O(N+L)
{
    if (ciphertext.size() != plaintext.size())   // size does not match
        return false;
    map<char, char> m = m_curr;
    set<char> s = s_curr;
    for (int i = 0; i < ciphertext.size(); i ++)   // O(N)
    {
        if (! isalpha(ciphertext[i]) || ! isalpha(plaintext[i]))
            // either contains non-letter
            return false;
        if (m[tolower(ciphertext[i])] != '?' && m[tolower(ciphertext[i])] != tolower(plaintext[i]))
            // inconsistent
            return false;
        m[tolower(ciphertext[i])] = tolower(plaintext[i]);
        s.insert(tolower(plaintext[i]));
    }
    
    int count = 0;
    for (map<char, char>::iterator it = m.begin(); it != m.end(); it ++)   // O(L)
    {
        if ((*it).second != '?')
            count ++;
    }
    if (s.size() != count)   // inconsistent
        return false;
    
    m_mappingTable.push_back(m);
    m_set.push_back(s);
    m_curr = m;
    s_curr = s;
    pushN ++;
    return true;
}

bool TranslatorImpl::popMapping()
{
    if (pushN == popN)
        return false;
    
    m_curr = *(m_mappingTable.erase(m_mappingTable.end() - 1) - 1);   // pop
    s_curr = *(m_set.erase(m_set.end() - 1) - 1);
    popN ++;
    return true;  // This compiles, but may not be correct
}

string TranslatorImpl::getTranslation(const string& ciphertext) const
{
    map<char, char> m = m_curr;
    string translated = "";
    for (int i = 0; i < ciphertext.size(); i ++)
    {
        if (isalpha(ciphertext[i]))
        {
            if (m[tolower(ciphertext[i])] == '?')
                translated += '?';
            else
            {
                if (isupper(ciphertext[i]))
                    translated += toupper(m[tolower(ciphertext[i])]);
                else
                    translated += m[ciphertext[i]];
            }
        }
        else
            translated += ciphertext[i];   // not a letter, unchanged
    }
    return translated;
}

//******************** Translator functions ************************************

// These functions simply delegate to TranslatorImpl's functions.
// You probably don't want to change any of this code.

Translator::Translator()
{
    m_impl = new TranslatorImpl;
}

Translator::~Translator()
{
    delete m_impl;
}

bool Translator::pushMapping(string ciphertext, string plaintext)
{
    return m_impl->pushMapping(ciphertext, plaintext);
}

bool Translator::popMapping()
{
    return m_impl->popMapping();
}

string Translator::getTranslation(const string& ciphertext) const
{
    return m_impl->getTranslation(ciphertext);
}
