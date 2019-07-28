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

void Node::setIndex(std::pair<int, int> ind){
    this->index = ind;
    this->asindex = true;
}

std::pair<int, int> Node::getIndex(){
    return this->index;
}

Ptrie::Ptrie(){
    //this->root = std::map<std::string, std::unique_ptr<Node>> {};
}

Ptrie::~Ptrie(){}

void Ptrie::addLetter(char letter){
    this->letter_list.push_back(letter);
}

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
    int cpt=0;
    while(std::getline(inFile, line)){
        std::vector<std::string> split = splitline(line);
        std::string word = split[0];
        int size = word.size();
        int freq = itoa(split[1]);
        std::map<char, std::shared_ptr<Node>>::iterator it;
        std::shared_ptr<Node> cp;
        for(auto i = 0; i<size; i++){
            char ind = word[i];
            if(i==0){
                it = this->root.find(ind);
                if(it == this->root.end()){
                    this->root[ind] = std::make_shared<Node>(0);
                    cp = this->root[ind];
                }
                else
                    cp = this->root[ind];
            }
            else if(i==size-1){
                it = cp->children.find(ind);
                if(it == cp->children.end()){
                    cp->children[ind] = std::make_shared<Node>(freq);
                    cp = cp->children[ind];
                }
                else{
                    cp = cp->children[ind];
                    cp->setFreq(freq);
                }
            }
            else{
                it = cp->children.find(ind);
                if(it == cp->children.end()){
                    cp->children[ind] = std::make_shared<Node>(0);
                    cp = cp->children[ind];
                }
                else
                    cp = cp->children[ind];
            }         
        }
        cpt++;
    }
    std::cout << cpt << " words learned." << std::endl;
    inFile.close();
}

void Ptrie::made_rec(std::shared_ptr<Node> node){
    if(node->children.size() == 1){
        int ind = this->letter_list.size();
        if(!node->asindex){
            std::pair<int, int> tmp(ind, 1);
            node->setIndex(tmp);
            this->addLetter(node->children.begin()->first);
            auto acc = node->children.begin()->second;
            node->children = acc->children;
        }
        else{
            std::pair tmp = node->getIndex();
            tmp.second += 1;
            node->setIndex(tmp);
            this->addLetter(node->children.begin()->first);
            auto acc = node->children.begin()->second;
            node->children = acc->children;
        }
        made_rec(node);
    }
    else{
        for(auto [key, val] : node->children)
            made_rec(val);
    }
}

void Ptrie::made_patricia(){
    for(auto [key, val] : this->root){
        made_rec(val);
    }
}

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

int main(){
    Ptrie p;

    p.build("../words.txt");
    //p.print_ptrie();
    p.made_patricia();

    return 0;
}
