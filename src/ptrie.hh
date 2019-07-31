#pragma once

#ifndef PTRIE_HH
#define PTRIE_HH

#include <memory>
#include <string.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <stack> 
#include <boost/algorithm/string.hpp> 

/**
  *
  * Node class:
  *
  * Represent a node of Patricia trie, composed of:
  * a map of children, a boolean to represent if the node have an index in the 
  * letter list, a frequency = 0 if it is not a word and a pair of index is asindex = true. 
  */
class Node {
    public:
        std::map<char,std::shared_ptr<Node>> children;
        bool asindex = false;
        Node(int freq);
        ~Node();

        /**
          * setFreq
          *
          * Set the frequency of a node
          */
        void setFreq(int freq);

        /** 
          * getFreq
          *
          * Return the frequency of the node
          */
        int getFreq();

        /**
          *setIndex
          *
          * Set the index of a node
          */
        void setIndex(std::pair<int, int> ind);
 
        /** 
          * getIndex
          *
          * Return the index of the node
          */
        std::pair<int, int> getIndex();
    
    private:
        int frequency;
        std::pair<int, int> index;
};

/**
  *splitline
  *
  * Split a line depending of a space or a tabulation
  */
std::vector<std::string> splitline(std::string line);

/**
  * itoa
  *
  * convert a string to an int
  */
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
        void deSerialize(const std::string& str);
    private:
        std::map<char,std::shared_ptr<Node>> root;
        std::vector<char> letter_list;
};

#endif
