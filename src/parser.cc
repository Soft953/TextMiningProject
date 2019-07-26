#include "parser.hh"

std::vector<std::string> Parser::split(std::string str) {
    std::vector<std::string> result; 
    boost::split(result, str, boost::is_any_of("\n")); 
    return result;
}