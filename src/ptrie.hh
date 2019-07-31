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


class Node {
    public:
        /** 
         * Store children node using map 'character' -> Node
         */
        std::map<char,std::shared_ptr<Node>> children;
        /**
         * 
         * Check if the node contains compressed character in the letter_list used with the Patricia Trie 
         */
        bool asindex = false;

        Node(int freq);
        ~Node();

        void setFreq(int freq);
        int getFreq();

        void setIndex(std::pair<int, int> ind);
        std::pair<int, int> getIndex();
    
    private:
        /**
         * Frequency value, default value = 0 -> not a word
         *                  else              -> word
         */
        int frequency;
        /**
         * Set Index value, used to build the letter_list of the Patricia Trie
         */
        std::pair<int, int> index;
};

std::vector<std::string> splitline(std::string line);
int itoa(std::string str);

class Ptrie {
    public:
        Ptrie();
        ~Ptrie();

        /**
         * 
         * Add a character into the letter_list variable
         * 
         * Used by the compressed node of the Patricia Trie
         */
        void addLetter(char letter);

        /**
         * Build a Trie from a file.
         * 
         * Store each character and frequency
         * 
         * Can be compressed to a Patricia Trie using Ptrie::made_patricia()
         * 
         */
        void build(std::string path);

        /**
         * Recursive function called by Ptrie::made_patricia()
         * 
         */
        void made_rec(std::shared_ptr<Node> node);

        /**
         * 
         * Compress the Trie into a Patricia Trie, remove useless node,
         *  set character into the letter_list. Also set the index on each compressed node.
         */
        void made_patricia();

        /**
         * 
         * Recursive function called by Ptrie::print_ptrie()
         * 
         */
        void print_rec(std::string word, std::shared_ptr<Node> node);

        /**
         * 
         * Display all the word in the Trie (before compression with made_patricia)
         */
        void print_ptrie();

        /**
         * Print all the word contained in the Patricia Trie (after compression with made_patricia)
         */
        void getWords();

        /**
         * Recursive function called by Ptrie::getWords()
         */
        void getWordsRec(std::string word, std::shared_ptr<Node> node);

        /**
         * 
         * Return the serialized version of a Patricia Trie
         */
        std::string serialize();

        /**
         * 
         * Build Patricia Trie from a serialized string
         */
        void deSerialize(const std::string& str);

        /**
         * 
         * Store root node using map 'character' -> Node
         */
        std::map<char,std::shared_ptr<Node>> root;
    private:


        /**
         * 
         * Store compressed character for the Patricia Trie
         */
        std::vector<char> letter_list;
};

#endif
