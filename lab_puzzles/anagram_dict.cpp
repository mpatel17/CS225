/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream file;
    file.open (filename);
    size_t curr;
    string finS;

    if (!file.is_open())
      return;

    string word;
    while (file >> word)
    {
      curr = 1;

      for(size_t c = 0; c<word.size(); c++)
        curr *= (int) word[c];

      curr += word.size();
      finS = std::to_string(curr);

      if ( dict.find(finS) == dict.end() ) {
        vector<string> anaCurr = {word};
        dict[finS] = anaCurr;
      }

      else {
        dict[finS].push_back(word);
      }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    size_t curr;
    string finS;

    for(size_t i= 0; i < words.size(); i++){
      curr = 1;

      for(size_t c = 0; c<words[i].size(); c++)
        curr *= (int) words[i][c];

      curr += words[i].size();
      finS = std::to_string(curr);

      if ( dict.find(finS) == dict.end() ) {
        vector<string> anaCurr = {words[i]};
        dict[finS] = anaCurr;
      }

      else {
        dict[finS].push_back(words[i]);
      }
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    string finS;
    size_t curr = 1;

    for(size_t c = 0; c<word.size(); c++)
      curr *= (int) word[c];

    curr += word.size();
    finS = std::to_string(curr);

    if ( dict.find(finS) == dict.end() ) {
      return vector<string>();
    }

    else {
      return dict.find(finS)->second;
    }


}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> totAna;
    for (std::map<string, vector<string>>::const_iterator it = dict.begin(); it != dict.end(); ++it){

      if ((it->second).size() < 2)
        continue;


      else
        totAna.push_back(it->second);
    }

    return totAna;
}
