#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/damerauLevenshtein.hh"

/*

Example :

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}
*/

TEST_CASE( "Damereau Levenshtein test", "[Distance]" ) {
    REQUIRE( DamereauLevenshtein().distance("test", "test") == 0 );
    REQUIRE( DamereauLevenshtein().distance("test", "teste") == 1 );
    REQUIRE( DamereauLevenshtein().distance("test", "tesk") == 1 );
    REQUIRE( DamereauLevenshtein().distance("test", "west") == 1 );
    REQUIRE( DamereauLevenshtein().distance("test", "tcst") == 1 );
    REQUIRE( DamereauLevenshtein().distance("test", "sesw") == 2 );
    REQUIRE( DamereauLevenshtein().distance("test", "lestu") == 2 );
    REQUIRE( DamereauLevenshtein().distance("test", "bpst") == 2 );
    REQUIRE( DamereauLevenshtein().distance("test", "tstb") == 2 );
}