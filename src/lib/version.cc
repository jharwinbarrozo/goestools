#include "version.h"
#include "version-gen.h"

#include <iostream>

void version(int argc, char** argv) {
  std::string argv0(argv[0]);
  auto pos = argv0.rfind('/');
  if (pos != std::string::npos) {
    argv0 = argv0.substr(pos + 1);
  }

  std::cout
    << argv0
    << " for GK-2A -- " << GIT_COMMIT_HASH
    << " (" << GIT_COMMIT_DATE << ")"
    << std::endl
    << std::endl;
  std::cout
    << "Originally part of goestools written by Pieter Noordhuis\nand contributors (https://github.com/pietern/goestools)"
    << std::endl;
  std::cout
    << "\nModified by sam210723 for compatibility with GEO-KOMPSAT-2A\n(https://github.com/sam210723/goestools)"
    << std::endl;
}
