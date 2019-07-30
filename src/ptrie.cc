#include "ptrie.hh"
#define UNUSED(expr) do { (void)(expr); } while (0)


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

void Ptrie::build(std::string path) {

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
    //inFile.close();
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
    } else {
        for(auto [key, val] : node->children) {
            UNUSED(key);
            made_rec(val);
        }
    }
}

void Ptrie::made_patricia(){
    for(auto [key, val] : this->root){
        UNUSED(key);
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

void serializeRec(std::string& res, const std::shared_ptr<Node>& node) {
    auto const& size = node->children.size();
    std::size_t i = 0;
    res += " ";
    for(auto const& [key, val] : node->children) {
        res += key;
        if(val->getFreq() > 0)
            res += "-" + std::to_string(val->getFreq());
        if(val->children.size() >= 1)
            serializeRec(res, val);
        if (i + 1 < size)
            res += " ";
        i++;
    }
    res += " )";
}

// 1 2 5 ) 6 ) ) 3 ) 4 7 ) 8 9 ) ) ) )

std::string Ptrie::serialize() {
    std::string res = std::string("");
    auto const& size = this->root.size();
    std::size_t i = 0;
    for(auto const& [key, val] : this->root) {
        res += key;
        if(val->getFreq() > 0)
            res += "-" + std::to_string(val->getFreq());
        if(val->children.size() >= 1)
            serializeRec(res, val);
        if (i + 1 < size)
            res += " ";
        i++;
    }
    return res;
}

/*
void deSerializeStack(const std::vector<std::string>& splitted_string, std::shared_ptr<std::map<char,std::shared_ptr<Node>>> root) {
    std::stack<std::shared_ptr<std::map<char,std::shared_ptr<Node>>>> stack;
    stack.push(root);
    //int back_to_root = 0;
    //root['z'] = std::make_shared<Node>(0);
    for (auto const& str : splitted_string) {
        if (str.size() == 1) {
            if (!str.compare(")")) {
                //if (stack.size() == 1)
                //    root = stack.top();
                stack.pop();
            }
            else {
                if (back_to_root) {
                    node->children[str[0]] = std::make_shared<Node>(0);
                    stack.push(node->children[str[0]]);
                    back_to_root = 0;
                } else {
                //stack.top()->children[str[0]] = std::make_shared<Node>(0);
                //stack.push(stack.top()->children[str[0]]);
                //}
                std::map<char,std::shared_ptr<Node>> m = *stack.top();
                m[str[0]] = std::make_shared<Node>(0);
                stack.push(std::make_shared<std::map<char,std::shared_ptr<Node>>>(m[str[0]]->children));
            }
        }
        else {
            std::vector<std::string> tmp;
            boost::split(tmp, str, boost::is_any_of("-"));
            const char c = tmp[0][0];
            const int freq = std::stoi(tmp[1]);
            if (back_to_root) {
                stack.top()->children[c] = std::make_shared<Node>(freq);
                stack.push(stack.top()->children[c]);
                back_to_root = 0;               
            }
            stack.top()->children[c] = std::make_shared<Node>(freq);
            stack.push(stack.top()->children[c]);
            
            std::map<char,std::shared_ptr<Node>> m = *stack.top();
            m[c] = std::make_shared<Node>(freq);
            stack.push(std::make_shared<std::map<char,std::shared_ptr<Node>>>(m[c]->children));
        }
    } 
}
//cp->children[ind] = std::make_shared<Node>(freq);
*/

void Ptrie::deSerialize(const std::string& str) {
    std::vector<std::string> tmp; 
    boost::split(tmp, str, boost::is_any_of(" "));
    //deSerializeStack(tmp, std::make_shared<std::map<char,std::shared_ptr<Node>>>(this->root));
    //std::size_t i = 0;
    std::stack<std::shared_ptr<std::map<char,std::shared_ptr<Node>>>> stack;
    //auto save = std::make_shared<std::map<char,std::shared_ptr<Node>>>(this->root);
    stack.push(std::make_shared<std::map<char,std::shared_ptr<Node>>>(this->root));
    auto save = stack.top();
    //(*stack.top())['z'] = std::make_shared<Node>(0);
    for (auto const& str : tmp) {
        if (str.size() == 1) {
            if (!str.compare(")")) {
                stack.pop();
            }
            else {
                (*stack.top())[str[0]] = std::make_shared<Node>(0);
                auto node = (*stack.top())[str[0]];
                auto sharedptr_children = std::make_shared<std::map<char,std::shared_ptr<Node>>>(node->children);
                (node->children) = *sharedptr_children;

                //auto sharedptr_children = std::make_shared<std::map<char,std::shared_ptr<Node>>>((*stack.top())[str[0]]->children);
                
                stack.push(sharedptr_children);
            }
        }
        else {
            std::vector<std::string> tmp;
            boost::split(tmp, str, boost::is_any_of("-"));
            const char c = tmp[0][0];
            const int freq = std::stoi(tmp[1]);
            (*stack.top())[c] = std::make_shared<Node>(freq);
            auto node = (*stack.top())[c];
            auto sharedptr_children = std::make_shared<std::map<char,std::shared_ptr<Node>>>((*stack.top())[c]->children);
            //(*stack.top())[str[0]]->children = *sharedptr_children;
            stack.push(sharedptr_children);

            
            
            
            //auto sharedptr_children = std::make_shared<std::map<char,std::shared_ptr<Node>>>((*stack.top())[c]->children);
            //stack.push(std::make_shared<std::map<char,std::shared_ptr<Node>>>((*stack.top())[c]->children));
        }
    }
    this->root = *save;
    /*
    std::stack<std::map<char,std::shared_ptr<Node>>> stack;
    stack.push(this->root);
    //auto saveref = &stack.top();
    for (auto const& str : tmp) {
        if (str.size() == 1) {
            if (!str.compare(")")) {
                stack.pop();
            }
            else {
                stack.top()[str[0]]= std::make_shared<Node>(0);
                stack.push(stack.top()[str[0]]->children);
            }
        }
        else {
            std::vector<std::string> tmp;
            boost::split(tmp, str, boost::is_any_of("-"));
            const char c = tmp[0][0];
            const int freq = std::stoi(tmp[1]);
            stack.top()[c] = std::make_shared<Node>(freq);
            stack.push(stack.top()[c]->children);
        }
    }
    while (stack.size() != 2) {
        stack.pop();
    }
    this->root = stack.top();
    auto test = this->root['a'];
    */
}
/*
int main(int argc, char* argv[]){
    if (argc < 2) {
        return -1;
    }
    
    Ptrie p;

    p.build(argv[1]);
    auto serialize_str = p.serialize();
    std::cout << serialize_str << std::endl;
    p.made_patricia();
    std::cout << serialize_str << std::endl;
    //p.print_ptrie();
    //auto tmp = p.serialize();
    
    Ptrie p2;

    p2.deSerialize(serialize_str);
    auto serialize_str2 = p2.serialize();
    std::cout << serialize_str2 << std::endl;

    p2.print_ptrie();

    //p.print_ptrie();
    return 0;
}
*/