//reader

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

class Reader{
    private:
        static size_t getFilesize(const char* filename);

    public:
        static std::tuple<void*, int> readFile(const char *filename);
        static void clearMmappedData(const char* filename, void* mmappedData, int fd);
};