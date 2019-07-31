#include <iostream> 
#include <string>

#include "../reader.hh"
#include "../ptrie.hh"
#include "../damerauLevenshtein.hh"

namespace 
{ 
    const size_t ERROR_IN_COMMAND_LINE = 0; 
    const size_t SUCCESS = 0; 
    const size_t ERROR_UNHANDLED_EXCEPTION = 2; 

}

struct Word
{
    std::string str;
    int freq = 0;
    int distance = 0;
};

// Sort by distance
bool compareDistance(const Word& e1, const Word& e2) {
    return (e1.distance < e2.distance);
}

// Sort by frequence
bool compareFrequence(const Word& e1, const Word& e2) {
    return (e1.freq > e2.freq);
}

size_t SIZE = 0;
size_t IT = 0;

// Sort by Lexi
bool compareLexi(const Word& e1, const Word& e2) {
    //WTF Iterator goes too far ! we need to stop it.... 2h of debug
    if (IT >= SIZE) return 0;
    IT++;
    return e1.str.compare(e2.str);
} 

void findWordWithDistanceRec(std::string word, std::shared_ptr<Node> node, std::string str, int distance, std::vector<Word>& result){
    for(auto const& [key, val] : node->children){
        std::string cpy = word;
        cpy += key;
        if(val->getFreq() > 0) {
            int d = DamereauLevenshtein().distance(str, cpy);
            if (d <= distance) {
                if (cpy.empty()) {
                    std::cout << "EMPTY HER" << std::endl;
                }
                result.push_back({cpy, val->getFreq(), d});
            }
        }
        if(val->children.size() >= 1)
            findWordWithDistanceRec(cpy, val, str, distance, result);
    }
}


void findWordWithDistance(Ptrie p, std::string str, int distance, std::vector<Word>& result) {
    for(auto const& [key, val] : p.root){
        std::string word = "";
        word += key;
        if(val->getFreq() > 0) {
            int d = DamereauLevenshtein().distance(str, word);
            if (d <= distance) {
                if (word.empty()) {
                    std::cout << "EMPTY HER" << std::endl;
                }
                result.push_back({word, val->getFreq(), d});
            }

        }
        if(val->children.size() >= 1)
            findWordWithDistanceRec(word, val, str, distance, result);
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Usage: ./TextMiningApp /path/to/compiled/dict.bin" << std::endl;
        return ERROR_IN_COMMAND_LINE;
    }
    std::ifstream inFile;
    inFile.open(argv[1]);
    if(!inFile){
        std::cerr << "Unable to open file" << std::endl;
        exit(1);
    }
    std::string line;

    Ptrie p;
    while(std::getline(inFile, line)){
        p.deSerialize(line);
    }

    std::vector<std::string> wordsToFind;
    std::vector<int> distanceToFind;


    for (std::string line_in; std::getline(std::cin, line_in);) {
        std::vector<std::string> tmp; 
        boost::split(tmp, line_in, boost::is_any_of(" "));
        wordsToFind.push_back(tmp[2]);
        distanceToFind.push_back(std::stoi(tmp[1]));
    }

    for (size_t j = 0; j < wordsToFind.size(); j++)
    {
        std::vector<Word> result = std::vector<Word>();

        findWordWithDistance(p, wordsToFind[j], distanceToFind[j], result);

        SIZE = result.size();
        IT = 0;
        
        std::sort(result.begin(), result.end(), compareDistance);
        std::sort(result.begin(), result.end(), compareFrequence);
        std::sort(result.begin(), result.end(), compareLexi);
        
        std::cout << "[";
        size_t i = 0;
        size_t size = result.size();
        for (auto w : result) {
            std::cout << "{\"word\":\"" << w.str << "\",\"freq\":" << w.freq << ",\"distance\":" << w.distance << "}";
            if (i+1 < size)
                std::cout << ",";
            i++;
        }
        std::cout << "]" << std::endl;
    }
    return SUCCESS;
}