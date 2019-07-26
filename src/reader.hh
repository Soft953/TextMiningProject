//reader

#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <assert.h>
#include <iostream>

class Reader{
    private:
        static size_t getFilesize(const char* filename);

    public:
        static void readFile(const char *filename);
};