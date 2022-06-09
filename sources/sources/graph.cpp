#include "../headers/graph_gl.h"

GLint  Graph:: fps   =     30;
GLint  Graph:: alto  =     600;
GLint  Graph:: sit   =     0;
GLint  Graph:: bSit  =     0;


GLenum           Graph::styles[4]           = {GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP,GL_POLYGON};
std::string      Graph::analog_types[4]     = {"Points *", "Lines |", "Line Loop / ", "Polygon /\\"};


vector<point_t*>    Graph::puntos          = {};


vector<GLboolean>           Graph::flags        = {false};
vector<vector<point_t*>>    Graph::_buffers     = { {0,0} };
vector<GLclampf>            Graph::temp_color   = {};

vector<vector<GLclampf>> Graph::bColors = {
  {1.0f, 0.2f, 0.1f, 1},
  {1.0f, 1.0f, 0.0f, 1},
  {1.0f, 0.0f, 1.0f, 1},
  {0.0f, 0.5f, 0.5f, 1}
};


GLint Graph::Win = 0;
Graph::Graph() {}


void Graph::entry() {

     inicio();
     configDisplay();
     light();
     
     glutMainLoop();
}

void Graph::inicio() {
    
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(ancho, alto);
    glutInitWindowPosition(wPos[0], wPos[1]);
    Win = glutCreateWindow(wName);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(mouse_move);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);

}


void Graph::configDisplay() {

    glClearColor(wColor[0], wColor[1], wColor[2],wColor[3]);
    
    glEnable(GL_DEPTH);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    
    glOrtho(0,800,0,600,-1,1);

    glPointSize(pSize);
    glLineWidth(wSize);

    glutSetWindow(Win);

}


void Graph::display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f( 1.0, 1.0, 1.0 );
    glPushMatrix();
    if(!puntos.empty()) show();
    glPopMatrix();
    


    for (size_t _iterator = 0; _iterator < _buffers.size(); _iterator++)
    {
        if(flags[_iterator]==true) {
            if(!_buffers[_iterator].empty())
            { 
                glPushMatrix();
                  showBuffer(_iterator);
                glPopMatrix();
            }
        }
    }
    
    glEnd();

    menu(analog_types[sit], _buffers.size());
    
    glutSwapBuffers();
}


void Graph::mouse(int boton, int estado, int posx, int posy) {

    if ((estado == GLUT_DOWN) && (boton == GLUT_LEFT_BUTTON)) { 
        point(posx,posy);
    } else if((estado == GLUT_DOWN) && (boton == GLUT_RIGHT_BUTTON)) {
        bufferify();
    }
}

void Graph::mouse_move(int x, int y) {
    point(x,y);
}

void Graph::keyboard(unsigned char key, int x, int y) {
  switch (key)
  {
  //change
  case 'a':  
      sit++;
      if(sit > 3) sit = 0;
      break;
  //back
  case 's':
     if(!puntos.empty()) puntos.pop_back();
    break;
 
 //clear
  case 'd':

      if(!puntos.empty()) puntos.clear();
      clearBuffer();

    break;
  case 'g':
    if(_buffers.size()>=0) _buffers.pop_back();
    break;
  case '1':
  
    temp_color = bColors[bSit];
    glClearColor(temp_color[0], temp_color[1], temp_color[2], temp_color[3]);

    if(bSit >= 3) {
        bSit = 0 ;
    } else{bSit++;} 

    break;


  default:
      break;
  }
}


void Graph::idle() {

	if ((GLUT_ELAPSED_TIME - (0 + Graph::fps) > 0)) {

		glutPostRedisplay();
	}
}


void Graph::light() {

 GLfloat fv[4] = {-1.0f, 2.0f, 3.0f, 0};
 glLightfv(GL_LIGHT0, GL_POSITION, fv);


 GLfloat md[4] = {0.3f,0.8f,0.8f, 1};
 glMaterialfv(GL_FRONT, GL_DIFFUSE, md);


 GLfloat me[4] = {0.f,0.9f,0.6f,1};
 glMaterialfv(GL_FRONT, GL_SPECULAR, me);
 

 GLfloat ms[4] = {0.9f,0.3f,3,0};
 glMaterialfv(GL_FRONT, GL_SHININESS, ms);

 
 GLfloat mem[4] = {0.5,0.7,0,1};
 glMaterialfv(GL_FRONT, GL_EMISSION, mem);


 GLfloat ma[4] = {0.4,0.2,0.7,1};
 glMaterialfv(GL_FRONT, GL_AMBIENT, ma);


}

void Graph::point(int X, int Y) 
{
 auto *temp = new point_t(X,alto-Y);
 puntos.emplace_back(std::move(temp));
}

void Graph::show() {
    glBegin(styles[sit]);
    for (auto &it : puntos)
    {   
         glVertex2d(it->x, it->y);
         it->estado=true;
    }
    glEnd();
}


void Graph::showBuffer(int _it) {
    glBegin(styles[sit]);
    for (auto &it : _buffers[_it])
    {   
         glVertex2d(it->x, it->y);
         it->estado=true;
    }
    glEnd();
}


void Graph::bufferify() {

    for (size_t i = 0; i < _buffers.size(); i++)
    {
        if(_buffers[i].empty() && !puntos.empty()) {
            _buffers[i] = puntos;
            puntos.clear();
            flags[i] = true;
            return;
        }
    }

     vector<point_t*> temp;
    _buffers.emplace_back(std::move(temp));
    flags.push_back(false);
}

void Graph::clearBuffer() {
    for (auto &it : _buffers)
    {   
        it.clear();
    }
}

void Graph::textify(std::string texto, int x, int y) {
    glRasterPos2i(x,y);
    for (size_t i = 0; i < texto.length(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)texto[i]);
    }
}

void Graph::menu(std::string type, size_t layers) {

    int general_X = 630;

   glColor3f( 1.0, 1.0, 1.0 );
    textify("Type: "+type, general_X,580);
    textify("layers: "+std::to_string((int)layers),general_X, 550);
    

    textify("Mouse L: draw", general_X, 500);
    textify("Mouse R: new layer",general_X, 480);

    textify("A: change type", general_X, 450);
    textify("S: undo", general_X, 430);
    textify("D: clear all", general_X, 410);

    textify("1: back color", general_X, 370);

}