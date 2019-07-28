#pragma once

#ifndef PTRIE_HH
#define PTRIE_HH

#include <memory>
#include <string.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <boost/algorithm/string.hpp> 


class Node {
    public:
        std::map<char,std::shared_ptr<Node>> children;
        bool asindex = false;
        Node(int freq);
        ~Node();
        void setFreq(int freq);
        int getFreq();
        void setIndex(std::pair<int, int> ind);
        std::pair<int, int> getIndex();
    
    private:
        int frequency;
        std::pair<int, int> index;
};

std::vector<std::string> splitline(std::string line);
int itoa(std::string str);

class Ptrie {
    public:
        Ptrie();
        ~Ptrie();
        void addLetter(char letter);
        void build(std::string path);
        void made_rec(std::shared_ptr<Node> node);
        void made_patricia();
        void print_rec(std::string word, std::shared_ptr<Node> node);
        void print_ptrie();
        std::string serialize();
        void deSerialize(std::string str);
    private:
        std::map<char,std::shared_ptr<Node>> root;
        std::vector<char> letter_list;
};

#endif
