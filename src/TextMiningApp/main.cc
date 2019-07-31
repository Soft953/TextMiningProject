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

/*
void Ptrie::print_rec(std::string word, std::shared_ptr<Node> node){
    for(auto const& [key, val] : node->children){
        std::string cpy = word;
        cpy += key;
        if(val->getFreq() > 0)
            std::cout << cpy << std::endl;
        if(val->children.size() >= 1)
            print_rec(cpy, val); 
    }
}

void Ptrie::print_ptrie(){
    for(auto const& [key, val] : this->root){
        std::string word = "";
        word += key;
        if(val->getFreq() > 0)
            std::cout << word << std::endl;
        if(val->children.size() >= 1)
            print_rec(word, val);
    }
}
*/

struct Word
{
    std::string str;
    int freq;
    int distance;
};


std::vector<Word> result;

// Sort by distance
bool compareDistance(Word e1, Word e2) {
    return (e1.distance < e2.distance);
}

// Sort by frequence
bool compareFrequence(Word e1, Word e2) {
    return (e1.freq > e2.freq);
}

// Sort by frequence
bool compareLexi(Word e1, Word e2) {
    return e1.str.compare(e2.str);
} 

void findWordWithDistanceRec(std::string word, std::shared_ptr<Node> node, std::string str, int distance){
    for(auto const& [key, val] : node->children){
        std::string cpy = word;
        cpy += key;
        if(val->getFreq() > 0) {
            int d = DamereauLevenshtein().distance(str, cpy);
            if (d <= distance) {
                result.push_back({cpy, val->getFreq(), d});
            }
        }
        if(val->children.size() >= 1)
            findWordWithDistanceRec(cpy, val, str, distance);
    }
}


void findWordWithDistance(Ptrie p, std::string str, int distance) {
    for(auto const& [key, val] : p.root){
        std::string word = "";
        word += key;
        if(val->getFreq() > 0) {
            int d = DamereauLevenshtein().distance(str, word);
            if (d <= distance) {
                result.push_back({word, val->getFreq(), d});
            }

        }
        if(val->children.size() >= 1)
            findWordWithDistanceRec(word, val, str, distance);
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
    //int cpt=0;

    Ptrie p;
    while(std::getline(inFile, line)){
        p.deSerialize(line);
    }
    findWordWithDistance(p, "test", 1);

    std::sort(result.begin(), result.end(), compareDistance);
    std::sort(result.begin(), result.end(), compareFrequence);
    //std::sort(result.begin(), result.end(), compareLexi);

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
    return SUCCESS;
}
