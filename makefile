BIN = $(DIR_BIN)/pincel
DIR_BIN = ./build
DIR_INC = ./sources/headers
DIR_OBJ = ./objects
DIR_MAIN = ./sources/sources

OBJ = $(DIR_OBJ)/main.o $(DIR_OBJ)/graph.o

COMPILER = g++
FLAGS = -std=c++17 -I$(DIR_INC) -lm -lglut -lGL -lGLU 


$(BIN) : $(OBJ)
	@mkdir -p $(DIR_BIN)
	@$(COMPILER) $(OBJ)  $(FLAGS) -o $(BIN)


$(DIR_OBJ)/%.o : $(DIR_MAIN)/%.cpp
	@mkdir -p $(DIR_OBJ)
	@$(COMPILER) -c -MD $(FLAGS) $< -o $@
-include $(DIR_OBJ)/*.d



.PHONY: install clean

install: 
	apt-get install -y freeglut3 freeglut3-dev libglew-dev && apt-get install -y mesa-utils

clean:
	@rm -r $(DIR_BIN) $(DIR_OBJ)