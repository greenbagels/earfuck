//standard library headers
#include <deque>
#include <iostream>
#include <string>
//system headers
//local headers
#include "program.h"

Program::Program(std::string &raw_instructions, std::string &raw_stdin)
{
   instructions = std::deque<unsigned char>(raw_instructions.begin(), raw_instructions.end());
   stdin_deque = std::deque<unsigned char>(raw_stdin.begin(), raw_stdin.end());
   parse_instructions();
}

/*
template <typename T>
int Program::input_container(T& dest_container, const char* msg) //TODO: change to accept file input as well
{
  std::string temp;
  std::cout << msg << '\n';
  std::getline(std::cin, temp);
  dest_container = T(temp.begin(), temp.end());
  return 0;
}
*/

int Program::parse_instructions()
{
  //TODO: Remove quick-and-dirty skeleton version of the program model
  //TODO: Possibly break this function down into smaller ones
  for(auto i = instructions.begin(); i != instructions.end(); ++i)
  {
    switch(*i)
    {
      case '<':
        bf_memory.dec_vec();
        break;
      case '>':
        bf_memory.inc_vec();
        break;
      case '+':
        bf_memory.inc_val();
        break;
      case '-':
        bf_memory.dec_val();
        break;
      case ',':
        bf_memory.get_byte() = stdin_deque.front();
        stdin_deque.pop_front(); //We're tearing straight through the stdin, kind of like https://xkcd.com/205/
        break;
      case '.':
        std::cout << bf_memory.get_byte();
        break;
      case '[':
        //TODO: change the bracket handling to a more elegant way without the need for post-logic inc/dec
        /*we could change this to a while loop to catch subsequent loops, but I think that breaks the 
          one-instruction-per-iteration philosophy of the current program design.*/
        if(!bf_memory.get_byte())
        {
          std::vector<unsigned char> bracket_lifo;
          do {
           switch(*i)
            {
              case '[':
              bracket_lifo.push_back(*i);
              break;
              case ']':
              bracket_lifo.pop_back();
              break;
              default:
              break;
            }
            if (i == instructions.end())
            {
              std::cout << "\nAttempted to increment an end iterator!\n";
              exit(1);
            }
            ++i;
          } while (!bracket_lifo.empty());
        --i;
        }
        break;
      case ']':
        if(bf_memory.get_byte())
        {
          std::vector<unsigned int> bracket_lifo;
          do {
            switch(*i)
            {
              case ']':
              bracket_lifo.push_back(*i);
              break;
              case '[':
              bracket_lifo.pop_back();
              break;
              default:
              break;
            }
            if (i == instructions.begin())
            {
              std::cout << "\nAttempted to decrement a beginning iterator!\n";
              exit(1);
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
