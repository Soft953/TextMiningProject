#include "reader.hh"

size_t Reader::getFilesize(const char* filename) {
    struct stat st;
    stat(filename, &st);
    return st.st_size;
}

void Reader::readFile(const char *filename)
{
    size_t filesize = getFilesize(filename);

    //Open file
    int fd = open(filename, O_RDONLY, 0);
    assert(fd != -1);

    //Execute mmap
    void *mmappedData = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE | MAP_POPULATE, fd, 0);
    assert(mmappedData != MAP_FAILED);


    auto data = static_cast<char*>(mmappedData);

    std::string data_str = std::string(data);

    //std::cout << data_str << std::endl;

    //std::cout << data << std::endl;
    
    //Write the mmapped data to stdout (= FD #1)
    //if ( write(1, mmappedData, filesize) < 0) {
    //    return;
    //}

    //Cleanup
    int rc = munmap(mmappedData, filesize);
    assert(rc == 0);
    close(fd);
}