#include "provided.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class DecrypterImpl
{
public:
    DecrypterImpl();
    ~DecrypterImpl();
    bool load(string filename);   // O(W)
    vector<string> crack(const string& ciphertext);   // O(?)
private:
    // private member variables
    WordList* m_wl;
    Translator m_translator;
    
    // private functions
    string Crack(vector<string> raw, vector<string>& output, int index);
    bool isFullyTranslated(string raw);
};

DecrypterImpl::DecrypterImpl()
{
    m_wl = new WordList;
}

DecrypterImpl::~DecrypterImpl()
{
    delete m_wl;
}

bool DecrypterImpl::load(string filename)
{
    delete m_wl;
    m_wl = new WordList;   // discard the old list
    return m_wl->loadWordList(filename);
}

vector<string> DecrypterImpl::crack(const string& ciphertext)
{
    string separators = ",;:.!()[]{}-\"#$%^& 1234567890";   // digits, spaces, & punctuations
    Tokenizer words(separators);
    string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    Tokenizer punctuations(alphabet);
    cout << "1" << endl;
    vector<string> raw = words.tokenize(ciphertext);
    cout << "2" << endl;
    vector<string> punc = punctuations.tokenize(ciphertext);
    cout << "3" << endl;
    
    vector<string> decrypted;
    Tokenizer space(" ");
    Crack(raw, decrypted, -1);
    cout << "4" << endl;
    if (decrypted.empty())
        return decrypted;
    for (int i = 0; i < decrypted.size(); i ++)
    {
        vector<string> almost = space.tokenize(decrypted[i]);
        decrypted[i] = "";   // reset
        for (int k = 0; k < almost.size(); k ++)
            decrypted[i] += almost[k] + punc[k];
    }
    sort(decrypted.begin(), decrypted.end());
    return decrypted;
}

string DecrypterImpl::Crack(vector<string> raw, vector<string>& output, int index)
{
    int longest = 0;
    string longestUntranslated = "";
    string outputString;
    int tempIndex = 0;
    
    // step 2
    // cout << "Crack: 1" << endl;
    // find the longest untranslated ciphertext
    int length;
    for (int i = 0; i < raw.size(); i ++)
    {
        string tr = m_translator.getTranslation(raw[i]);
        length = 0;
        for (int k = 0; k < tr.size(); k ++)
        {
            if (tr[k] == '?')
                length ++;
        }
        if (length >= longest)   // ATTENTION
        {
            longestUntranslated = raw[i];
            tempIndex = i;
            longest = length;
        }
    }
    
    // step 3 & 4
    if (tempIndex != index && longestUntranslated != "")
    {
        cout << "Crack: 2" << endl;
        index = tempIndex;
        vector<string> C = m_wl->findCandidates(longestUntranslated, m_translator.getTranslation(longestUntranslated));
    
        // step 5
        if (C.empty())
            return "";   // return empty string -> back to previous recursive call
        
        // step 6
        for (int i = 0; i < C.size(); i ++)
        {
            vector<string> tempTranslated = raw;
            if (! m_translator.pushMapping(longestUntranslated, C[i]))
            {
                cout << "Crack: 3" << endl;
                // conflict mapping
                goto label;   // wrong mapping, go back to step 6
            }
            for (int k = 0; k < raw.size(); k ++)
            {
                string temp = m_translator.getTranslation(raw[k]);
                if (isFullyTranslated(temp) && ! m_wl->contains(temp))
                {
                    cout << "Crack: 4" << endl;
                    // at least one fully-translated word cannot be found in the word list
                    m_translator.popMapping();
                    goto label;   // wrong mapping, go back to step 6
                }
                tempTranslated[k] = temp;
            }
            for (int k = 0; k < tempTranslated.size(); k ++)
            {
                if (! isFullyTranslated(tempTranslated[k]))
                {
                    cout << "Crack: 5" << endl;
                    // translation not completed
                    outputString += Crack(raw, output, index);   // go back to 2 recursively
                }
            }
            {
                // translation completed
                string complete = "";
                bool completed = true;
                for (int i = 0; i < raw.size(); i ++)
                {
                    string temp = m_translator.getTranslation(raw[i]);
                    if (isFullyTranslated(temp) && m_wl->contains(temp))
                    {
                        // every word is fully translated
                        complete += temp;
                        complete += " ";
                    }
                    else
                        completed = false;
                }
                if (completed)
                {
                    cout << "Crack: 6" << endl;
                    output.push_back(complete);
                    m_translator.popMapping();
                }
            }
            label: ;
        }
    }
    // having tried all candidates in C
    m_translator.popMapping();   // throw away current mapping
    return outputString;
}

bool DecrypterImpl::isFullyTranslated(string raw)
{
    for (char c : raw)
    {
        if (c == '?')
            return false;
    }
    return true;
}

//******************** Decrypter functions ************************************

// These functions simply delegate to DecrypterImpl's functions.
// You probably don't want to change any of this code.

Decrypter::Decrypter()
{
    m_impl = new DecrypterImpl;
}

Decrypter::~Decrypter()
{
    delete m_impl;
}

bool Decrypter::load(string filename)
{
    return m_impl->load(filename);
}

vector<string> Decrypter::crack(const string& ciphertext)
{
   return m_impl->crack(ciphertext);
}
