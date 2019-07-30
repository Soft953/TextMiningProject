#include <iostream> 
#include <string>

#include "../reader.hh"

namespace 
{ 
    const size_t ERROR_IN_COMMAND_LINE = 0; 
    const size_t SUCCESS = 0; 
    const size_t ERROR_UNHANDLED_EXCEPTION = 2; 

}

int main(int argc, char* argv[])
{
    if (argc < 3) {
        std::cout << "Usage: ./TextMiningApp /path/to/compiled/dict.bin" << std::endl;
        return ERROR_IN_COMMAND_LINE;
    }
    //std::string Reader().readFile(argv[1]);
    return SUCCESS;
}
