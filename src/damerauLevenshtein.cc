#include "damerauLevenshtein.hh"

int DamereauLevenshtein::distance(std::string s1, std::string s2) {
    
    int** d = new int*[s1.length() + 1];
    
    for(size_t i = 0; i <= s1.length(); i++)
        d[i] = new int[s2.length() + 1];
    
    for(std::size_t i = 0; i <= s1.length(); i++){
        d[i][0] = i;
    }
    for(std::size_t j = 0; j <= s2.length(); j++){
        d[0][j] = j;
    }

    for(std::size_t i = 1; i <= s1.length(); i++){
        for(std::size_t j = 1; j <= s2.length(); j++){
            int substitution_cost = 0;
            if (s1[i-1] != s2[j-1])
                substitution_cost = 1;
            d[i][j] = std::min({d[i - 1][j] + 1, d[i][j-1] + 1, d[i - 1][j - 1] + substitution_cost});
            if (i > 1 && j > 1 && s1[i] == s2[j - 1] && s1[i-1] == s2[j]) {
                d[i][j] = std::min({d[i][j], d[i - 2][j - 2] + substitution_cost});
            }
        }
    }

    int distance = d[s1.length()][s2.length()];

    for(size_t i = 0; i <= s1.length(); i++)
        delete d[i];
    delete d;
    return distance;
}