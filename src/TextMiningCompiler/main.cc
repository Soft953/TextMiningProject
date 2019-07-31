#include <iostream> 
#include <fstream>
#include <string>

#include "../reader.hh"
#include "../ptrie.hh"

namespace 
{ 
    const size_t ERROR_IN_COMMAND_LINE = 0; 
    const size_t SUCCESS = 0; 
    const size_t ERROR_UNHANDLED_EXCEPTION = 2; 

}

int main(int argc, char* argv[])
{
    if (argc < 3) {
        std::cout << "Usage: ./TextMiningCompiler /path/to/word/freq.txt /path/to/output/dict.bin" << std::endl;
        return ERROR_IN_COMMAND_LINE;
    }
    /*
    auto [mmappedData, fd] = Reader().readFile(argv[1]);
    
    auto data = static_cast<char*>(mmappedData);
    std::string data_str = std::string(data);
    */

    Ptrie p;

    p.build(argv[1]);
    auto save = p.serialize();

    Ptrie p2;
    p2.deSerialize(save);

    std::cout << save << std::endl;
    std::cout << p2.serialize() << std::endl;
    
    //p.made_patricia();
    //p.getWords();
    
    /*std::ofstream outputFile (argv[2]);
    if (outputFile.is_open())
    {
        outputFile << p.serialize();
        outputFile.close();
    }
    else
        std::cout << "Unable to open file" << std::endl;
*/
    //Reader().clearMmappedData(argv[1], mmappedData, fd);
    return SUCCESS;
}
