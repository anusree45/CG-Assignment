    //STANDARD I/O
#include<stdio.h>
#include<stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include<math.h>
#define PI 3.1416
float theta = 0;
struct point
{
    GLfloat x, y, z;
};

int factorial (int n)
{
    if (n<=1)
    return (1);
    else
    n = n * factorial ( n-1 );
    return n;
}

void computeNcR (int n, int *hold_ncr_values)
{
    int r;
    for (r=0; r<=n; r++) //start from nC0, then nC1, nC2, nC3 till nCn
    {
        hold_ncr_values [r] = factorial (n) / ( factorial (n-r) * factorial (r) );
    }
}

void computeBezierPoints (float t, point *actual_bezier_point, int number_of_control_points,
 point *control_points_array, int *hold_ncr_values) // 5 parameters
{
    int i, n = number_of_control_points - 1;
    float bernstein_polynomial;
    actual_bezier_point -> x = 0;
    actual_bezier_point -> y = 0;
    actual_bezier_point -> z = 0;
    for ( i=0; i<number_of_control_points; i++ )
    {
        bernstein_polynomial = hold_ncr_values [i] * pow(t, i) * pow( 1-t, n-i);
        actual_bezier_point->x += bernstein_polynomial * control_points_array [i].x;
        actual_bezier_point->y += bernstein_polynomial * control_points_array [i].y;
        actual_bezier_point->z += bernstein_polynomial * control_points_array [i].z;
     }
}

void Bezier (point *control_points_array, int number_of_control_points, int number_of_bezier_points)
{
    point actual_bezier_point;
    float t;
    int *hold_ncr_values, i;
    hold_ncr_values = new int [number_of_control_points]; // to hold the nCr values
    computeNcR (number_of_control_points - 1, hold_ncr_values); // calculate nCr values
    glBegin (GL_LINE_STRIP);
    for(i=0; i<=number_of_bezier_points; i++)
    {
        t=float (i) / float (number_of_bezier_points);
        computeBezierPoints ( t, &actual_bezier_point, number_of_control_points,
        control_points_array, hold_ncr_values );// 5 parameters
        glVertex2f (actual_bezier_point.x, actual_bezier_point.y);
    }
    glEnd ();
    delete [] hold_ncr_values;
}
static int slices = 30;
static int stacks = 26;

    //GLOBAL VAR
float xx=240.0;
float y=325.0;
float yy=549.0;

    //RGB INITIALIZATION
/*float rr=245.0;
float gg=160.0;
float bb=0.0;
*/

float rr=249.0;
float gg=132;
float bb=4.0;
    //CONDITION FLAGS
int eclipse=0;
int sunrise=0;

    //TEXT DISPLAY USING BITMAP CHARACTERS
/*
void draw_lines()
{
    glBegin(GL_LINES);
        glColor3f(1.0,1.0,1.0);
        glVertex3f(-1.79,0.98,-6.0);
        glVertex3f(2.6,0.02,-6.0);
        glVertex3f(-1.79,-0.98,-6.0);
        glVertex3f(2.6,-0.02,-6.0);


    glEnd();
}

void emission()
{
    float emissive[]={0.2,0.2,0.2,1.0};
    glMaterialfv(GL_FRONT,GL_EMISSION,emissive);
}

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


    glPushMatrix();
        glColor3f(0.976,0.698,0.031);
        glTranslated(-2,0.0,-6);
        glRotated(190,0,1,0);
        //glRotated(a,0,0,1);
        GLfloat mat_amb1[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
        GLfloat mat_dif1[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
        //GLfloat light_dir[]={1.0, 2.0, 3.0, 0.0};
        GLfloat mat_spec1[] = { 0.1f, 0.1f, 0.0f, 1.0f };
        GLfloat mat_pos1[] = { -2, 0.0, -6.0, 0.0 };
        glEnable(GL_LIGHT1);
        glEnable(GL_NORMALIZE);
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_LIGHTING);

        const GLfloat light_amb1[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
        const GLfloat light_dif1[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
        const GLfloat light_spec1[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        const GLfloat light_pos1[] = { -2, 0.0, -6.0, 0.0 };
        const GLfloat light_dir1[] = {-1.0,0.0,0.0};


        glLightfv(GL_LIGHT1, GL_AMBIENT,  light_amb1);
        glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_dif1);
        glLightfv(GL_LIGHT1, GL_SPECULAR, light_spec1);
        glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);
        glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_dir1);
        glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 180.0);
        emission();

        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb1);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif1);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec1);
        glMaterialf(GL_FRONT, GL_SHININESS, 20.0);
        glutSolidSphere(1.0,slices,stacks);

        //glEnable(GL_LIGHT0);
        glDisable(GL_LIGHT1);

    glPopMatrix();

    float emissive[]={0.0,0.0,0.0,1.0};

    glPushMatrix();

        glColor3d(1,1,1);
        glTranslated(2.0,0.0,-6);
        glRotated(60,0,1,0);
        //glRotated(a,0,0,1);
        glutSolidSphere(0.15,slices,stacks);
    glPopMatrix();

    glPushMatrix();

        glColor3f (115.0/255.0, 164.0/255.0, 244/255.0);
        glTranslated(3,0.0,-6);
        glRotated(60,0,1,0);
        //glRotated(a,0,0,1);
        glutSolidSphere(0.4,slices,stacks);
    glPopMatrix();
    glPushMatrix();
        draw_lines();
    glPopMatrix();
    glutSwapBuffers();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_position[] = { -2, 0.0, -6.0, 1.0 };
//const GLfloat light_position[] = {-1.5,2.0,0.0,0.0};
//const GLfloat spot_direction[] = {-1.0f, 0.0f, 0.0f};


const GLfloat mat_ambient[]    = { 0.2f, 0.1f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

void eclipsefn()
{
    glutInitWindowSize(640,480);
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glClearColor(0,0,0,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    //glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    //glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
    //glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.0);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glShadeModel(GL_SMOOTH);


}
*/
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

   /* glBegin (GL_QUADS);

        glColor3f(0.3,0.3,1); //
        glVertex3f (-1000.0, 0.0, 0.0);
        glVertex3f (-1000.0, 275.0, 0.0);
        glVertex3f (1000.0, 275.0, 0.0);
        glVertex3f (1000.0, 0.0, 0.0);

    glEnd ();
    */
    // CASCADING CALL TO OBJECT SUN

    glClear (GL_COLOR_BUFFER_BIT);
    int number_of_control_points= 4, number_of_bezier_points= 10;
    point control_points_array[4]= {{-1000, 250, 0}, {250, 300, 0}, {450, 200, 0},{1000, 280, 0}};
    control_points_array[1].x += 50 * sin (theta * PI/180.0); // for animating the flag
    control_points_array[1].y += 25 * sin (theta * PI/180.0);
    control_points_array[2].x -= 50 * sin ((theta+30) * PI/180.0);
    control_points_array[2].y -= 50 * sin ((theta+30) * PI/180.0);
    control_points_array[3].x -= 25 * sin ((theta-30) * PI/180.0);
    control_points_array[3].y += sin ((theta-30) * PI/180.0);
    theta += 1; //animating speed
    glPushMatrix ();
    glPointSize (5);
    glColor3f (0, 0, 1); //Indian flag: Saffron color code
    for (int i=0; i<350; i++)
    {
        glTranslatef(0, -0.8, 0 );
        Bezier(control_points_array, number_of_control_points, number_of_bezier_points);
    }
    glPopMatrix();
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


    //KEYBOARD EVENT HANDLER



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
