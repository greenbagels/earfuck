#ifndef MEMORY_H
#define MEMORY_H

#include <deque>
#include <vector>

class Memory
{
  public:
    Memory();
    void inc_vec();  // equivalent to >
    void dec_vec();  // equivalent to <
    void inc_val();  // equivalent to +
    void dec_val();  // equivalent to -
    unsigned char& get_byte(); // used for , or .
    unsigned char& get_byte(unsigned int);
    std::vector<unsigned char>::size_type current_index();

  private:
    const std::size_t growth = 500u; // our standard growth size for if we overflow
    std::vector<unsigned char> memory; // our address space
    std::vector<unsigned char>::size_type memory_index; // pointer to our current byte
};

#endif //MEMORY_H
