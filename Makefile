#OBJS specifies which files to compile as part of the project
OBJS = src/glfx/*.cpp src/*.cpp

#CC specifies which compiler we're using
CC = g++
#CC = g++-4.8

#COMPILER_FLAGS specifies the additional compilation options we're using
#COMPILER_FLAGS = -Ideps
#COMPILER_FLAGS = -Ideps -g
COMPILER_FLAGS = -std=c++11 -Ideps

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lGL -lGLEW

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = dist/glsprite

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
