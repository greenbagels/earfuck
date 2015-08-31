#include <deque>
#include <iostream>
#include <string>
#include "brainfuck.h"

template <typename T>
int input_container(T& dest_container, const char* msg) //TODO: change to accept file input as well
{
  std::string temp;
  std::cout << msg << '\n';
  std::getline(std::cin, temp);
  dest_container = T(temp.begin(), temp.end());
  return 0;
}

template <typename T, typename U>
int fetch_user_input(T& instructions, U& stdin_bytes)
{
  input_container(instructions, "Please enter the brainfuck program (instructions) to interpret");
  input_container(stdin_bytes, "Please enter the program's stdin (leave blank if none required)");
  return 0;
}

template <typename T, typename U>
int parse_instructions(T& instructions, U& stdin_bytes)
{
  //TODO: Remove quick-and-dirty skeleton version of the program model
  Brainfuck bf_instance;
  for(auto i = 0u; i < instructions.size(); ++i)
  {
    switch(instructions[i])
    {
      case '<':
        bf_instance.dec_vec();
        break;
      case '>':
        bf_instance.inc_vec();
        break;
      case '+':
        bf_instance.inc_val();
        break;
      case '-':
        bf_instance.dec_val();
        break;
      case ',':
        bf_instance.get_byte() = stdin_bytes.front();
        stdin_bytes.pop_front(); //We're tearing straight through the stdin, kind of like https://xkcd.com/205/
        break;
      case '.':
        std::cout << bf_instance.get_byte();
        break;
      case '[':
        //TODO: change the bracket handling to a more elegant way without the need for post-logic inc/dec
        /*we could change this to a while loop to catch subsequent loops, but I think that breaks the 
          one-instruction-per-iteration philosophy of the current program design.*/
        if(!bf_instance.get_byte())
        {
          std::vector<unsigned int> bracket_lifo;
          do {
           switch(instructions[i])
            {
              case '[':
              bracket_lifo.push_back(i);
              break;
              case ']':
              bracket_lifo.pop_back();
              break;
              default:
              break;
            }
            ++i;
          } while (!bracket_lifo.empty());
        --i;
        }
        break;
      case ']':
        if(bf_instance.get_byte())
        {
          std::vector<unsigned int> bracket_lifo;
          do {
            switch(instructions[i])
            {
              case ']':
              bracket_lifo.push_back(i);
              break;
              case '[':
              bracket_lifo.pop_back();
              break;
              default:
              break;
            }
            --i;
          } while (!bracket_lifo.empty());
        ++i;
        }
        break;
      default:
        break;
    }
  }
  return 0;
}

int load_program()
{
  std::deque<unsigned char> instructions;
  std::deque<unsigned char> stdin_bytes;
  fetch_user_input(instructions, stdin_bytes);
  parse_instructions(instructions, stdin_bytes);
  return 0;
}

int main()
{
  load_program();
  return 0;
}
