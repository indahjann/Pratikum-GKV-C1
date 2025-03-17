#include <GL/glut.h>

// Joint angles
static int shoulder = 0, elbow = 0, wrist = 0;
static int finger1 = 0, finger2 = 0, finger3 = 0, finger4 = 0, thumb = 0;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    
    // Shoulder joint and upper arm
    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef((GLfloat) shoulder, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();
    
    // Elbow joint and forearm
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat) elbow, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();
    
    // Wrist joint and palm
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat) wrist, 0.0, 0.0, 1.0);
    glTranslatef(0.5, 0.0, 0.0);
    
    glPushMatrix();
    glScalef(1.0, 0.8, 1.2);
    glutWireCube(1.0);
    glPopMatrix();
    
    // Finger 1 (index finger)
    glPushMatrix();
    glTranslatef(0.5, 0.2, 0.3);
    glRotatef((GLfloat) finger1, 0.0, 0.0, 1.0);
    glTranslatef(0.3, 0.0, 0.0);
    
    glPushMatrix();
    glScalef(0.6, 0.2, 0.2);
    glutWireCube(1.0);
    glPopMatrix();
    glPopMatrix();
    
    // Finger 2 (middle finger)
    glPushMatrix();
    glTranslatef(0.5, 0.2, 0.0);
    glRotatef((GLfloat) finger2, 0.0, 0.0, 1.0);
    glTranslatef(0.35, 0.0, 0.0);
    
    glPushMatrix();
    glScalef(0.7, 0.2, 0.2);
    glutWireCube(1.0);
    glPopMatrix();
    glPopMatrix();
    
    // Finger 3 (ring finger)
    glPushMatrix();
    glTranslatef(0.5, 0.2, -0.3);
    glRotatef((GLfloat) finger3, 0.0, 0.0, 1.0);
    glTranslatef(0.3, 0.0, 0.0);
    
    glPushMatrix();
    glScalef(0.6, 0.2, 0.2);
    glutWireCube(1.0);
    glPopMatrix();
    glPopMatrix();
    
    // Finger 4 (pinky)
    glPushMatrix();
    glTranslatef(0.5, 0.2, -0.5);
    glRotatef((GLfloat) finger4, 0.0, 0.0, 1.0);
    glTranslatef(0.25, 0.0, 0.0);
    
    glPushMatrix();
    glScalef(0.5, 0.15, 0.15);
    glutWireCube(1.0);
    glPopMatrix();
    glPopMatrix();
    
    // Thumb
    glPushMatrix();
    glTranslatef(0.3, -0.2, 0.5);
    glRotatef((GLfloat) thumb - 30, 1.0, 0.0, 1.0);
    glTranslatef(0.25, 0.0, 0.0);
    
    glPushMatrix();
    glScalef(0.5, 0.2, 0.2);
    glutWireCube(1.0);
    glPopMatrix();
    glPopMatrix();
    
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        // Shoulder controls
        case 's': shoulder = (shoulder + 5) % 360; break;
        case 'S': shoulder = (shoulder - 5) % 360; break;
        
        // Elbow controls
        case 'e': elbow = (elbow + 5) % 360; break;
        case 'E': elbow = (elbow - 5) % 360; break;
        
        // Wrist controls
        case 'w': wrist = (wrist + 5) % 360; break;
        case 'W': wrist = (wrist - 5) % 360; break;
        
        // Finger controls
        case '1': finger1 = (finger1 + 5) % 90; break;
        case '!': finger1 = (finger1 - 5) % 90; break;
        
        case '2': finger2 = (finger2 + 5) % 90; break;
        case '@': finger2 = (finger2 - 5) % 90; break;
        
        case '3': finger3 = (finger3 + 5) % 90; break;
        case '#': finger3 = (finger3 - 5) % 90; break;
        
        case '4': finger4 = (finger4 + 5) % 90; break;
        case '$': finger4 = (finger4 - 5) % 90; break;
        
        case '5': thumb = (thumb + 5) % 90; break;
        case '%': thumb = (thumb - 5) % 90; break;
        
        // All fingers at once
        case 'f': 
            finger1 = (finger1 + 5) % 90;
            finger2 = (finger2 + 5) % 90;
            finger3 = (finger3 + 5) % 90;
            finger4 = (finger4 + 5) % 90;
            thumb = (thumb + 5) % 90;
            break;
        case 'F': 
            finger1 = (finger1 - 5) % 90;
            finger2 = (finger2 - 5) % 90;
            finger3 = (finger3 - 5) % 90;
            finger4 = (finger4 - 5) % 90;
            thumb = (thumb - 5) % 90;
            break;
            
        case 27: exit(0); break;
        default: break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
