#ifndef APP_CONFIG_HPP
#define APP_CONFIG_CPP

#include <string>

namespace Config {

const char PATHSEP = '/';

extern std::string basedir;
void setBasedir (const char* exePath);

}

#endif
