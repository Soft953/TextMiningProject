#include "ptrie.hh"

Node::Node(int freq){
    //this->children = std::map<char, std::unique_ptr<Node>> {};
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
    //this->root = std::map<char, std::unique_ptr<Node>> {};
}

Ptrie::~Ptrie(){}

std::vector<char*> splitline(char* line){
    int size = strlen(line);
    std::vector<char*> res;
    char* tmp;
    char* tmp2;
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

int itoa(char* str){
    int size = strlen(str);
    int res=0;
    for(auto i = 0; i<size; i++){
        res*=10;
        int tmp = (int)str[i] - 48;
        res +=tmp;
    }
    return res;
}

void Ptrie::build(char* path){

    std::ifstream inFile;
    inFile.open(path);
    if(!inFile){
        std::cerr << "Unable to open file" << std::endl;
        exit(1);
    }
    char line[128];
    while(inFile.getline(line, sizeof(line))){
        std::vector<char*> split = splitline(line);
        char* word = split[0];
        int size = strlen(word);
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

int main(){
    Ptrie p;

    p.build((char*)"test.txt");
    return 0;
}
