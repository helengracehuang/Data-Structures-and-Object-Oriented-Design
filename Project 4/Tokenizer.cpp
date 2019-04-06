#include "provided.h"
#include <string>
#include <vector>

using namespace std;

class TokenizerImpl
{
public:
    TokenizerImpl(string separators);   // O(P) (P for # of separators)
    vector<string> tokenize(const std::string& s) const;   // O(S*P) (S for # of characters in s)
private:
    vector<char> sp;
    bool isSeparator(char c) const;   // O(P)
};

TokenizerImpl::TokenizerImpl(string separators)
{
    for (char c : separators)
        sp.push_back(c);
}

vector<string> TokenizerImpl::tokenize(const std::string& s) const
{
    string currword;
    vector<string> words;
    for (int i = 0; i < s.size(); i ++)   // O(S*P)
    {
        char c = s[i];
        if(isSeparator(c))   // O(P)
        {
            // end of current word, push to stack
            if (currword != "")
            {
                words.push_back(currword);
                currword = "";   // reset currword
            }
        }
        else if (i == s.size() - 1)   // for the dangling last segment
        {
            currword += c;
            if (currword != "")
            {
                words.push_back(currword);
                currword = "";   // reset currword
            }
        }
        else
            currword += c;
    }
    return words;
}

// private functions
bool TokenizerImpl::isSeparator(char c) const
{
    for (int i = 0; i < sp.size(); i ++)
    {
        if (c == sp[i])
            return true;
    }
    return false;
}

//******************** Tokenizer functions ************************************

// These functions simply delegate to TokenizerImpl's functions.
// You probably don't want to change any of this code.

Tokenizer::Tokenizer(string separators)
{
    m_impl = new TokenizerImpl(separators);
}

Tokenizer::~Tokenizer()
{
    delete m_impl;
}

vector<string> Tokenizer::tokenize(const std::string& s) const
{
    return m_impl->tokenize(s);
}
