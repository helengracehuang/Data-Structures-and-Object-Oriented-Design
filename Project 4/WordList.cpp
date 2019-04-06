#include "provided.h"
#include "MyHash.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class WordListImpl
{
public:
    bool loadWordList(string filename);   // O(W)
    bool contains(string word) const;   // O(1)
    vector<string> findCandidates(string cipherWord, string currTranslation) const; // O(Q)
private:
    // private variables
    MyHash<string, int> words;
    MyHash<string, vector<string>> patternMap;
    // private functions
    bool isValid(string s) const;
    void toLower(string& s) const;
    string generatePattern(string s) const;
    void insertWord(string word, vector<string>* vp);
};

// public functions
bool WordListImpl::loadWordList(string filename)
{
    // discard old contents
    words.reset();
    patternMap.reset();
    
    ifstream wordList(filename);
    if (!wordList)  // Opening the file fail?
        return false;
    int n = 1;
    string s;
    while(getline(wordList, s))  // read and process each line of a file until end
    {
        if (isValid(s))
        {
            toLower(s);
            words.associate(s, n);
            if (! patternMap.find(generatePattern(s)))
                patternMap.associate(generatePattern(s), vector<string>());
            insertWord(s, patternMap.find(generatePattern(s)));
            n ++;
        }
        s = "";   // reset s
    }
    return true;
}

bool WordListImpl::contains(string word) const
{
    toLower(word);
    return words.find(word);   // nullptr = false; something else = true
}

vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
{
    vector<string> empty;   // empty vector
    vector<string> candidates;
    // keep everything lowercase
    toLower(cipherWord);
    toLower(currTranslation);
    
    string pattern = generatePattern(cipherWord);
    if (currTranslation.size() != cipherWord.size())   // size doesn't match
        return empty;   // return empty vector
    if (! patternMap.find(generatePattern(cipherWord)))   // cannot find candidate with the same pattern
        return empty;   // return empty vector
    
    candidates = *patternMap.find(generatePattern(cipherWord));   // a vector of valid candidates waiting for translation check
    for(int i = 0; i < candidates.size(); i ++)   // O(Q)
    {
        for (int k = 0; k < currTranslation.size(); k ++)   // O(1)
        {
            char ct = currTranslation[k];
            if (ct == '?')
            {
                if (!isalpha(cipherWord[k]))   // not letter
                    return empty;   // return empty vector
                // no need to check match
            }
            else if (isalpha(ct))
            {
                if (!isalpha(cipherWord[k]))   // not letter
                    return empty;   // return empty vector
                if (candidates[i][k] != ct)   // candidate does not match current translation
                {
                    candidates.erase(candidates.begin() + i);   // erase current word from candidates
                    i --;   // decrement i
                    break;
                }
            }
            else if (ct == '\'')
            {
                if (cipherWord[k] != '\'')   // not apostrophe
                    return empty;   // return empty vector
                if (candidates[i][k] != '\'')   // candidate does not match current translation
                {
                    candidates.erase(candidates.begin() + i);   // erase current word from candidates
                    i --;   // decrement i
                    break;
                }
            }
            else   // strange symbols (neither '?', letter, nor apostrophe)
                return empty;   // return empty vector
        }
    }
    return candidates;
    
}

// private functions
bool WordListImpl::isValid(string s) const
{
    for (char c : s)
    {
        if (!isalpha(c) && c != '\'')
        return false;
    }
    return true;
}

void WordListImpl::toLower(string& s) const
{
    for (int i = 0; i < s.size(); i ++)
    {
        if (isupper(s[i]))
            s[i] = tolower(s[i]);
    }
}

string WordListImpl::generatePattern(string s) const
{
    MyHash<char, char> charMap;
    string pattern;
    char p = 'A';
    for (char c : s)
    {
        if (!charMap.find(c))
        {
            charMap.associate(c, p);
            pattern += p;
            p ++;
        }
        else
            pattern += p;
    }
    
    return pattern;
}

void WordListImpl::insertWord(string word, vector<string>* vp)
{
    vp->push_back(word);
}

//******************** WordList functions ************************************

// These functions simply delegate to WordListImpl's functions.
// You probably don't want to change any of this code.

WordList::WordList()
{
    m_impl = new WordListImpl;
}

WordList::~WordList()
{
    delete m_impl;
}

bool WordList::loadWordList(string filename)
{
    return m_impl->loadWordList(filename);
}

bool WordList::contains(string word) const
{
    return m_impl->contains(word);
}

vector<string> WordList::findCandidates(string cipherWord, string currTranslation) const
{
   return m_impl->findCandidates(cipherWord, currTranslation);
}

//***** hash functions for string, int, and char *****

unsigned int hash(const std::string& s)
{
    return std::hash<std::string>()(s);
}

unsigned int hash(const int& i)
{
    return std::hash<int>()(i);
}

unsigned int hash(const char& c)
{
    return std::hash<char>()(c);
}
