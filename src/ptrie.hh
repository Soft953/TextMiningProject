#pragma once

#ifndef PTRIE_HH
#define PTRIE_HH

#include <memory>
#include <string.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>


class Node {
    public:
        std::map<char,std::shared_ptr<Node>> children;
        Node(int freq);
        ~Node();
        void setFreq(int freq);
        int getFreq();
    
    private:
        int frequency;
};

std::vector<std::string> splitline(std::string line);
int itoa(std::string str);

class Ptrie {
    public:
        Ptrie();
        ~Ptrie();
        void build(std::string path);
        void print_rec(std::string word, std::shared_ptr<Node> node);
        void print_ptrie();
    private:
        std::map<char,std::shared_ptr<Node>> root;
};

#endif
