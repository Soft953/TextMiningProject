#pragma once

#include <string>
#include "ptrie.hh"

class DamereauLevenshtein {
    public:
        static int distance(std::string s1, std::string s2);

};