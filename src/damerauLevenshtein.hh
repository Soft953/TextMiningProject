#pragma once

#include <string>
#include "ptrie.hh"

class DamereauLevenshtein {
    public:
        /**
         * Return the Damereau Levenshtein distance between two strings
         */
        static int distance(std::string s1, std::string s2);

};