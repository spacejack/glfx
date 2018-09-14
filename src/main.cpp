#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>
#include "glfx/window.hpp"
#include "app.hpp"
#include "config.hpp"

using namespace std;
using namespace GLFX;

static vector<string> split (const string& s, char d) {
	stringstream ss(s);
	string part;
	vector<string> parts;
	while (getline(ss, part, d)) {
		parts.push_back(part);
	}
	return parts;
}

static Window::Options parseOptions (int argc, char* argv[]) {
	Window::Options opts;
	for (int i = 1; i < argc; ++i) {
		string arg = argv[i];
		if (arg == "-fs") {
			opts.fullscreen = true;
		} else if (arg == "-db") {
			opts.doubleBuffer = true;
		} else if (arg == "-sb") {
			opts.singleBuffer = true;
		} else if (arg == "-sz") {
			// size - requires int width & height
			if (i >= argc -1) {
				throw runtime_error("Parameter -sz must be followed by WxH");
			}
			i += 1;
			auto arg2 = argv[i];
			auto wh = split(arg2, 'x');
			if (wh.size() != 2) {
				throw runtime_error("Parameter -sz must be followed by WxH");
			}
			try {
				opts.width = std::stoi(wh[0]);
				opts.height = std::stoi(wh[1]);
			} catch (...) {
				throw runtime_error("-sz WxH parameter: W and H must be integers");
			}
		} else {
			throw runtime_error(string("Unrecognized parameter: ") + arg);
		}
	}
	if (!opts.fullscreen && (opts.width < 1 || opts.height < 1)) {
		opts.width = 640;
		opts.height = 480;
	}
	return opts;
}

int main (int argc, char* argv[]) {
	try {
		Config::setBasedir(argv[0]);
		auto options = parseOptions(argc, argv);
		auto window = Window("GLFX", options);
		App app(window);
		app.run();
	} catch (std::exception& ex) {
		fprintf(stderr, "%s\n", ex.what());
		return 1;
	} catch (...) {
		fprintf(stderr, "An unknown exception occurred\n");
		return 1;
	}
	printf("Exiting OK\n");
	return 0;
}
