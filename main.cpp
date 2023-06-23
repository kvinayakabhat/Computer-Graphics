#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>
#include <stdio.h>
#define GL_PI 3.14
#define MAX 25
#define INFINITY 999

int n, i = 1, a[25], b[25], cost[25][25], tree[25][25], src, l[2], dist[10];
char s[20], *s1;
void *currentfont;

char *itoa(int num, char *buffer, int base)
{
    sprintf(buffer, "%d", num);
    return buffer;
}

// BELLMAN VARIABLES
typedef struct
{
    int u, v, w;
} Edge;

const int NODES = 5; /* the number of nodes */
int EDGES = 0;       /* the number of edges */
Edge edges[32];      /* large enough for n <= 2^NODES=32 */
int d[32];           /* d[i] is the minimum distance from source node s to node i */

// FUNCTION TO SELECT BITMAP FONT
void setFont(void *font)
{
    currentfont = font;
}

// FUNCTION TO DRAW BITMAP string at (x,y)
void drawstring(GLfloat x, GLfloat y, char *string)
{
    char *c;
    glRasterPos2f(x, y);

    for (c = string; *c != '\0'; *c++)
    {
        glutBitmapCharacter(currentfont, *c);
    }
}

// FUNCTION TO DELAY
void delay()
{
    for (int i = 0; i < 22000; i++)
        for (int j = 0; j < 22000; j++)
            ;
}

// DISPLAY FUNCTION FOR TITLE PAGE
void title()
{
    glLineWidth(3.0);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(10, 10);
    glVertex2f(10, 490);
    glVertex2f(490, 490);
    glVertex2f(490, 10);
    glEnd();

    setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(1.0, 1.0, 1.0);
    drawstring(100, 440, "Topic: Bellman Ford Algorithm");
    glColor3f(1.0, 1.0, 1.0);
    drawstring(100, 400, "Submitted by");
    glColor3f(1.0, 0.0, 0.0);
    drawstring(100, 360, "Abhishek Megotia");
    glColor3f(1.0, 0.0, 0.0);
    drawstring(100, 320, "VI CSE A");
    glColor3f(1.0, 0.0, 0.0);
    drawstring(100, 280, "1BG11CS003");
    glColor3f(1.0, 1.0, 1.0);
    drawstring(100, 100, "Right click in My Window for options");
    glFlush();
}

// DISPLAY FUNCTION FOR INITIALIZING (DRAWING) THE  INPUT AND OUTPUT AREAS
void initial()
{
    glClear(GL_COLOR_BUFFER_BIT);

    setFont(GLUT_BITMAP_HELVETICA_18);

    glColor3f(0.0, 0.0, 0.0);
    drawstring(20, 230, "Input Area");
    drawstring(300, 230, "Output Area");

    glLineWidth(2.0);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(20, 20);
    glVertex2f(20, 210);
    glVertex2f(250, 210);
    glVertex2f(250, 20);
    glEnd();

    glLineWidth(2.0);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(300, 20);
    glVertex2f(300, 210);
    glVertex2f(470, 210);
    glVertex2f(470, 20);
    glEnd();
    glFlush();
}

// FUNCTION TO DRAW BITMAP NUMBER AT (X,Y)
void raster(int x, int y, int num)
{
    int temp, j = 0;
    char str[20];

    temp = num;
    while (temp != 0)
    {
        l[j] = temp % 10;
        temp = temp / 10;
        j++;
    }
    j--;
    while (j >= 0)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, l[j] + 48);
        j--;
    }
}

// FUNCTION TO DRAW SQUARE AT (X,Y)
void drawSquare(GLint x, GLint y)
{
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + 40, y);
    glVertex2f(x + 40, y + 40);
    glVertex2f(x, y + 40);
    glEnd();
    glFlush();
}

// FUNCTION TO DRAW LINE BETWEEN NODES
void drawline()
{
    int i, j;
    glLineWidth(3.0);
    glColor3f(1.0, 0.0, 0.0);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (cost[i][j] != 0 && cost[i][j] != INFINITY)
            {
                glBegin(GL_LINES);
                glVertex2f(a[i], b[i]);
                glVertex2f(a[j], b[j]);
                glEnd();
            }
        }
    }
    glFlush();
}

// FUNCTION TO IMPLEMENT BELLMAN FORD ALGORITHM
void shortestpath()
{
    int k, current;
    for (i = 0; i < n; i++)
    {
        d[i] = INFINITY;
    }
    d[src] = 0;
    for (k = 1; k <= n - 1; k++)
    {
        for (i = 0; i < EDGES; i++)
        {
            if (d[edges[i].v] > d[edges[i].u] + edges[i].w)
            {
                d[edges[i].v] = d[edges[i].u] + edges[i].w;
                current = edges[i].v;
            }
        }
    }
    // Check for negative cycles
    for (i = 0; i < EDGES; i++)
    {
        if (d[edges[i].v] > d[edges[i].u] + edges[i].w)
        {
            printf("Negative cycle found.\n");
            return;
        }
    }
    printf("Shortest distances:\n");
    for (i = 0; i < n; i++)
    {
        printf("From %d to %d: %d\n", src, i, d[i]);
    }
}

// FUNCTION TO CALCULATE DISTANCE
float distance(int x1, int x2, int y1, int y2)
{
    float d;
    d = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    return d;
}

// FUNCTION TO CALCULATE COST MATRIX
void calculate_cost_matrix()
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i != j)
            {
                cost[i][j] = (int)distance(a[i], a[j], b[i], b[j]);
            }
            else
            {
                cost[i][j] = 0;
            }
        }
    }
}

// FUNCTION TO ADD EDGE TO THE GRAPH
void add_edge(int u, int v, int w)
{
    edges[EDGES].u = u;
    edges[EDGES].v = v;
    edges[EDGES].w = w;
    EDGES++;
}

// FUNCTION TO DRAW THE GRAPH
void draw_graph()
{
    int i;
    glPointSize(10.0);
    glColor3f(1.0, 0.0, 0.0);
    for (i = 0; i < n; i++)
    {
        glPushMatrix();
        glTranslatef(a[i], b[i], 0);
        glutSolidSphere(5, 20, 20);
        glPopMatrix();
    }
    drawline();
    glFlush();
}

// MOUSE FUNCTION
void MyMouse(int button, int state, int x, int y)
{
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        initial();
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (i <= n)
        {
            a[i] = x;
            b[i] = 480 - y;
            glColor3f(0.0, 0.0, 0.0);
            glPushMatrix();
            glTranslatef(x, 480 - y, 0);
            glutSolidSphere(5, 20, 20);
            glPopMatrix();
            glFlush();
            i++;
        }
    }
}

// KEYBOARD FUNCTION
void MyKeyboard(unsigned char key, int x, int y)
{
    if (key == 13) // ASCII value of Carriage Return
    {
        calculate_cost_matrix();
        draw_graph();
        glutMouseFunc(NULL);
    }
}

// FUNCTION TO DISPLAY THE COST MATRIX
void display_cost_matrix()
{
    int i, j;
    char buffer[10];
    setFont(GLUT_BITMAP_HELVETICA_12);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            glColor3f(0.0, 0.0, 0.0);
            itoa(cost[i][j], buffer, 10);
            drawstring(310 + j * 20, 200 - i * 20, buffer);
        }
    }
    glFlush();
}

// FUNCTION TO DISPLAY THE SHORTEST PATHS
void display_shortest_paths()
{
    int i;
    char buffer[10];
    setFont(GLUT_BITMAP_HELVETICA_12);
    for (i = 0; i < n; i++)
    {
        glColor3f(0.0, 0.0, 0.0);
        itoa(i, buffer, 10);
        drawstring(310, 200 - i * 20, buffer);
        if (d[i] == INFINITY)
        {
            glColor3f(1.0, 0.0, 0.0);
            drawstring(330, 200 - i * 20, "Infinity");
        }
        else
        {
            glColor3f(0.0, 0.0, 0.0);
            itoa(d[i], buffer, 10);
            drawstring(330, 200 - i * 20, buffer);
        }
    }
    glFlush();
}

// FUNCTION TO DISPLAY THE MENU
void display_menu()
{
    setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0.0, 0.0, 0.0);
    drawstring(330, 250, "MENU");
    glColor3f(0.0, 0.0, 0.0);
    drawstring(310, 200, "1. Input Graph");
    glColor3f(0.0, 0.0, 0.0);
    drawstring(310, 180, "2. Calculate Shortest Paths");
    glColor3f(0.0, 0.0, 0.0);
    drawstring(310, 160, "3. Display Cost Matrix");
    glColor3f(0.0, 0.0, 0.0);
    drawstring(310, 140, "4. Display Shortest Paths");
    glColor3f(0.0, 0.0, 0.0);
    drawstring(310, 120, "5. Exit");
    glFlush();
}

// FUNCTION TO SELECT FROM THE MENU
void select_menu(int option)
{
    switch (option)
    {
    case 1:
        glutMouseFunc(MyMouse);
        glutKeyboardFunc(NULL);
        break;
    case 2:
        shortestpath();
        break;
    case 3:
        display_cost_matrix();
        break;
    case 4:
        display_shortest_paths();
        break;
    case 5:
        exit(0);
        break;
    }
}

// RESHAPE FUNCTION
void MyReshape(GLsizei w, GLsizei h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// MAIN FUNCTION
void main(int argc, char **argv)
{
    printf("Enter the number of nodes in the graph: ");
    scanf("%d", &n);
    printf("Enter the source node: ");
    scanf("%d", &src);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Bellman Ford Algorithm");
    glutReshapeFunc(MyReshape);
    glutDisplayFunc(title);
    glutIdleFunc(title);

    glutCreateMenu(select_menu);
    glutAddMenuEntry("Input Graph", 1);
    glutAddMenuEntry("Calculate Shortest Paths", 2);
    glutAddMenuEntry("Display Cost Matrix", 3);
    glutAddMenuEntry("Display Shortest Paths", 4);
    glutAddMenuEntry("Exit", 5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glutMainLoop();
}
