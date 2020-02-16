#include "dir.h"

#include <util/error.h>

#ifdef _WIN32
  #include <shlwapi.h>
#endif

Dir::Dir(const std::string& path)
    : path_(path) {
  dir_ = opendir(path.c_str());

  #ifndef _WIN32
    ASSERT(dir_ != nullptr);
  #endif
}

Dir::~Dir() {
  closedir(dir_);
}

std::vector<std::string> Dir::matchFiles(const std::string& pattern) {
  std::vector<std::string> result;
  struct dirent *ent;
  while ((ent = readdir(dir_)) != NULL) {
    #ifdef _WIN32
      if (PathMatchSpecA(ent->d_name, pattern.c_str())) {
        result.push_back(path_ + "/" + std::string(ent->d_name));
      }
    #else
      if (fnmatch(pattern.c_str(), ent->d_name, 0) == 0) {
        result.push_back(path_ + "/" + std::string(ent->d_name));
      }
    #endif
  }
  return result;
}
