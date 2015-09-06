#ifndef PROGRAM_H
#define PROGRAM_H

//standard library headers
#include <deque>
#include <string>
//system headers
//local headers
#include "memory.h"

class Program
{
  public:
    Program(std::string&, std::string&);
    int parse_instructions();
  private:
    std::deque<unsigned char> instructions;
    std::deque<unsigned char> stdin_deque;
    Memory bf_memory;
};

#endif // PROGRAM_H
