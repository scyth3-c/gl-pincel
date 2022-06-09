#include "../headers/graph_gl.h"
#include <GL/glut.h>

int main(int argc, char *argv[])
{
    
    glutInit(&argc, argv);

    Graph tasty;
    
    tasty.entry();

    return 0;
}
