#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/damerauLevenshtein.hh"
#include "../src/ptrie.hh"

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


int serialiseTest(std::string ref) {
    
    Ptrie p;

    auto a = std::make_shared<Node>(0);
    auto b = std::make_shared<Node>(0);
    auto c = std::make_shared<Node>(0);
    auto d = std::make_shared<Node>(0);
    auto e = std::make_shared<Node>(0);
    auto f = std::make_shared<Node>(0);
    auto g = std::make_shared<Node>(0);
    auto h = std::make_shared<Node>(0);
    auto i = std::make_shared<Node>(0);
    auto j = std::make_shared<Node>(0);
    auto k = std::make_shared<Node>(0);
    
    f->children['k'] = k;
    b->children['e'] = e;
    b->children['f'] = f;
    a->children['b'] = b;
    a->children['c'] = c;
    d->children['g'] = g;
    d->children['h'] = h;
    d->children['i'] = i;
    d->children['j'] = j;
    a->children['d'] = d;

    p.root  = a->children;

    return p.serialize().compare(ref);
}

TEST_CASE( "Serialisation test", "[Serialisation]" ) {
    REQUIRE( serialiseTest("b e ) f k ) ) ) c ) d g ) h ) i ) j ) ) )") == 0 );
}

