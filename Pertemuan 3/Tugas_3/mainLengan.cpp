#include <GL/glut.h>


static int shoulder = 0, elbow = 0, wrist = 0;
static int fingerBase[5] = {0, 0, 0, 0, 0};
static int fingerMid[5] = {0, 0, 0, 0, 0};
static int moveAll = 0;

void init(void){ 
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void drawFinger(int idx, float x, float y, float z, float length, float width) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef((GLfloat)fingerBase[idx], 0.0, 0.0, 1.0);
    glTranslatef(length/4, 0.0, 0.0);
    
    // Ruas jari bawah
    glPushMatrix();
    glScalef(length/2, width, width);
    glutWireCube(1.0);
    glPopMatrix();
    
    // Join atas bawah
    glTranslatef(length/4, 0.0, 0.0);
    glRotatef((GLfloat)fingerMid[idx], 0.0, 0.0, 1.0);
    glTranslatef(length/4, 0.0, 0.0);
    
    // Ruas jari bawah
    glPushMatrix();
    glScalef(length/2, width, width);
    glutWireCube(1.0);
    glPopMatrix();
    
    glPopMatrix();
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
 
    // Bahu
    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0); 
    
    // Lengan atas
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0); 
    glPopMatrix();
    
    // Siku
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0); 
    
    // Lengan Bawah
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();
    
    // Pergelangan
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)wrist, 0.0, 0.0, 1.0);
    glTranslatef(0.5, 0.0, 0.0);
    
    // Telapak tangan
    glPushMatrix();
    glScalef(1.0, 0.8, 1.0);
    glutWireCube(1.0);
    glPopMatrix();
    
    // Jari
    drawFinger(0, 0.0, -0.4, 0.3, 1.0, 0.2);  // Jempol
    drawFinger(1, 0.5, 0.2, 0.3, 1.0, 0.2);   // telunjuk
    drawFinger(2, 0.5, 0.0, 0.0, 1.1, 0.2);   // tengah
    drawFinger(3, 0.5, 0.0, -0.3, 1.0, 0.2);  // cincin
    drawFinger(4, 0.5, -0.2, -0.3, 0.9, 0.2); // kelingking
    
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat)w/(GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'a': moveAll = !moveAll; break;
        
        // Bahu
        case 's': shoulder = (shoulder + 5) % 360; break;
        case 'S': shoulder = (shoulder - 5) % 360; break;
        
        // Siku
        case 'e': elbow = (elbow + 5) % 360; break;
        case 'E': elbow = (elbow - 5) % 360; break;
        
        // Pergelangan
        case 'w': wrist = (wrist + 5) % 360; break;
        case 'W': wrist = (wrist - 5) % 360; break;
        
        // Jari
        case '1': case '2': case '3': case '4': case '5': {
            int idx = key - '1';
            fingerBase[idx] = (fingerBase[idx] + 5) % 90;
            if (moveAll) fingerMid[idx] = (fingerMid[idx] + 5) % 90;
            break;
        }
        case '!': case '@': case '#': case '$': case '%': {
            int idx = key == '!' ? 0 : key == '@' ? 1 : key == '#' ? 2 : key == '$' ? 3 : 4;
            fingerBase[idx] = (fingerBase[idx] - 5) % 90;
            if (moveAll) fingerMid[idx] = (fingerMid[idx] - 5) % 90;
            break;
        }
        
        // Jari bagian atas
        case 'q': fingerMid[0] = (fingerMid[0] + 5) % 180; break;
        case 'r': fingerMid[1] = (fingerMid[1] + 5) % 180; break;
        case 't': fingerMid[2] = (fingerMid[2] + 5) % 180; break;
        case 'y': fingerMid[3] = (fingerMid[3] + 5) % 180; break;
        case 'u': fingerMid[4] = (fingerMid[4] + 5) % 180; break;
        case 'Q': fingerMid[0] = (fingerMid[0] - 5) % 180; break;
        case 'R': fingerMid[1] = (fingerMid[1] - 5) % 180; break;
        case 'T': fingerMid[2] = (fingerMid[2] - 5) % 180; break;
        case 'Y': fingerMid[3] = (fingerMid[3] - 5) % 180; break;
        case 'U': fingerMid[4] = (fingerMid[4] - 5) % 180; break;
        
        // menutup semua jari
        case 'c': {
            for (int i = 0; i < 5; i++) {
                fingerBase[i] = (fingerBase[i] + 5) % 180;
                fingerMid[i] = (fingerMid[i] + 5) % 180;
            }
            break;
        }
        
        // membuka semua jari
        case 'o': {
            for (int i = 0; i < 5; i++) {
                fingerBase[i] = (fingerBase[i] - 5) % 180;
                fingerMid[i] = (fingerMid[i] - 5) % 180;
            }
            break;
        }
        
        case 27: exit(0); break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lengan Bergerak dengan Jari");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
