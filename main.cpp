#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)


float playerX = 0.3;
float playerZ = 0.7;
float Rotate = 0 ;
bool flag= true;
float CatX=0;
float CatFlag= true;
float ChairX = 0.0;
float ChairZ = 0.0;
float ChairY = 0.0;
float TvX = 0.0;
float TvY = 0.0;
float TvZ = 0.0;
float WallColor1 = 1.0;
float WallColor2 = 1.0;
float WallColor3 = 1.0;
void Timer(int value);





class Vector3f {
public:
    float x, y, z;
   

    Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
        x = _x;
        y = _y;
        z = _z;
    }

    Vector3f operator+(Vector3f &v) {
        return Vector3f(x + v.x, y + v.y, z + v.z);
    }

    Vector3f operator-(Vector3f &v) {
        return Vector3f(x - v.x, y - v.y, z - v.z);
    }

    Vector3f operator*(float n) {
        return Vector3f(x * n, y * n, z * n);
    }

    Vector3f operator/(float n) {
        return Vector3f(x / n, y / n, z / n);
    }

    Vector3f unit() {
        return *this / sqrt(x * x + y * y + z * z);
    }

    Vector3f cross(Vector3f v) {
        return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }
};

class Camera {
public:
    Vector3f eye, center, up;

    Camera(float eyeX = 1.0f, float eyeY = 1.0f, float eyeZ = 1.0f, float centerX = 0.0f, float centerY = 0.0f, float centerZ = 0.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f) {
        eye = Vector3f(eyeX, eyeY, eyeZ);
        center = Vector3f(centerX, centerY, centerZ);
        up = Vector3f(upX, upY, upZ);
    }

    void moveX(float d) {
        Vector3f right = up.cross(center - eye).unit();
        Vector3f rightd=right * d;
        eye = eye + rightd;
        center = center + rightd;
    }

    void moveY(float d) {
        Vector3f upd =up.unit() * d;
        eye = eye + upd;
        center = center + upd;
    }

    void moveZ(float d) {
        Vector3f view = (center - eye).unit();
        Vector3f viewd = view * d;
        eye = eye + viewd;
        center = center + viewd;
    }

    void rotateX(float a) {
        Vector3f view = (center - eye).unit();
        Vector3f right = up.cross(view).unit();
        Vector3f sind = up * sin(DEG2RAD(a));
        view = view * cos(DEG2RAD(a)) + sind;
        up = view.cross(right);
        center = eye + view;
    }

    void rotateY(float a) {
        Vector3f view = (center - eye).unit();
        Vector3f right = up.cross(view).unit();
        Vector3f rsin = right * sin(DEG2RAD(a));
        view = view * cos(DEG2RAD(a)) + rsin;
        right = view.cross(up);
        center = eye + view;
    }

    void look() {
        gluLookAt(
            eye.x, eye.y, eye.z,
            center.x, center.y, center.z,
            up.x, up.y, up.z
        );
    }
    void toplook() {
            gluLookAt(
                eye.x = 0, eye.y = 3, eye.z = -1,
                center.x, center.y, center.z,
                up.x = 0, up.y = 1, up.z = 0
            );
        }
        void frontlook() {
            gluLookAt(
                eye.x = 0, eye.y = 1, eye.z = 2.5,
                center.x, center.y, center.z,
                up.x = 0, up.y = 1, up.z = 0
            );
        }
        void sidelook() {
            gluLookAt(
                eye.x = 3, eye.y = 1, eye.z = 0,
                center.x, center.y, center.z,
                up.x = 0, up.y = 1, up.z = 0
            );
        }

        void mainview() {
            gluLookAt(
                eye.x = 1, eye.y = 1, eye.z = 1,
                center.x, center.y, center.z,
                up.x = 0, up.y = 1, up.z = 0
            );
        }
    
};

Camera camera;

void drawWall(double thickness) {
    glPushMatrix();
    glTranslated(0.6, 0.6 * thickness, 0.6);
    glColor3f(WallColor1, WallColor2,WallColor3);
    glScaled(1.5, thickness, 1.5);
    glutSolidCube(1);
    glPopMatrix();
}
void drawTableLeg(double thick, double len) {
    glPushMatrix();
    glTranslated(0, len / 2, 0);
    glScaled(thick, len, thick);
    glutSolidCube(1.0);
    glPopMatrix();
}
void drawJackPart() {
    glPushMatrix();
    glScaled(0.2, 0.2, 1.0);
    glutSolidSphere(1, 15, 15);
    glPopMatrix();
    glPushMatrix();
    glTranslated(0, 0, 1.2);
    glutSolidSphere(0.2, 15, 15);
    glTranslated(0, 0, -2.4);
    glutSolidSphere(0.2, 15, 15);
    glPopMatrix();
}
void drawJack() {
    glPushMatrix();
    drawJackPart();
    glRotated(90.0, 0, 1, 0);
    drawJackPart();
    glRotated(90.0, 1, 0, 0);
    drawJackPart();
    glPopMatrix();
}


void drawTable(double topWid, double topThick, double legThick, double legLen){
    glPushMatrix();
    glTranslated(0, legLen, 0);
    glColor3f(0.5f, 0.35f, 0.05f);
    glScaled(topWid, topThick, topWid);
    glutSolidCube(1.0);
    glPopMatrix();

    double dist = 0.95*topWid / 2.0 - legThick / 2.0;
    glPushMatrix();
    glTranslated(dist, 0, dist);
    drawTableLeg(legThick, legLen);
    glTranslated(0, 0, -2 * dist);
    drawTableLeg(legThick, legLen);
    glTranslated(-2 * dist, 0, 2 * dist);
    drawTableLeg(legThick, legLen);
    glTranslated(0, 0, -2 * dist);
    drawTableLeg(legThick, legLen);
    
    glPopMatrix();
}


void drawPlayer(float x, float z) {
    glPushMatrix();
    glColor3ub(224, 172, 105);
    glTranslated(x, 0.55, z+0.06);
    glutSolidSphere(0.06, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslated(x, 0.105, z);
    glScaled(0.05, 0.3, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslated(x, 0.105, z + 0.1);
    glScaled(0.05, 0.3, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();
    
    
    
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslated(x, 0.38, z + 0.05);
    glScaled(0.05, 0.25, 0.15);
    glutSolidCube(1.0);
    glPopMatrix();
    
    
}

void drawShelf(){
    
    glPushMatrix();
    glColor3f(0.5f, 0.35f, 0.05f);
    glTranslated(0.0, 0.65,   0.55);
    glRotated(90,0, 0, 0);
    glScaled(0.25, 0.55, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();
    
    
}

void drawCup() {
    glPushMatrix();
    glColor3ub(43, 23, 0);
    glTranslated(0.4, 0.02, 0.695);
    glScaled(1, 0.7, 1);
    glutSolidCube(0.05);
    glPopMatrix();

    glPushMatrix();
    glColor3f(4.0, 2.0, 0.0);
    GLUquadricObj* qobj;
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_FILL);
    glTranslated(0.4, 0.06, 0.695);
    glScaled(0.02, 0.04, 0.02);
    glRotated(-90, 1.0, 0.0, 0.0);
    gluCylinder(qobj, 0.4, 1, 2, 6, 30);
    glPopMatrix();

    glPushMatrix();
    glColor3f(4.0, 2.0, 0.0);
    gluQuadricDrawStyle(qobj, GLU_FILL);
    glTranslated(0.4, 0.035, 0.695);
    glScaled(0.02, 0.05, 0.02);
    glRotated(-90, 1.0, 0.0, 0.0);
    gluCylinder(qobj, 1, 0.4, 0.5, 6, 30);
    glPopMatrix();

    glPushMatrix();
    glColor3f(4.0, 2.0, 0.0);
    glTranslated(0.4, 0.14, 0.695);
    glutSolidSphere(0.02, 8, 8);
    glPopMatrix();

    
    
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslated(0, 0.105, 0);
    glScaled(0.05, 0.3, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();


}


void drawTvStand(){
    
    
    glPushMatrix();
    glColor3f(0.5f, 0.35f, 0.05f);
    glTranslated(0.55, 0.105, 0.0);
    glScaled(0.45, 0.3, 0.22);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.90,0.75,0.00);
    glTranslated(0.69, 0.18, 0.14);
    glScaled(0.17, 0.2, 0.01);
    glutSolidCube(1.0);
    glPopMatrix();
    
    
    glPushMatrix();
    glColor3f(0.90,0.75,0.00);
    glTranslated(0.46, 0.18, 0.14);
    glScaled(0.2, 0.2, 0.01);
    glutSolidCube(1.0);
    glPopMatrix();
    
    
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslated(0.55, 0.35, 0.0);
    glScaled(0.25, 0.3, 0.15);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);
    glTranslated(0.55, 0.35, 0.06);
    glScaled(0.25, 0.3, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();
    
    
    
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(0.85, 0.105, 0.0);
    glScaled(0.08, 0.3, 0.22);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(0.2, 0.105, 0.0);
    glScaled(0.08, 0.3, 0.22);
    glutSolidCube(1.0);
    glPopMatrix();
    
    

    
    
    
}

void drawTeapot(){
    glPushMatrix();
    glTranslated(1.1, 0.4, 0.52);
    glColor3f(0.00,0.10,0.20);
    glRotated(30, 0, 1, 0);
    glutSolidTeapot(0.06);
    
   
    glPopMatrix();

}


void drawChair(double topWid, double topThick, double legThick, double legLen){
    double dist = 0.95*topWid / 2.0 - legThick / 2.0;
    
    glPushMatrix();
    
   // glTranslated(0, 0.45, -0.07);
   // glRotated(90, 0, 0, 0);
  //  glScaled(topWid, topThick, 0.3);
    glTranslated(dist, 0.2, dist);
    drawTableLeg(legThick, legLen);
    glPopMatrix();
    glPushMatrix();
   
   // glTranslated(0, 0.45, -0.07);
   // glRotated(90, 0, 0, 0);
  //  glScaled(topWid, topThick, 0.3);
    glTranslated(-0.06, 0.2, dist);
    drawTableLeg(legThick, legLen);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0, legLen+0.15, 0.07);
    glRotated(90, 0, 0, 0);
    glScaled(0.12, topThick, 0.12);
    glutSolidCube(1.0);
    glPopMatrix();
    
  
    
    
    glPushMatrix();
    glTranslated(0, legLen, 0);
    glScaled(topWid, topThick, topWid);
    glutSolidCube(1.0);
    glPopMatrix();
    

   
    glPushMatrix();
    glTranslated(dist, 0, dist);
    drawTableLeg(legThick, legLen);
    glTranslated(0, 0, -2 * dist);
    drawTableLeg(legThick, legLen);
    glTranslated(-2 * dist, 0, 2 * dist);
    drawTableLeg(legThick, legLen);
    glTranslated(0, 0, -2 * dist);
    drawTableLeg(legThick, legLen);
    
    glColor3f(0.5f, 0.35f, 0.05f);
    glPopMatrix();
    
}
void drawlamp() {
    glPushMatrix();
    
    glTranslated(0.5,1.32, 0.5);

    glScaled(0.009, 0.2, 0.009);
    glColor3f(0.88,1.00,0.30);

    glutSolidCube(1.0);
    glPopMatrix();
    
    glPopMatrix();
    glPushMatrix();
    glTranslated(0.5,1.2, 0.5);
    glColor3f(0.88,1.00,0.30);

    glutSolidSphere(0.06, 30, 30);
    

    
  
    
}

void drawcat (){
    
    
    glPushMatrix();
    glTranslated(0.8,0.06, 0.8);

    glScaled(0.7, 1, 1);
  
    glColor3f(1,0.5,0);

    glutSolidSphere(0.08, 30, 30);
    
    glPopMatrix();
    glPushMatrix();
    glTranslated(0.8,0.07, 0.9);

    glScaled(1, 1, 1);
  
    glColor3f(1,0.5,0);

    glutSolidSphere(0.04, 30, 30);
    
    
    
    glPopMatrix();
    glPushMatrix();
    glTranslated(0.8,0.07, 0.9);

    glScaled(1, 1, 1);
  
    glColor3f(1,0.5,0);

    glutSolidSphere(0.04, 30, 30);
    
    glPopMatrix();
    
    
    glPushMatrix();
    glTranslated(0.82,0.085, 0.9);

    glScaled(0.01, 0.1, 0.01);
  
    glColor3f(1,0.5,0);

    glutSolidCube(1.0);
    
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0.78,0.085, 0.9);

    glScaled(0.01, 0.1, 0.01);
  
    glColor3f(1,0.5,0);

    glutSolidCube(1.0);
    
    glPopMatrix();
    
    
    
    
    
}

void setupLights() {
    GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };
    GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
    GLfloat specular[] = { 1.0f, 1.0f, 1.0, 1.0f };
    GLfloat shininess[] = { 50 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    GLfloat lightIntensity[] = { 0.7f, 0.7f, 1, 1.0f };
    GLfloat lightPosition[] = { 0.5,1.2, 0.5, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
    
    GLfloat lightIntensity1[] = { 0.1f, 0.1f, 0.1 , 1.0f };
    GLfloat lightPosition1[] = { 0.46, 0.18, 0.14, 0.0f };
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightIntensity1);
}
void setupCamera() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 640 / 480, 0.001, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    camera.look();
}





void Display() {
    setupCamera();
    setupLights();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glTranslated(0.525, 0.0, 0.525);
   
    drawTable(0.275, 0.01, 0.01, 0.15);
    
    glPopMatrix();
    
    
    glPushMatrix();
    drawWall(0.04);
    glTranslated(0, -0.4, 0.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0, 1.35, 0.0);
    drawWall(0.04);
    glPopMatrix();
    
    glPushMatrix();
    glRotated(90, 0, 0, 1.0);
    drawWall(0.04);
    glPopMatrix();
    glPushMatrix();
    glRotated(-90, 1.0, 0.0, 0.0);
    drawWall(0.04);
    glPopMatrix();
    glPushMatrix();
  


   
    drawPlayer(playerX,playerZ);
  

 
  
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.0, 0, 0);
    glScaled(0.05, 0.05, 0.05);
    glTranslatef(10.5, 4.5, 10.5);
    glRotatef(Rotate, 0, 1,0 );
    drawJack();
    
   

    glPopMatrix();
    
    glPushMatrix();
    
    drawShelf();
    
    glPopMatrix();
    
    glPushMatrix();

    
    glTranslatef(-0.35, 0.65, 0);
    drawCup();
   
    
    glPopMatrix();
    
    glPushMatrix();
    
    
    glPopMatrix();
    glPushMatrix();
    glTranslatef(TvX,TvY, TvZ);
    
    drawTvStand();
 
   

   
    
    glPopMatrix();
    
   
    glPushMatrix();
    drawTeapot();
    glPopMatrix();
    
    glPushMatrix();
    
  
    glTranslatef(1.1,0, 0.5);
    drawTable(0.275, 0.01, 0.01, 0.3);
   
    glPopMatrix();
    
 
   
    glPushMatrix();
    
    glTranslatef(1.1+ChairX,0+ChairY, 0.7+ChairZ);
    drawChair(0.15, 0.02, 0.02, 0.25);
    glPopMatrix();

    
     glPushMatrix();
     
     glTranslatef(1.1+ChairX,0+ChairY, 0.2+ChairZ);
    glRotatef(180, 0, 1,0 );
     drawChair(0.15, 0.02, 0.02, 0.25);
     glPopMatrix();
    
    glPushMatrix();
    drawlamp();

    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0,0 ,CatX );
    drawcat();
    
    
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.3,0 ,CatX );
    drawcat();
    
    
    glPopMatrix();
    
    
    if (flag==false) {
        WallColor1=0.0;
        WallColor2=0.0;
        WallColor3=0.0;
//        MessageBox(0, (LPCWSTR)L"GOOAAAALLL!! you won :O", (LPCWSTR)L"End of Game", MB_OK);
      
    }
 
       
   

    glFlush();
    
    

}

void Anim() {
    
    if (CatX < 0 || CatX < 0.35 && CatFlag == false) {
        CatFlag = false;
        CatX += 0.005;
    }
    else {
        CatFlag = true;
        CatX -= 0.005;
    }
    
  

    glutPostRedisplay();
}

void print(float x, float y, float z, char* string)
{
    int len, i;

    //set the position of the text in the window using the x and y coordinates
    glRasterPos3f(x, y ,z);

    //get the length of the string to display
    len = (int)strlen(string);

    //loop to display character by character
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
    }
}
 

void Timer(int value) {
    if (playerX < 0.5 && playerZ<0.1 ) {
        flag= false;
            }

    
    


    


    // ask OpenGL to recall the display function to reflect the changes on the window
    glutPostRedisplay();

    // recall the Timer function after 20 seconds (20,000 milliseconds)
    glutTimerFunc(10, Timer, 0);
}


void Keyboard(unsigned char key, int x, int y) {
    float d = 0.05;

    switch (key) {
    case 'w':
        camera.moveY(d);
        break;
    case 's':
        camera.moveY(-d);
        break;
    case 'a':
        camera.moveX(d);
        break;
    case 'd':
        camera.moveX(-d);
        break;
    case 'q':
        camera.moveZ(d);
        break;
    case 'e':
        camera.moveZ(-d);
        break;
            
            
        case 'y':
            if (playerX<1.3) {
                playerX=playerX+0.1;
            }
            break;
            
        case 'g':
            if (playerZ<1.2) {
                playerZ=playerZ+0.1;
            }
          
            break;
            
        case 'h':
            if (playerX>0.1) {
                playerX=playerX-0.1;
            }
          
            break;
            
            
        case 'j':
            if (playerZ>0.1) {
                playerZ=playerZ-0.1;
            }
           
            break;
            
        case 'o':
            if (ChairX<0) {
                ChairX=ChairX+0.1;
            }
               
            
           
            break;
        case 'l':
            if (ChairX>-0.8) {
                
                ChairX=ChairX-0.1;
            }
                
            
           
            break;
        case 'k':
            if (ChairZ<0.5) {
                ChairZ=ChairZ+0.1;
            }
                
            
           
            break;
        case ';':
            if (ChairZ>0.1) {
                ChairZ=ChairZ-0.1;
            }
           
        
           
            break;
            
        case '[':
            if (ChairY>0.1) {
                ChairY=ChairY-0.1;
            }
            break;
            
        case ']':
            if (ChairY<0.9) {
                ChairY=ChairY+0.1;
            }
           
        
           
            break;
           
        case 'W':
            if (TvX<0.4) {
                TvX=TvX+0.1;
            }
               
            
           
            break;
        case 'S':
            if (TvX>-0.1) {
                
                TvX=TvX-0.1;
            }
                
            
           
            break;
        case 'A':
            if (TvZ<1.2) {
                TvZ=TvZ+0.1;
            }
                
            
           
            break;
        case 'D':
            if (TvZ>0.2) {
                TvZ=TvZ-0.1;
            }
           
        
           
            break;
            
        case 'R':
            if (TvY>0.2) {
                TvY=TvY-0.1;
            }
            break;
            
        case 'T':
            if (TvY<0.8) {
                TvY=TvY+0.1;
                
                
            }
            break;
        
        case '1':
            WallColor1=1.0;
            WallColor2=1.0;
            WallColor3=0.0;
            break;
        
        case '2':
            WallColor1=1.0;
            WallColor2=0.0;
            WallColor3=0.0;
            break;
            
        case '3':
            WallColor1=1.0;
            WallColor2=1.0;
            WallColor3=1.0;
            break;
        
        case '4':
            WallColor1=1.0;
            WallColor2=1.0;
            WallColor3=1.0;
            break;
        
           
        case '5':
                camera.toplook();
                break;
            case '6':
                camera.frontlook();
                break;
            case '7':
                camera.sidelook();
                break;

            case '8':
                camera.mainview();
                break;
           
          

            
            
            
    case GLUT_KEY_ESCAPE:
        exit(EXIT_SUCCESS);
    }

    glutPostRedisplay();
}
void Special(int key, int x, int y) {
    float a = 1.0;

    switch (key) {
    case GLUT_KEY_UP:
        camera.rotateX(a);
        break;
    case GLUT_KEY_DOWN:
        camera.rotateX(-a);
        break;
    case GLUT_KEY_LEFT:
        camera.rotateY(a);
        break;
    case GLUT_KEY_RIGHT:
        camera.rotateY(-a);
        break;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitWindowSize(640, 480);
    glutInitWindowPosition(50, 50);

    glutCreateWindow("Lab 5");
    glutDisplayFunc(Display);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(Special);
    glutIdleFunc(Anim);
    glutTimerFunc(0, Timer, 0);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    
    

    glShadeModel(GL_SMOOTH);

    glutMainLoop();
    return  0;
}
