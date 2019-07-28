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
        std::map<char,std::unique_ptr<Node>> children;
        Node(int freq);
        ~Node();
        void setFreq(int freq);
        int getFreq();
    
    private:
        int frequency;
};

std::vector<char*> splitline(char* line);
int itoa(char* str);

class Ptrie {
    public:
        Ptrie();
        ~Ptrie();
        void build(char* path);
    private:
        std::map<char,std::unique_ptr<Node>> root;
};

#endif
