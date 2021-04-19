#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include<bits/stdc++.h>

using namespace std;

const int windowWidth = 700;
const int windowheight = 700;

GLfloat eyeX = 0;
GLfloat eyeY = 10;
GLfloat eyeZ = -20;

GLfloat lookX = 0;
GLfloat lookY = 0;
GLfloat lookZ = 0;

float inithight = 0.5;
float initwight = 0.5;
float initdense = 0.5;

float roomHeight = 20;
float roomWidth = 30;
float roomLength = 20;

float walldepth = 1;

float wearDropWidth = 5;
float wearDropHeight = 8;
float wearDropLength = 3;

float portHoleWidth = 2.75;
float portHoleHeight = 4;
float portHoleLength = 0.1;

float dressingTableWidth = 2;
float dressingTableHeight = 4;
float dressingTableLength = 8;

float bedWidth = 8;
float bedHeight = 2;
float bedLength = 12;

float rotationYAngle = 0;
float rotationXAngle = 0;

float fanAngle = 0.0;
bool fanRotate = true;
float hourAngle = 0.0;
float minuteAngle = 0.0;

static GLfloat vertex_unitCube[8][3] =
{
    {0.0, 0.0, 0.0},    //0
    {0.0, 0.0, 1.0},    //1
    {1.0, 0.0, 1.0},    //2
    {1.0, 0.0, 0.0},    //3
    {0.0, 1.0, 0.0},    //4
    {0.0, 1.0, 1.0},    //5
    {1.0, 1.0, 1.0},    //6
    {1.0, 1.0, 0.0}     //7
};

static GLubyte unitCube_indices[6][4] =
{
    {1, 2, 6, 5},
    {2, 3, 7, 6},
    {3, 0, 4, 7},
    {0, 1, 5, 4},
    {4, 5, 6, 7},
    {1, 0, 3, 2}
};


void unitCube(float colorR=0.5, float colorG=0.5, float colorB=0.5, float alpha=1)
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3ub (colorR,colorG,colorB);
        glColor4f(colorR,colorG,colorB,alpha);
        colorR += 0.03;
        colorG += 0.03;
        colorB += 0.03;

        for (GLint j=0; j<4; j++)
        {
            glVertex3fv(&vertex_unitCube[unitCube_indices[i][j]][0]);
        }
    }
    glEnd();
}

void axes()
{
    float length = 10;
    float width = 0.3;

    // X-axis
    glPushMatrix();
    glTranslatef(length/2,0,0);
    glScalef(length,width,width);
    glTranslatef(-0.5,-0.5,-0.5);
    unitCube(0.8,0.1,0.1);  //red
    glPopMatrix();

    // Y-axis
    glPushMatrix();
    glTranslatef(0,length/2,0);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    unitCube(0.1,0.8,0.1);  //green
    glPopMatrix();

    // Z-axis
    glPushMatrix();
    glTranslatef(0,0,length/2);
    glScalef(width,width,length);
    glTranslatef(-0.5,-0.5,-0.5);
    unitCube(0.1,0.1,0.8);  //blue
    glPopMatrix();
}

void roomFloor(float x,float y,float z,float xx,float yy,float zz,float cr=0.5,float cg=0.5,float cb=0.5)
{
    glPushMatrix();
        glTranslatef(xx,yy,zz);
        glScalef(x,y,z);
        glTranslatef(-inithight,-initwight,-initdense);
        unitCube(cr,cg,cb);
    glPopMatrix();
}

void building(){
    roomFloor(roomWidth,walldepth,roomLength,0,-walldepth/2,0); //bottom ->1st 3 parameter scale,2nd 3 translation,3rd 3 color
    roomFloor(roomWidth,walldepth,roomLength,0,roomHeight+walldepth/2,0,0.61,0.56,0.49);   //top
    roomFloor(walldepth,roomHeight,roomLength,(roomWidth/2-walldepth/2),roomHeight/2,0,0.18,0.55,0.34);    //left
    roomFloor(walldepth,roomHeight,roomLength,-(roomWidth/2-walldepth/2),roomHeight/2,0,0.18,0.55,0.34);   //right
    roomFloor(roomWidth,roomHeight,walldepth,0,roomHeight/2,(roomLength/2-walldepth/2),0.55,0.39,0.42);    //back
}

void weardrop(float x,float z,int n,float angle=0){
    wearDropHeight = 2*n+(n+1)*0.5;

    glPushMatrix();
        glTranslatef(x,0,z);
        glTranslatef(0,wearDropHeight/2,0);
        glRotatef(angle,0,1,0);
        glTranslatef(0,-wearDropHeight/2,0);
        glPushMatrix();
            for(int i=0;i<n;i++)
            {
                float yshift = 1.5+i*2.5;
                //drawer
                glPushMatrix();
                    glTranslatef(0,yshift,-(wearDropLength/2)+0.3);
                    glScalef(wearDropWidth-1,2,1);
                    glTranslatef(-inithight,-initwight,-initdense);
                    unitCube(0.165,0.09,0.059);
                glPopMatrix();

                //handle
                glPushMatrix();
                    glTranslatef(0,yshift,-wearDropLength/2);
                    glScalef(1,.2,.5);
                    glTranslatef(-inithight,-initwight,-initdense);
                    unitCube(1,1,1);
                glPopMatrix();
            }

            //body
            glPushMatrix();
                glTranslatef(0,wearDropHeight/2,0);
                glScalef(wearDropWidth,wearDropHeight,wearDropLength);
                glTranslatef(-inithight,-initwight,-initdense);
                //unitCube(89,39,25);
                unitCube(0.35,0.15,0.098);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

}


void weardrops(){
    weardrop(roomWidth/2-walldepth-wearDropWidth/2,roomLength/2-walldepth-wearDropLength/2,3);
    weardrop(-(roomWidth/2-walldepth-wearDropLength/2),-(bedLength-roomLength/2+walldepth+1+wearDropWidth/2),2,-90);
}

void bed(float x, float z){
    float coverHight = 1;
    float headLength = 1;
    float headHight = 5;
    glPushMatrix();
        glTranslatef(x,0,z);
        glPushMatrix();
            //bad mat
            glPushMatrix();
                glPushMatrix();
                    glTranslatef((bedWidth/2)+1.5,0.25,0);
                    glScalef(1,0.1,5);
                    glTranslatef(-inithight,-initwight,-initdense);
                    unitCube(0.22,0.29,0.67);
                glPopMatrix();
                glPushMatrix();
                    glTranslatef((bedWidth/2)+1.5,0.2,0);
                    glScalef(3,0.1,5);
                    glTranslatef(-inithight,-initwight,-initdense);
                    unitCube(1,0.24,0);
                glPopMatrix();
            glPopMatrix();

            //bad pillow 1
            glPushMatrix();
                glTranslatef(2,bedHeight+coverHight,3.5);
                glScalef((bedWidth/2)-1,1,2);
                glTranslatef(-inithight,-initwight,-initdense);
                unitCube(0,0,0.8);
            glPopMatrix();

            //bad pillow 2
            glPushMatrix();
                glTranslatef(-2,bedHeight+coverHight,3.5);
                glScalef((bedWidth/2)-1,1,2);
                glTranslatef(-inithight,-initwight,-initdense);
                unitCube(0,0,0.8);
            glPopMatrix();

            //bad shit
            glPushMatrix();
                glTranslatef(0,bedHeight+coverHight,-(3));
                glScalef(bedWidth-1,0.1,4);
                glTranslatef(-inithight,-initwight,-initdense);
                unitCube(0.55,0.04,0.31);
            glPopMatrix();

            //bed box left 2
            glPushMatrix();
                glTranslatef(bedWidth/2,0.5+(bedHeight-1)/2,-(0.5+((bedLength/2)-1)/2));
                glScalef(0.1,1,5);
                glTranslatef(-inithight,-initwight,-initdense);
                unitCube(0.3,0.16,0.1);
            glPopMatrix();

            //bed box left 1
            glPushMatrix();
                glTranslatef(bedWidth/2,0.5+(bedHeight-1)/2,0.5+((bedLength/2)-1)/2);
                glScalef(0.1,bedHeight-1,(bedLength/2)-1);
                glTranslatef(-inithight,-initwight,-initdense);
                unitCube(0.3,0.16,0.1);
            glPopMatrix();

            //bed box front
            glPushMatrix();
                glTranslatef(0,0.5+(bedHeight-1)/2,-bedLength/2);
                glScalef(bedWidth-1,bedHeight-1,0.1);
                glTranslatef(-inithight,-initwight,-initdense);
                unitCube(0.3,0.16,0.1);
            glPopMatrix();

            //bed head box
            glPushMatrix();
                glTranslatef(0,bedHeight+coverHight+2,bedLength/2-headLength);
                glScalef(bedWidth-1,headHight-coverHight-1,0.1);
                glTranslatef(-inithight,-initwight,-initdense);
                unitCube(0.35,0.16,0.075);
            glPopMatrix();

            //bed head
            glPushMatrix();
                glTranslatef(0,bedHeight+headHight/2,bedLength/2-headLength/2);
                glScalef(bedWidth,headHight,headLength);
                glTranslatef(-inithight,-initwight,-initdense);
                unitCube(0.3,0.16,0.1);
            glPopMatrix();

            //bed cover
            glPushMatrix();
                glTranslatef(0,bedHeight+coverHight/2,-headLength/2);
                glScalef(bedWidth,coverHight,bedLength-1);
                glTranslatef(-inithight,-initwight,-initdense);
                unitCube(0.52,0.44,1);
            glPopMatrix();

            //bed lower
            glPushMatrix();
                glTranslatef(0,bedHeight/2,0);
                glScalef(bedWidth,bedHeight,bedLength);
                glTranslatef(-inithight,-initwight,-initdense);
                unitCube(0.5,0.22,0.14);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void beds(){
    bed(-(roomWidth/2-walldepth-bedWidth/2),roomLength/2-walldepth-bedLength/2);
}

void dressingTable(float x, float z, int n){
    dressingTableLength = 2*n+(n+1)*0.5;

    glPushMatrix();
        glTranslatef(x,0,z);
        glPushMatrix();
        //upper part
        //mirror
            glPushMatrix();
                glTranslatef(dressingTableWidth/2-0.5,dressingTableHeight+3,0);
                glScalef(0.1,dressingTableHeight+1,dressingTableLength-2.5);
                glTranslatef(-inithight,-initwight,-initdense);
                unitCube(1,1,1);
            glPopMatrix();
        //mirror box
            glPushMatrix();
                glTranslatef(dressingTableWidth/2-0.25,dressingTableHeight+3,0);
                glScalef(0.5,dressingTableHeight+2,dressingTableLength-2);
                glTranslatef(-inithight,-initwight,-initdense);
                unitCube(0.5,0.22,0.14);
            glPopMatrix();
          //lower part
            glPushMatrix();
                glTranslatef(0,0,-dressingTableLength/2);
                glPushMatrix();
                    for(int i=0;i<n;i++){
                        float zshift = 1.5+i*2.5;
                        //lower drawer
                        glPushMatrix();
                            glTranslatef(-dressingTableWidth/2,dressingTableHeight/2,zshift);
                            glScalef(0.1,dressingTableHeight-1,dressingTableWidth);
                            glTranslatef(-inithight,-initwight,-initdense);
                            unitCube(0.165,0.09,0.059);
                        glPopMatrix();

                         //handle
                        glPushMatrix();
                            glTranslatef(-dressingTableWidth/2-0.1,dressingTableHeight/2,zshift+0.5);
                            glScalef(0.1,1,.2);
                            glTranslatef(-inithight,-initwight,-initdense);
                            unitCube(1,1,1);
                        glPopMatrix();

                    }
                    //lower part
                    glPushMatrix();
                        glTranslatef(0,dressingTableHeight/2,dressingTableLength/2);
                        glScalef(dressingTableWidth,dressingTableHeight,dressingTableLength);
                        glTranslatef(-inithight,-initwight,-initdense);
                        unitCube(0.5,0.22,0.14);
                    glPopMatrix();  //lower part
                glPopMatrix();// lower part with translation to z-axis
            glPopMatrix();//lower part back to origin
        glPopMatrix();//total dressing table
    glPopMatrix();
}

void dressingTables(){
    dressingTable(roomWidth/2-walldepth-dressingTableWidth/2,-2,3);
}

void portHole(float x,float y, float z,int n, int m,float angle=0){
    portHoleHeight = 2*n+(n+1)*0.25;
    portHoleWidth = 2*m+(m+1)*0.25;

    glPushMatrix();
        glTranslatef(x,y,z);
        glTranslatef(0,portHoleHeight/2,0);
        glRotatef(angle,0,1,0);
        glTranslatef(0,-portHoleHeight/2,0);
        glPushMatrix();
            glTranslatef(-portHoleWidth/2,0,0);
            glPushMatrix();
                for(int i = 0;i<n;i++){
                    for(int j = 0;j<m;j++){
                        float xshift = 1.25+j*2.25;
                        float yshift = 1.25+i*2.25;
                        //window frame
                        glPushMatrix();
                            glTranslatef(xshift,yshift,-0.1);
                            glScalef(2,2,0.05);
                            glTranslatef(-inithight,-initwight,-initdense);
                            unitCube(1,1,1);
                        glPopMatrix();
                    }
                }
                //window frame
                glPushMatrix();
                    glTranslatef(portHoleWidth/2,portHoleHeight/2,0);
                    glScalef(portHoleWidth,portHoleHeight,portHoleLength);
                    glTranslatef(-inithight,-initwight,-initdense);
                    unitCube(0,0,0);
                glPopMatrix();//frame
            glPopMatrix();//window
        glPopMatrix();//take it to it's origin
    glPopMatrix();// hole window in origin


}

void windows(){
    portHole(2,1+roomHeight/4,roomLength/2-walldepth,4,3);
    portHole(-(roomWidth/2-walldepth),1+roomHeight/4,roomLength/2-walldepth-portHoleWidth/2-4,3,2,-90);
}


void fan(float x,float y, float z){
    glPushMatrix();
        glRotatef(fanAngle, 0,1,0);
        glPushMatrix();
            glTranslatef(x,y,z);
            glPushMatrix();
                //blade 1
                glPushMatrix();
                    glTranslatef(0,0.5,-4);
                    glScalef(2,0.1,4);
                    glTranslatef(-inithight,-initwight,-initdense);
                    unitCube(0.94,1,1);
                glPopMatrix();
                //blade 2
                glPushMatrix();
                    glTranslatef(0,0.5,4);
                    glScalef(2,0.1,4);
                    glTranslatef(-inithight,-initwight,-initdense);
                    unitCube(0.94,1,1);
                glPopMatrix();
                //blade 3
                glPushMatrix();
                    glTranslatef(4,0.5,0);
                    glScalef(4,0.1,2);
                    glTranslatef(-inithight,-initwight,-initdense);
                    unitCube(0.94,1,1);
                glPopMatrix();
                //blade 4
                glPushMatrix();
                    glTranslatef(-4,0.5,0);
                    glScalef(4,0.1,2);
                    glTranslatef(-inithight,-initwight,-initdense);
                    unitCube(0.94,1,1);
                glPopMatrix();
                //side connector 1
                glPushMatrix();
                    glTranslatef(-2,0.5,0);
                    glScalef(1,0.5,0.5);
                    glTranslatef(-inithight,-initwight,-initdense);
                    unitCube(0.9,0.9,0.98);
                glPopMatrix();
                //side connector 2
                glPushMatrix();
                    glTranslatef(2,0.5,0);
                    glScalef(1,0.5,0.5);
                    glTranslatef(-inithight,-initwight,-initdense);
                    unitCube(0.9,0.9,0.98);
                glPopMatrix();
                //side connector 3
                glPushMatrix();
                    glTranslatef(0,0.5,2);
                    glScalef(0.5,0.5,1);
                    glTranslatef(-inithight,-initwight,-initdense);
                    unitCube(0.9,0.9,0.98);
                glPopMatrix();
                 //side connector 4
                glPushMatrix();
                    glTranslatef(0,0.5,-2);
                    glScalef(0.5,0.5,1);
                    glTranslatef(-inithight,-initwight,-initdense);
                    unitCube(0.9,0.9,0.98);
                glPopMatrix();
                //stand
                glPushMatrix();
                    glTranslatef(0,3,0);
                    glScalef(0.5,4,0.5);
                    glTranslatef(-inithight,-initwight,-initdense);
                    unitCube(0.18,0.31,0.31);
                glPopMatrix();
                //circle
                glPushMatrix();
                    glTranslatef(0,0.5,0);
                    glScalef(3,1,3);
                    glPushMatrix();
                        for(int i=0;i<360;i++){
                            glPushMatrix();
                                glRotatef(i,0,1,0);
                                glPushMatrix();
                                    glScalef(0.1,1,1);
                                    glTranslatef(-inithight,-initwight,-initdense);
                                    unitCube(0,0.75,1);
                                glPopMatrix();
                            glPopMatrix();
                        }
                    glPopMatrix();
                glPopMatrix();//circle
            glPopMatrix();//total fan
        glPopMatrix();//translated
    glPopMatrix();//rotated
}


void fans(){
    fan(0,roomHeight-walldepth-5,0);
}


void watch(float x,float y, float z){
    glPushMatrix();
        glTranslatef(x,y,z);
        glPushMatrix();
            //hour hand
            glPushMatrix();
                glRotatef(hourAngle,0,0,1);
                glPushMatrix();
                    glTranslatef(0,0.25,-0.3);
                    glScalef(0.2,1,0.1);
                    glTranslatef(-inithight,-initwight,-initdense);
                    unitCube(0,0,0);
                glPopMatrix();
            glPopMatrix();
            //minute hand
            glPushMatrix();
                glRotatef(minuteAngle,0,0,1);
                glPushMatrix();
                    glTranslatef(0,0.3,-0.4);
                    glScalef(0.2,1.2,0.1);
                    glTranslatef(-inithight,-initwight,-initdense);
                    unitCube(0,0,0);
                glPopMatrix();
            glPopMatrix();
            glPushMatrix();
                //inside
                glPushMatrix();
                    glTranslatef(0,0,-0.2);
                    glScalef(2,2,0.1);
                    glTranslatef(-inithight,-initwight,-initdense);
                    unitCube(1,1,1);
                glPopMatrix();
                //frame
                glPushMatrix();
                    glScalef(2.5,2.5,0.2);
                    glTranslatef(-inithight,-initwight,-initdense);
                    unitCube(0.22,0.28,0.31);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();//hole watch
    glPopMatrix();
}

void watches(){
    watch(-(roomWidth/2-bedWidth/2-walldepth)+1,3*(roomHeight/4)-1.5,(roomLength/2)-walldepth-0.1);
}

void light(float x,float y,float z){
    glPushMatrix();
        glTranslatef(x,y,z);
        glPushMatrix();
            glScalef(0.5,0.5,5);
            glTranslatef(-inithight,-initwight,-initdense);
            unitCube(1,1,1);
        glPopMatrix();
    glPopMatrix();
}

void lights(){
    light(roomWidth/2-walldepth/0.25,3*(roomHeight/4),-4);
}

void lamp(float x,float y,float z){
    glPushMatrix();
        glTranslatef(x,y,z);
        glPushMatrix();
            //circle
            glPushMatrix();
                glTranslatef(0,3,0);
                glScalef(2,2,2);
                glPushMatrix();
                    for(int i=0;i<360;i++){
                        glPushMatrix();
                            glRotatef(i,0,1,0);
                            glPushMatrix();
                                glScalef(0.1,1,1);
                                glTranslatef(-inithight,-initwight,-initdense);
                                unitCube(0.93,0.68,0.055);
                            glPopMatrix();
                        glPopMatrix();
                    }
                glPopMatrix();
            glPopMatrix();//circle
            //stand
            glPushMatrix();
                glTranslatef(0,1,0);
                glScalef(0.2,2,0.2);
                glTranslatef(-inithight,-initwight,-initdense);
                unitCube(0.65,0.165,0.165);
            glPopMatrix();//stand
        glPopMatrix();// lamp
    glPopMatrix();
}

void lamps(){
    lamp(-(roomWidth/2-walldepth-wearDropLength/2),wearDropHeight,-(bedLength-roomLength/2+walldepth+1+wearDropWidth/2));
}

void floordesign(){
    glPushMatrix();
        bool c = false;
        for(int i = 1;i<roomLength;i++){
            for(int j=1;j<roomWidth;j++){
                if(c){
                    glPushMatrix();
                        glTranslatef(roomWidth/2-j,0,roomLength/2-i);
                        glScalef(1,0.1,1);
                        glTranslatef(-inithight,-initwight,-initdense);
                        unitCube(0,0,0);
                    glPopMatrix();
                    c=false;
                }else{
                    glPushMatrix();
                        glTranslatef(roomWidth/2-j,0,roomLength/2-i);
                        glScalef(1,0.1,1);
                        glTranslatef(-inithight,-initwight,-initdense);
                        unitCube(1,1,1);
                    glPopMatrix();
                    c=true;
                }
            }
        }
    glPopMatrix();
}


void chair(float x, float z){
    glPushMatrix();
        glTranslatef(x,0,z);
        glPushMatrix();
            //support upper 1
            glPushMatrix();
                glTranslatef(-1.25,4,0);
                glScalef(0.5,0.5,2);
                glTranslatef(-inithight,-initwight,-initdense);
                unitCube(0.8,0.52,0.25);
            glPopMatrix();
            //support upper 1
            glPushMatrix();
                glTranslatef(-1.25,5,0);
                glScalef(0.5,0.5,2);
                glTranslatef(-inithight,-initwight,-initdense);
                unitCube(0.8,0.52,0.25);
            glPopMatrix();
            //support lower right
            glPushMatrix();
                glTranslatef(0,1,-1.25);
                glScalef(2,0.5,0.5);
                glTranslatef(-inithight,-initwight,-initdense);
                unitCube(0.8,0.52,0.25);
            glPopMatrix();
            //support lower left
            glPushMatrix();
                glTranslatef(0,1,1.25);
                glScalef(2,0.5,0.5);
                glTranslatef(-inithight,-initwight,-initdense);
                unitCube(0.8,0.52,0.25);
            glPopMatrix();
            //leg back right
            glPushMatrix();
                glTranslatef(-1.25,3,-1.25);
                glScalef(0.5,6,0.5);
                glTranslatef(-inithight,-initwight,-initdense);
                unitCube(0.8,0.52,0.25);
            glPopMatrix();
            //leg front left
            glPushMatrix();
                glTranslatef(1.25,1.5,1.25);
                glScalef(0.5,3,0.5);
                glTranslatef(-inithight,-initwight,-initdense);
                unitCube(0.8,0.52,0.25);
            glPopMatrix();
            //leg front right
            glPushMatrix();
                glTranslatef(1.25,1.5,-1.25);
                glScalef(0.5,3,0.5);
                glTranslatef(-inithight,-initwight,-initdense);
                unitCube(0.8,0.52,0.25);
            glPopMatrix();
            //leg back left
            glPushMatrix();
                glTranslatef(-1.25,3,1.25);
                glScalef(0.5,6,0.5);
                glTranslatef(-inithight,-initwight,-initdense);
                unitCube(0.8,0.52,0.25);
            glPopMatrix();
            //base
            glPushMatrix();
                glTranslatef(0,3.2,0);
                glScalef(3,0.4,3);
                glTranslatef(-inithight,-initwight,-initdense);
                unitCube(0.8,0.52,0.25);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void chairs(){
    chair(roomWidth/2-walldepth-dressingTableWidth-4,-dressingTableLength/2+2);
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-3, 3, -3, 3, 2.0, 50.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ, lookX,lookY,lookZ, 0,1,0);
    glViewport(0, 0, windowWidth, windowheight);

    //glRotatef(rotationYAngle, 0,1,0);
    //glRotatef(rotationXAngle, 1,0,0);
    //axes();

    building();
    weardrops();
    beds();
    dressingTables();
    windows();
    fans();
    watches();
    lights();
    lamps();
    floordesign();
    chairs();



    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27 :
    case 'q':
        exit(0);
        break;
    case '+':
        lookY +=0.1;
        eyeZ +=0.5;
        break;
    case '-':
        lookY -=0.1;
        eyeZ -=0.5;
        break;
    case 'A':
    case 'a':
        lookX -=0.1;
        eyeX -=0.5;
        break;
    case 'D':
    case 'd':
        lookX += 0.1;
        eyeX +=0.5;
        break;
    case 'W':
    case 'w':
        eyeY -=0.5;
        break;
    case 'S':
    case 's':
        eyeY +=0.5;
    break;
    case 'T':
    case 't':
        fanRotate= !fanRotate;
        break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    if (fanRotate == true)
    {
        fanAngle += 0.8;
        if(fanAngle > 360.0)
            fanAngle -= 360.0*floor(fanAngle/360.0);
    }

    if (fanRotate == true)
    {
        minuteAngle += 0.2;
        if(minuteAngle > 360.0)
            minuteAngle -= 360.0*floor(minuteAngle/360.0);
    }

    if (fanRotate == true)
    {
        hourAngle += 0.05;
        if(hourAngle > 360.0)
            hourAngle -= 360.0*floor(hourAngle/360.0);
    }

    glutPostRedisplay();
}

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(windowWidth,windowheight);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("1607005");

    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

//    glClearColor(1,1,1,1);

    glEnable(GL_DEPTH_TEST);
    glShadeModel( GL_SMOOTH );
    glEnable(GL_NORMALIZE);
    glEnable(GL_BLEND);

    cout<<"Press + to zoom in"<<endl;
    cout<<"Press - to zoom out"<<endl;
    cout<<"Press a to move left"<<endl;
    cout<<"Press d to move right"<<endl;
    cout<<"Press w to move up"<<endl;
    cout<<"Press s to move down"<<endl;
    cout<<"Press q to exit"<<endl;
    cout<<"Press t to stop/start rotation"<<endl;


    glutMainLoop();

    return EXIT_SUCCESS;
}
