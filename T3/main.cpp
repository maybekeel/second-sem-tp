#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <limits>
#include <string>
#include <functional>
#include <map>
#include "commands.hpp"
#include "figures.hpp"
#include "iomessages.hpp"

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "Bad args\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "File is not open\n";
    return 1;
  }
  using istreamIter_t = std::istream_iterator< ivlicheva::Polygon >;
  std::vector< ivlicheva::Polygon > polygons;
  while (!file.eof())
  {
    file.clear();
    std::copy(istreamIter_t(file), istreamIter_t(), std::back_inserter(polygons));
    if (!file)
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  file.close();

  ivlicheva::Commands commands(polygons, std::cin, std::cout);
  using command_t = std::function< bool(void) >;
  std::map< std::string, command_t > mapOfCommands(
   {
     {"AREA", std::bind(&ivlicheva::Commands::getArea, std::ref(commands))},
     {"MAX", std::bind(&ivlicheva::Commands::getMax, std::ref(commands))},
     {"MIN", std::bind(&ivlicheva::Commands::getMin, std::ref(commands))},
     {"COUNT", std::bind(&ivlicheva::Commands::getCount, std::ref(commands))},
     {"RECTS", std::bind(&ivlicheva::Commands::getRects, std::ref(commands))},
     {"RIGHTSHAPES", std::bind(&ivlicheva::Commands::getRightShapes, std::ref(commands))}
   });
  while (!std::cin.eof())
  {
    std::string nameOfCommand = "";
    std::cin >> nameOfCommand;
    if (!nameOfCommand.empty())
    {
      auto commandIter = mapOfCommands.find(nameOfCommand);
      if (commandIter == mapOfCommands.end() || !commandIter->second())
      {
        ivlicheva::outputMessageError(std::cout);
        std::cin.clear();
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
    }
  }
  return 0;
}
