
#include<iostream>
#include<stdio.h>
#include<math.h>
#include<glut.h>
#include<string.h>
using namespace std;
int k = 0;
GLfloat default_colors[3];
int n = 0;
int flag = 0;
typedef struct circle
{
    GLfloat x;
    GLfloat y;
    GLfloat r;
    GLfloat colors[3];


}circle;

circle c[10];
int a[10];
int initial[10] = { 7,10,3,5,6,8,9,1,4,2 };
GLfloat initial_x1, initial_x2;
int i = 0, j = 0;
int swapping = 0;
int sorting = 0;
int bsorting = 0;



void enteruser()
{
    cout << "enter the number of circles \n";
    cin >> n;

    printf("enter the values for the circles (between 1-10 only)\n");

    for (int ii = 0; ii<n; ii++)
    {
        cin >> initial[ii];
    }
}

void initialise()
{
    default_colors[0] = 0.3;
    default_colors[1] = 0.0;
    default_colors[2] = 0.3;

    i = j = swapping = 0; //reset all globals
    for (int i = 0; i<n; i++)
    {
        c[i].colors[0] = default_colors[0];
        c[i].colors[1] = default_colors[1];
        c[i].colors[2] = default_colors[2];
        a[i] = initial[i];
        c[i].r = a[i] * 4.0;
        c[i].y = 300.0;
        if (i == 0)
            c[i].x = 45.0;
        else
            c[i].x = c[i - 1].x + 90.0;//(c[i-1].r+c[i].r+10.0); //distance between circles = sum of 2 10 readii

    }
}

//func to display text on screen char by char
void bitmap_output(int x, int y, string input, void *font)
{
    int len, i;
    glRasterPos2f(x, y);
    len = input.length();
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(font, input[i]);
    }
}
void coverpage()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.7, 0.0, 0.0);
    bitmap_output(180.0, 475.0, "    RNS INSTITUTE OF TECHNOLOGY  ", GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(0.0, 0.2, 1.0);
    bitmap_output(175.0, 440.0, "DEPARTMENT OF COMPUTER SCIENCE", GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(0.7, 0.5, 0.06);
    bitmap_output(210.0, 375.0, "A MINI PROJECT ON", GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(0.3, 0.8, 0.4);
    bitmap_output(183.0, 340.0, "BUBBLE AND SELECTION SORT VISUALIZER", GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(0.7, 0.5, 0.06);
    bitmap_output(80.0, 250.0, "BY", GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(0.7, 0.5, 0.06);
    bitmap_output(400.0, 240.0, "GUIDES", GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(0.79, 0.37, 1.0);
    bitmap_output(40.0, 210.0, "ADITHYA S H :1RN15CS011", GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(0.79, 0.37, 1.0);
    bitmap_output(40.0, 190.0, "ANKUSH CHAVAN :1RN15CS020", GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(0.79, 0.37, 1.0);
    bitmap_output(370.0, 210.0, "Mrs.MAMATHA JAJUR", GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(0.79, 0.37, 1.0);
    bitmap_output(370.0, 190.0, "Mrs.SAMPADA K S", GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(0.15, 0.6, 0.25);
    bitmap_output(215.0, 10.0, "PRESS C TO START", GLUT_BITMAP_TIMES_ROMAN_24);
}
//function to integer to string
void int_str(int rad, char r[])
{
    switch (rad)
    {
    case 1: strcpy(r, "1"); break;
    case 2: strcpy(r, "2"); break;
    case 3: strcpy(r, "3"); break;
    case 4: strcpy(r, "4"); break;
    case 5: strcpy(r, "5"); break;
    case 6: strcpy(r, "6"); break;
    case 7: strcpy(r, "7"); break;
    case 8: strcpy(r, "8"); break;
    case 9: strcpy(r, "9"); break;
    case 10: strcpy(r, "10"); break;
    }

}


void circle_draw(circle c)
{

    float i;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(c.colors[0], c.colors[1], c.colors[2]);
    glVertex2f(c.x, c.y);    //center of circle
    for (i = 0; i<360; i += 1)
        glVertex2f(c.x + sin(i) * c.r, c.y + cos(i) * c.r);
    glEnd();

    //display the value of circle below
    int x = c.x - 2;
    int y = c.y - (c.r + 10);
    int rad = c.r / 4;
    char r[3] = "";
    int_str(rad, r);
    glColor3f(0.3, 0.0, 0.8);
    bitmap_output(x, y, r, GLUT_BITMAP_TIMES_ROMAN_10);

}


void swap_circles(circle *cc1, circle *cc2)
{
    cc1->colors[0] = 0.3;
    cc1->colors[1] = 0.3;
    cc1->colors[2] = 0.3;
    cc2->colors[0] = 0.3;
    cc2->colors[1] = 0.3;
    cc2->colors[2] = 0.3;


    if (swapping == 0)    //if circles are not being swapped set destination for each circles
    {
        initial_x1 = cc1->x;
        initial_x2 = cc2->x; //center of circle in right
        swapping = 1;    //means cicle are being swapped
        printf("%f - %f\n", cc1->r, cc2->r);

    }

    if (initial_x1 <= cc2->x)
        cc2->x -= 3.0;

    if (initial_x2 >= cc1->x)
        cc1->x += 3.0;

    printf("one %f - %f\n", initial_x1, cc2->x);
    printf("two %f - %f\n", initial_x2, cc1->x);

    // if difference between destination and center < 0.3 then cicles are swapped
    if (abs(initial_x1 - cc2->x) < 0.3 && abs(initial_x2 - cc1->x) < 0.3)  //set this to speed of animation
    {
        swapping = 0;

        int temp = cc1->x;
        cc1->x = cc2->x;
        cc2->x = temp;


        temp = cc1->y;
        cc1->y = cc2->y;
        cc2->y = temp;

        temp = cc1->r;
        cc1->r = cc2->r;
        cc2->r = temp;
    }

}


void sort()
{
    int pass = 0;
    if (!swapping)
    {
        while (i < n)
        {
            pass++;
            j = i;
            while (j < n)
            {
                if (a[i] > a[j])
                {
                    printf("%d %d\n", j, a[j]);
                    int temp = a[i];
                    a[i] = a[j];
                    a[j] = temp;
                    goto SWAP;

                }
                j++;
            }
            i++;
        }
    }
SWAP:
    printf("swapping --> %d - %d\n", i, j);
    bitmap_output(10, 375, "Swapping ->",GLUT_BITMAP_9_BY_15);
    bitmap_output(10, 395, "Passes", GLUT_BITMAP_9_BY_15);
    //bitmap_output(150, 395,pass, GLUT_BITMAP_9_BY_15);
    char r[3] = "";
    int_str(a[i], r);
    bitmap_output(150, 375, r, GLUT_BITMAP_9_BY_15);
    int_str(a[j], r);
    bitmap_output(175, 375, r, GLUT_BITMAP_9_BY_15);
    swap_circles(&c[i], &c[j]);
}
void bsort()
{
    if (!swapping)
    {
        while (i < n)
        {
            j = i;
            while (j < n - 1)
            {
                if (a[j] > a[j + 1])
                {
                    printf("%d %d\n", j, a[j]);
                    int temp = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = temp;
                    goto SWAP;

                }
                j++;
            }
            i++;
        }
    }
SWAP:
    printf("swapping --> %d - %d\n", j, j + 1);
    bitmap_output(10, 375, "Swapping ->",GLUT_BITMAP_9_BY_15);
    char r[3] = "";
    int_str(a[j], r);
    bitmap_output(150, 375, r, GLUT_BITMAP_9_BY_15);
    int_str(a[j + 1], r);
    bitmap_output(175, 375, r, GLUT_BITMAP_9_BY_15);
    swap_circles(&c[j], &c[j + 1]);

}
void display_text()
{


    if (sorting == 0 && bsorting == 0)//if not sorting display menu
    {

        bitmap_output(10, 455, "Press t to SELECTION-SORT", GLUT_BITMAP_9_BY_15);
        bitmap_output(10, 435, "Press s to BUBBLE-SORT", GLUT_BITMAP_9_BY_15);
        bitmap_output(10, 415, "Press r to RANDOMISE", GLUT_BITMAP_9_BY_15);
        bitmap_output(10, 395, "Esc to QUIT", GLUT_BITMAP_9_BY_15);
    }
    else if (sorting == 1 || bsorting == 1)
    {
        glColor3f(0.1, 0.3, 0.1);
        glColor3f(0.0, 0.0, 0.0);
    }

}



void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    if (flag == 0)
    {
        coverpage();
    }
    else
    {
        glClearColor(1, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(0.0, 0.0, 0.0);
        display_text();
        glPointSize(2.0);
        for (int ii = 0; ii < n; ii++)
        {

            circle_draw(c[ii]);
        }

        if (i < n && sorting == 1) // call sort only on key press
            sort();
        else if (j + 1 < n && bsorting == 1) // call sort only on key press
            bsort();
        else
        {
            sorting = 0;
            bsorting = 0;
        }
    }
    glFlush();
    glutSwapBuffers();

}

void keyboard(unsigned char key, int x, int y)
{

    k = 1;
    if (k == 1)
    {
        switch (key)
        {
        case 27: flag = 1;
            break;
        case 'c':flag = 1;
            break;
        case 's': bsorting = 1; break;

        case 'r': initialise(); break;
        case 't':  sorting = 1; break;
        }
    }
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w, 2.0* (GLfloat)h / (GLfloat)w, -10.0, 10.0);
    else
        glOrtho(-2.0 * (GLfloat)w / (GLfloat)h, 2.0* (GLfloat)w / (GLfloat)h, -2.0, 2.0, -10.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 900.0, 0.0, 600.0);
}

void main()
{

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("2sort");
    init();
    glutKeyboardFunc(keyboard);
        enteruser();
        initialise();
    glutDisplayFunc(display);
    glutIdleFunc(display);

    glutMainLoop();
}




