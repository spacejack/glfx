#include "config.hpp"

using namespace std;

namespace Config {

std::string basedir("./");

}

void Config::setBasedir (const char* str) {
	string exePath(str);
	Config::basedir = exePath.substr(0, exePath.find_last_of("/"));
	printf("Configured basedir to: '%s'\n", Config::basedir.c_str());
}
