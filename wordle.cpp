
#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <vector>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
bool isValid(std::string word, const std::set<std::string>& dict);
void makeWords(int letter, const std::string& floating, std::string& word, std::set<std::string>& words, const std::set<std::string>& dict);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::string word = in;
    std::set<std::string> words;
    makeWords(0, floating, word, words, dict);
    
    
    return words;
}
bool isValid(std::string word, const std::set<std::string>& dict )
{
    std::set<std::string>::iterator it = dict.find(word);
    if (it != dict.end()) // we found the element
    {
        return true;
    }
    return false;
}

void makeWords(int letter, const std::string& floating, std::string& word, std::set<std::string>& words, const std::set<std::string>& dict)
{
    if((letter == word.size())) //Base case
    {
        if(isValid(word, dict))
        {
            words.insert(word);
        }
        return;
    }

    if(word[letter] != '-')
    {
        makeWords(letter + 1, floating, word, words, dict);
        return;
    }
    int count = 0;
    for (int i = 0; i < word.size(); i++) {
        if (word[i] == '-') {
            count++;
        }
    }
    for(int i = 0; i < floating.size(); i++)
    {
        word[letter] = floating[i];
        makeWords(letter + 1, floating.substr(0, i) + floating.substr(i + 1), word, words, dict);
    }
    if(count != floating.size())
    {
        for(char i = 'a'; i <= 'z'; ++i)
        {
            word[letter] = i;
            makeWords(letter + 1, floating, word, words, dict);
        }
    }
    word[letter] = '-';
    return;
}
 