//standard library headers
#include <fstream>
#include <iostream>
#include <stdexcept>
//system headers
#include <getopt.h> /* needed for getopt_long - GNU EXTENSION, NOT POSIX! */
//local headers
#include "program.h"

std::string slurp_file(std::string file_name)
{
  std::ifstream file_istream(file_name, std::ios_base::binary | std::ios_base::ate);
  if(file_istream.is_open())
  {
    std::string data(file_istream.tellg(), '\0');
    file_istream.seekg(0, std::ios_base::beg);
    file_istream.read(&data[0], data.size());
    file_istream.close();
    return data;
  }
  throw(std::ios_base::failure("File: " + file_name + " failed to open!"));
}

std::string get_string(int file_flag, std::string file_name = "")
{
  if(file_flag && !(file_name.empty()))
  { //let's yank the contents of the file if a true file name is given
    std::string dest_string;
    try
    {
      dest_string = slurp_file(file_name);
      return dest_string;
    }
    catch(std::ios_base::failure except)
    {
            std::cout << "Exception caught: " << except.what() << '\n';
    }
  }
  //it's not truly the file name, it's actually the string!
  return std::string(file_name);
}

int main(int argc, char* argv[])
{
  //  example program:
  //  ./program INSTRUCTIONS STDIN
  struct option long_opts[]
  { // do not require arguments so that option means file, no option means stdin
    { "instruction-file", no_argument, nullptr, 'i' },
    { "stdin-file", no_argument, nullptr, 's' },
    { 0, 0, 0, 0 }
  };
  int c = {0};
  int opt_index = {0};
  int instruct_flag = {0};
  int stdin_flag = {0};
  try
  {
    while ((c = getopt_long(argc, argv, "is", long_opts, &opt_index)) != -1)
    {
      switch(c)
      {
        case 'i':
          instruct_flag = 1;
          break;
        case 's':
          stdin_flag = 1;
          break;
        case '?':
          break;
        default:
          throw(std::invalid_argument("Erronous argument " + std::string(1, optopt) + " detected"));
      }
    }
    if(argv[optind] == nullptr)
    {
      throw(std::invalid_argument("Usage: ./bfinterpreter [options] instructions [stdin]\n"));
    }
  }
  catch(std::invalid_argument except)
  {
    std::cerr << "Exception caught: " << except.what() << '\n';
    exit(1);
  }
  std::string instruct_string;
  std::string stdin_string;
  instruct_string = get_string(instruct_flag, argv[optind]);
  if (argv[optind+1] != nullptr)
  {
    stdin_string = get_string(stdin_flag, argv[optind+1]);
  }
  Program program_instance(instruct_string, stdin_string);
  return 0;
}


