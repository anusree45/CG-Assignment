    //STANDARD I/O
#include<stdio.h>
#include<stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

    //GLOBAL VAR
float xx=240.0;
float y=325.0;
float yy=549.0;

    //RGB INITIALIZATION

float rr=249.0;
float gg=132;
float bb=4.0;
    //CONDITION FLAGS
int eclipse=0;
int sunrise=0;

    //TEXT DISPLAY USING BITMAP CHARACTERS

void drawString (void *font, float x, float y, char *str, float r,float g,float b) {

     char *ch;
     glColor3f(r,g,b);
     glRasterPos3f(x, y, 0.0);
     for (ch= str; *ch; ch++)
         glutBitmapCharacter(font, (int)*ch);
}

    //OBJECT SHADOW

void black()
{
    int x11,y11,radd;
    float dpp;



    radd=47;
    x11=0;
    y11=radd;
    dpp=1-radd;
    glColor3f(0.3,0.2,0.1);

    glBegin(GL_TRIANGLE_STRIP);

    while(x11<=y11){
        if(dpp<=0){
            x11++;
        dpp=dpp+2*x11+1;
        }
        else
        {
        x11++;
        y11--;
        dpp=dpp+2*(x11-y11)+1;
        }
        glVertex2f(x11+xx,y11+yy);
        glVertex2f(x11+xx,yy-y11);
        glVertex2f(xx-x11,yy+y11);
        glVertex2f(xx-x11,yy-y11);
        glVertex2f(xx+y11,yy+x11);
        glVertex2f(xx+y11,yy-x11);
        glVertex2f(xx-y11,yy+x11);
        glVertex2f(xx-y11,yy-x11);

    }
    glEnd();
}

    //OBJECT SUN

void sun()
{
    int x,x1,y1,rad;
    float dp;

    x=325;

    rad=50;
    x1=0;
    y1=rad;

    dp=1-rad;

    //glColor3f((rr+90.0)/255,(gg+30.0)/255,(bb-20.0)/255);
    glColor3f(247.0/255.0,253.0/255.0,4.0/255.0);
    glBegin(GL_TRIANGLES);
    while(x1<=y1){
        if(dp<=0){
            x1++;
            dp=dp+2*x1+1;
        }
        else{
            x1++;
            y1--;
            dp=dp+2*(x1-y1)+1;
        }
        glVertex2f(x1+x,y1+y);
        glVertex2f(x1+x,y-y1);
        glVertex2f(x-x1,y+y1);
        glVertex2f(x-x1,y-y1);
        glVertex2f(x+y1,y+x1);
        glVertex2f(x+y1,y-x1);
        glVertex2f(x-y1,y+x1);
        glVertex2f(x-y1,y-x1);

    }
    glEnd();

}

    //OBJECT SEA

void sea(){

   glBegin (GL_QUADS);

        glColor3f(0.3,0.3,1); //
        glVertex3f (-1000.0, 0.0, 0.0);
        glVertex3f (-1000.0, 275.0, 0.0);
        glVertex3f (1000.0, 275.0, 0.0);
        glVertex3f (1000.0, 0.0, 0.0);

    glEnd ();
   
    // CASCADING CALL TO OBJECT SUN

       sun();
}

    //TRANSITION LOGIC DEFINITION

void init() {

        // ECLIPSE CONDITION FLAG
    if(eclipse){

        //TRANSITION DEFINITION
    if(xx>=240.0 && xx<=280.0){
        xx+=0.3/4;
        rr-=1.20/4;
        gg-=1.0/4;
        bb-=1.0/4;

    }
    else if(xx>=280.0 && xx<=320.0){
        xx+=0.3/4;
        rr-=1.20/4;
        gg-=1.0/4;
        bb-=1.0/4;

    }
    else if(xx>=320.0 && xx<=330.0){
        if(xx==325){
            Sleep(5000);
        }
        xx+=0.040/4;
        rr-=0.120/4;
        gg-=0.160/4;
        bb-=0.10/4;

    }
    else if(xx>=330.0 && xx<=360.0){
        xx+=0.3/4;
        rr+=1.20/4;
        gg+=1.0/4;
        bb+=1.0/4;

    }
    else if(xx>=360.0 && xx<=400.0){
        xx+=0.3/4;
        rr+=0.90/4;
        gg+=0.65/4;
        bb-=0.75/4;

    }
    else if(xx>=400.0 && xx<=500.0){
        xx+=0.3/4;
        rr+=0.9/4;
        gg+=0.4/4;
        bb-=0.6/4;
    }
    else{

            float xx=240.0;
            float rr=249.0;
            float gg=132.0;
            float bb=4.0;
            glutPostRedisplay();
    }

     glutPostRedisplay();

    }


        //SUNRISE CONDITION FLAG
    else if(sunrise){

        if(y>=325.0 && y<=549.0){

                //TRANSITION DEFINITION
            y+=1.0/4;
            rr+=.2/4;
            gg+=.3/4;
            glutPostRedisplay();
        }
        else if(y==550.0){

                //RESET SUNRISE CONDITION FLAG
            sunrise=0;

                //RESET ORIGINAL RGB VAL
            float rr=249.0;
            float gg=132.0;
            float bb=4.0;
            glutPostRedisplay();
        }
    }
 }





    //MAIN DISPLAY MEHTOD

void disp()
{

    glClearColor(rr/255,gg/255,bb/255,1);	 //1,1,0.7,0.5	//0.6 0.5 0.5 1
    glClear(GL_COLOR_BUFFER_BIT);

    //DISPLAY SEA
    sea();

    //DISPLAY SHADOW
    if(eclipse) {
        black();
    }


    //TEXT DISPLAY WITH COLOUR TRANSITIONS
    if(eclipse){
        //glColor3f((rr+50.0)/255,(gg-34.0)/255,(bb+500.0)/255);

        drawString (GLUT_BITMAP_HELVETICA_18, 225.0, 200.0, "Press Escape to quit",0,0,0);

        //drawString (GLUT_BITMAP_TIMES_ROMAN_24, 100.0, 240.0, "S  O  L  A  R      E  C  L  I  P  S  E");
    }

    else if(sunrise){
        //glColor3f((rr-10.0)/255,(gg-60.0)/255,(bb-30.0)/255);

        drawString (GLUT_BITMAP_HELVETICA_18, 225.0, 200.0, "* Press Escape to quit",0,0,0);

        drawString (GLUT_BITMAP_HELVETICA_18, 225.0, 100.0, "* Press E for Eclipse ",0,0,0);

        drawString (GLUT_BITMAP_HELVETICA_18, 175.0, 149.0, "Wait for Sun to reach apex ...then ",0,0,0);

        //drawString (GLUT_BITMAP_HELVETICA_18, 320.0, 130.0, "             ");

        //drawString (GLUT_BITMAP_TIMES_ROMAN_24, 250.0, 240.0, "S  O  L  A  R      E  C  L  I  P  S  E");
    }

    else {
        drawString(GLUT_BITMAP_HELVETICA_18,225.0,200.0,"* Press S for Sunrise",0,0,0);
    }

        //FLUSH ONTO SCREEN
    glutSwapBuffers();

}

void keyboard (unsigned char key, int x, int y)
{
    //SET SUNRISE CONDITION FLAG

    if (key == 13) {                //13==Enter
        glutDisplayFunc(disp);
    }

    //END ANIMATION
    if (key == 27) {                //27==Escape
        exit (0);
    }

    //SET ECLIPSE CONDITION FLAG
    else if (key == 'e' || key == 'E') {
        eclipse=1;

    }
    else if (key=='s' || key=='S') {
        sunrise=1;
    }
}

    //RESHAPE WINDOW

void reshape (int width, int height)
{
    glViewport (0, 0, (GLsizei) width, (GLsizei) height);

    glMatrixMode (GL_PROJECTION);

    glLoadIdentity ();

    if(width<=height)
        glOrtho(-1, 1, -1*(GLfloat)height/(GLfloat)width, 1*(GLfloat)height/(GLfloat)width, -10, 10);
    else
        glOrtho(-1*(GLfloat)width/(GLfloat)height, 1*(GLfloat)width/(GLfloat)height, -1, 1, -10, 10);

    //glOrtho(-1.0,1.0, -1.0,1.0, -1.0,1.0);

    glMatrixMode (GL_MODELVIEW);


}




void first()
{
    glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f(1,1,1);
    //glColor3f(95.0/255,6.0/255,74.0/255);
    drawString (GLUT_BITMAP_9_BY_15, 200.0, 150.0, "* Press ESCAPE To Quit",1,0.5,0);
    drawString (GLUT_BITMAP_9_BY_15, 200.0, 200.0, "* Press 'ENTER' To Start",1,0.5,0);
    drawString (GLUT_BITMAP_TIMES_ROMAN_24, 5.0, 550,"BMS INSTITUTE OF TECHNOLOGY AND MANAGEMENT",0.596,0.870,0.850);
    drawString (GLUT_BITMAP_TIMES_ROMAN_24, 100, 500,"DEPARTMENT OF COMPUTER SCIENCE",1,0,0);
    drawString (GLUT_BITMAP_HELVETICA_18,140, 350,"UNDER THE GUIDANCE OF : SHANKAR.R",1,1,1);
    drawString (GLUT_BITMAP_HELVETICA_18,140, 300,"BY:  1BY18CS075  ANUSREE K",0.576,0.196,0.619);
    drawString (GLUT_BITMAP_HELVETICA_18,140, 270,"         1BY18CS078  KUMUDA SIRI T T",0.576,0.196,0.619);
    drawString (GLUT_BITMAP_TIMES_ROMAN_24, 130.0, 400.0, "S   O   L   A   R        E   C   L   I   P   S   E",1,1,0);

    glutSwapBuffers();


}

    //PROGRAM ENTRY POINT



int main(int argv,char **argc)
{


    glutInit(&argv,argc);

    glutInitWindowSize(650,650);



    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glutCreateWindow("Solar Eclipse");

    glutPositionWindow(0,0);

    gluOrtho2D(0,650,0,650);

    //initfirst();

    glutDisplayFunc(first);

    glutReshapeFunc (reshape);

    glutKeyboardFunc (keyboard);

    glutIdleFunc(init);



    glutMainLoop();

    return 0;

}
