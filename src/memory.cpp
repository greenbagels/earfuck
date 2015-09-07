//standard library headers
#include <algorithm>
//system headers
//local headers
#include "memory.h"

Memory::Memory()
{
  memory.resize(30000, '\0'); // bf demands that >=30k byte-size, null characters be available
  memory_index = 0; // starting location for the ptr
}

void Memory::inc_vec()
{
  if((memory_index+1) == memory.size())
  {
    memory.resize(memory.size() + growth, '\0');
  }
  ++memory_index;
}

void Memory::dec_vec()
{
  if(memory_index == 0)
  {
    std::vector<signed char> temp_vec(memory.size() + growth, '\0');
    std::copy(memory.begin(), memory.end(), temp_vec.begin() + growth);
    memory.swap(temp_vec);
    memory_index = growth;
  }
  --memory_index;
}

void Memory::inc_val()
{
  ++memory[memory_index];
}

void Memory::dec_val()
{
  --memory[memory_index];
}

signed char& Memory::get_byte()
{
  return memory[memory_index];
}

signed char& Memory::get_byte(unsigned int index)
{
  return memory[index];
}

std::vector<signed char>::size_type Memory::current_index()
{
  return memory_index;
}
