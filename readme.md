# GLFX

Simple OpenGL ES2 C++ wrapper and demo app.

Renders 2D sprite batches.

## Dependencies

glew, SDL, glm

glew and SDL libs and headers will need to be installed for your system.

Linux/Debian installation:

	$ sudo apt-get install libglew-dev libsdl2-dev libsdl2-image-dev

Install glm by copying the `glm` subdirectory from the [glm repo](https://github.com/g-truc/glm) into `deps/glm`

## VSCode Setup

Make a copy of `.vscode/c_cpp_properties.example.json` to `.vscode/c_cpp_properties.json` and make any necessary edits.

## Build & Run

	$ make
	$ ./dist/glsprite

### CLI Options

	-fs Fullscreen
	-db Use double-buffering (default)
	-sb Use single-buffering
	-sz Specify window or screen size eg: -sz 1920x1080

If using fullscreen, the app will attempt to determine display size. For some (hopefully rare) OS/hardware/driver combinations this may not work and you'll need to provide screen dimensions manually.
