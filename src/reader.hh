#pragma once

#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <assert.h>
#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp> 
#include <tuple>

/**
 *  Reader Class
 * 
 *  All method used to simplifly mmap
 */
class Reader{
    private:
        /**
         *  getFileSize
         * 
         *  Return the size of the file "filename"
         */
        static size_t getFilesize(const char* filename);

    public:
        /**
         * 
         * readFile:
         * 
         * mmap a file and return the mmapped data and the file descriptor 
         */
        static std::tuple<void*, int> readFile(const char *filename);

        /**
         * clearMmappedData
         * 
         * unmmap a file and close the file descriptor 
         */
        static void clearMmappedData(const char* filename, void* mmappedData, int fd);
};

    /*
    auto [mmappedData, fd] = Reader().readFile(argv[1]);
    
    auto data = static_cast<char*>(mmappedData);
    std::string data_str = std::string(data);
    */