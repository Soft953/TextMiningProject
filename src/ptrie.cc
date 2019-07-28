#include "ptrie.hh"

Node::Node(int freq){
    //this->children = std::map<std::string, std::unique_ptr<Node>> {};
    this->frequency = freq;
}

Node::~Node(){}

void Node::setFreq(int freq){
    this->frequency = freq;
}

int Node::getFreq(){
    return this->frequency;
}

Ptrie::Ptrie(){
    //this->root = std::map<std::string, std::unique_ptr<Node>> {};
}

Ptrie::~Ptrie(){}

std::vector<std::string> splitline(std::string line){
    int size = line.size();
    std::vector<std::string> res;
    std::string tmp;
    std::string tmp2;
    bool acc = false;
    for(auto i=0; i<size; i++){
        if( (line[i] == ' ' && acc == false) || (line[i] == '\t' && acc == false) ) {
            acc = true;
            res.push_back(tmp);
        }
        else if( (line[i] == ' ' && acc == true) || (line[i] == '\t' && acc == true ) )
            continue;
        else if(acc==false){
            tmp += line[i];
        }
        else if(acc==true){
            tmp2 += line[i];
            if(i==size-1)
                res.push_back(tmp2);
        }
    }
    return res;
}

int itoa(std::string str){
    int size = str.size();
    int res=0;
    for(auto i = 0; i<size; i++){
        res*=10;
        int tmp = (int)str[i] - 48;
        res +=tmp;
    }
    return res;
}

void Ptrie::build(std::string path){

    std::ifstream inFile;
    inFile.open(path);
    if(!inFile){
        std::cerr << "Unable to open file" << std::endl;
        exit(1);
    }
    std::string line;
    while(std::getline(inFile, line)){
        std::vector<std::string> split = splitline(line);
        std::string word = split[0];
        int size = word.size();
        int freq = itoa(split[1]);
        std::map<char, std::unique_ptr<Node>>::iterator it;
        std::unique_ptr<Node> cp;
        for(auto i = 0; i<size; i++){
            char ind = word[i];
            if(i==0){
                it = this->root.find(ind);
                if(it == this->root.end()){
                    //Node* n = new Node(0);
                    //std::unique_ptr<Node> tmp(n);
                    this->root[ind] = std::make_unique<Node>(0);
                    cp = std::make_unique<Node>(this->root[ind]->getFreq());
                }
                else
                    cp = std::make_unique<Node>(this->root[ind]->getFreq());
            }
            else if(i==size-1){
                it = cp->children.find(ind);
                if(it == cp->children.end()){
                    //Node* n = new Node(freq);
                    //std::unique_ptr<Node> tmp(n);
                    cp->children[ind] = std::make_unique<Node>(freq);
                    cp = std::make_unique<Node>(cp->children[ind]->getFreq());
                }
                else{
                    cp = std::make_unique<Node>(cp->children[ind]->getFreq());
                    cp->setFreq(freq);
                }
            }
            else{
                it = cp->children.find(ind);
                if(it == cp->children.end()){
                    //Node* n = new Node(0);
                    //std::unique_ptr<Node> tmp(n);
                    cp->children[ind] = std::make_unique<Node>(0);
                    cp = std::make_unique<Node>(cp->children[ind]->getFreq());
                }
                else
                    cp = std::make_unique<Node>(cp->children[ind]->getFreq());
            }         
        }
    }
    inFile.close();
}

void Ptrie::print_ptrie(){
    for(auto const& [key, val] : this->root){
        std::cout << key;
        auto n = std::make_unique<Node>(val->getFreq());
        for(auto const& [key2, val2] : n->children){
            std::cout << key2 << std::endl;
        }
    }
}

int main(){
    Ptrie p;

    p.build((std::string)"test.txt");
    p.print_ptrie();

    return 0;
}
