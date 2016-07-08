/**
 * \file stringhash.cpp
 * \author Rachel Lee
 *
 * \brief Implementation of stringhash.hpp
 */

#include "stringhash.hpp"

using std::string;

// Hash Function Gallery
//
// All the code below is in an anonymous namespace, so these function names
// are hidden from other code.

namespace {


/**
 * A hash function based on the sum of the character values in a
 * string. It sums the character values and then mods them by several numbers
 * to further distort the result.
 */
size_t moddedSumHash(const string& str)
{
    int sumOfLetters = 0;
    for(const char& c : str) {
        sumOfLetters = sumOfLetters + c;
    } 
    return (sumOfLetters % 39) + (sumOfLetters % 25) + (sumOfLetters % 5); 
}


/**
 * A hash function that multiplies two large numbers while looping through
 * the string to produce a hash value. It is named for its creator Robert Sedgwicks.
 *
 * http://www.partow.net/programming/hashfunctions/
 */
size_t rsHash(const std::string& str)
{
   size_t b    = 378551;
   size_t a    = 63689;
   size_t hash = 0;

   for(size_t i = 0; i < str.length(); i++)
   {
      hash = hash * a + str[i];
      a    = a * b;
   }

   return hash;
}

/**
 * A hash function that loops through the string setting the hash equal to
 * itself times 33 (with some bit-shifting tactics) plus the character value. 
 *
 * http://www.cse.yorku.ca/~oz/hash.html
 */
size_t thirtyThreeHash(const string& str)
{
    unsigned long hash = 5381;
    auto i = str.begin();
    int c = *i;

    while (i != str.end()) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        c = *(i++);
    }

    return hash;
}

} // end of anonymous namespace

size_t myhash(const string& str)
{
    return rsHash(str);
}

// Provide a table used by stringhash-test.cpp
std::initializer_list<HashFunctionInfo> hashInfo = {
    {"Modded Sum",   moddedSumHash},
    {"RS",           rsHash},
    {"Thirty-Three", thirtyThreeHash}  // No comma for last one
};

