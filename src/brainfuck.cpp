#include <algorithm>
#include "brainfuck.h"

Brainfuck::Brainfuck()
{
  memory.resize(30, '\0'); // bf demands that >=30k byte-size, null characters be available
  memory_index = 0; // starting location for the ptr
}

void Brainfuck::inc_vec()
{
  if((memory_index+1) == memory.size())
  {
    memory.resize(memory.size() + growth, '\0');
  }
  ++memory_index;
}

void Brainfuck::dec_vec()
{
  if(memory_index == 0)
  {
    std::vector<unsigned char> temp_vec(memory.size() + growth, '\0');
    std::copy(memory.begin(), memory.end(), temp_vec.begin() + growth);
    memory.swap(temp_vec);
    memory_index = growth;
  }
  --memory_index;
}

void Brainfuck::inc_val()
{
  ++memory[memory_index];
}

void Brainfuck::dec_val()
{
  --memory[memory_index];
}

unsigned char& Brainfuck::get_byte()
{
  return memory[memory_index];
}