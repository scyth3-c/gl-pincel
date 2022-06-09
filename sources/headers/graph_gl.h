#ifndef _GRAPH_H
#define _GRAPH_H


#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>

#include <vector>
using std::vector;

struct point_t {
    point_t(int _x, int _y) : x(_x), y(_y) {}
    int x{0};
    int y{0};
    bool estado = false;
};  


class Graph {

private:

    static GLint Win;
    GLint ancho{800};
    static GLint alto;
    GLint wPos[2]{50,50};
    const char* wName{"pincel"};
    static std::string analog_types[4];
    static GLint fps;

    GLclampf wColor[4]{0.0f, 0.5f, 0.5f, 1};
    GLfloat pSize{10}, wSize{10};


    static vector<point_t*> puntos;
    static vector<int > pila_puntos;
    static vector<GLenum> styles;
    
    static vector<GLboolean> flags;

    static vector<point_t*> buffer_uno;
    static vector<point_t*> buffer_dos;
    static vector<point_t*> buffer_tres;

    static vector<vector<point_t*>> _buffers;



    static vector<vector<GLclampf>> bColors;
    static vector<vector<GLclampf>> fColors;
    static vector<GLclampf> temp_color;

    static GLint sit;
    static GLint bSit;
    


public:

 Graph();

static void display();
static void keyboard(unsigned char, int,int);
static void mouse(int,int,int,int);
static void mouse_move(int,int);
static void idle();

void inicio();
void configDisplay();
void entry();
void light();
static void menu(std::string, size_t);


static void point(int,int);
static void show();
static void showBuffer(int);
static void bufferify();
static void clearBuffer();
static void textify(std::string, int, int);

};


#endif // ! _GRAPH_H