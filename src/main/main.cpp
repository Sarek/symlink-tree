#include <iostream>
#include <string>

#include <boost/program_options.hpp>

#include "traversal.h"

int main(int argc, char** argv) {
  namespace po = boost::program_options;
  using namespace slt;

  std::string original;
  std::string destination;

  po::options_description desc("Allowed options");
  po::positional_options_description positionals;
  positionals.add("original", 1);
  positionals.add("destination", -1);
  desc.add_options()
    ("help", "print a helpful message")
    ("original", po::value<std::string>(&original)->required(), "The original tree to reproduce")
    ("destination", po::value<std::string>(&destination)->required(), "The location where to reproduce the original tree")
  ;
  po::variables_map vm;
  try {
    po::store(po::command_line_parser(argc, argv)
                .options(desc)
                .positional(positionals)
                .run(),
              vm);
    po::notify(vm);
  } catch(po::error_with_option_name& e) {
    std::cout << e.what() << std::endl;
    std::cout << desc << std::endl;
    return 1;
  }

  if(vm.count("help")) {
    std::cout << desc << std::endl;
    return 1;
  }

  std::cout << "Reproducing directory below "
            << original
            << " in path "
            << destination
            << std::endl;

  symlink::traverse(original, [&destination, &original](auto path) {
    std::cout << "Found directory entry: " << path << std::endl;
    symlink::recreate(destination, original, path);
  });
}
