#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Variabel global
int windowWidth = 800;                // Lebar jendela aplikasi
int windowHeight = 600;               // Tinggi jendela aplikasi
float rotationX = 0.0f;               // Rotasi pada sumbu X
float rotationY = 0.0f;               // Rotasi pada sumbu Y
int projectionMode = 0;               // 0=plan, 1=front, 2=side, 3=isometric, 
								      // 4=dimetric, 5=trimetric, 6=1pt, 7=2pt, 8=3pt
const int TOTAL_PROJECTIONS = 9;      // Jumlah total mode proyeksi
const char* projectionNames[] = {"Plan View", "Front View", "Side View", "Isometric", 
                                "Dimetric", "Trimetric", "1-Point Perspective", 
                                "2-Point Perspective", "3-Point Perspective"};

// Warna-warna dasar
float red[] = {1.0f, 0.0f, 0.0f};         // Merah
float green[] = {0.0f, 1.0f, 0.0f};       // Hijau
float blue[] = {0.0f, 0.0f, 1.0f};        // Biru
float yellow[] = {1.0f, 1.0f, 0.0f};      // Kuning
float cyan[] = {0.0f, 1.0f, 1.0f};        // Cyan
float magenta[] = {1.0f, 0.0f, 1.0f};     // Magenta
float white[] = {1.0f, 1.0f, 1.0f};       // Putih
float gray[] = {0.5f, 0.5f, 0.5f};        // Abu-abu
float darkBrown[] = {0.4f, 0.2f, 0.0f};   // Coklat tua

// warna kursi
float brightOrange[] = {1.0f, 0.6f, 0.0f};       // Warna utama kursi (oranye cerah)
float lighterOrange[] = {1.0f, 0.7f, 0.2f};      // Warna alas kursi (oranye muda)
float darkerOrange[] = {0.8f, 0.4f, 0.0f};       // Warna kaki kursi (oranye tua)
float orangeHighlight[] = {1.0f, 0.8f, 0.4f};    // Warna aksen (oranye terang)
float orangeShadow[] = {0.7f, 0.35f, 0.0f};      // Warna bayangan (oranye gelap)
float black[] = {0.1f, 0.1f, 0.1f};              // Warna garis tepi (hitam)

// Fungsi untuk menggambar kubus dengan garis tepi
void drawCube(float size, float lineWidth) {
    // Menyimpan warna saat ini
    float currentColor[4];
    glGetFloatv(GL_CURRENT_COLOR, currentColor);
    
    glBegin(GL_QUADS);
    // Sisi depan
    glVertex3f(-size/2, -size/2, size/2);
    glVertex3f(size/2, -size/2, size/2);
    glVertex3f(size/2, size/2, size/2);
    glVertex3f(-size/2, size/2, size/2);
    
    // Sisi belakang
    glVertex3f(-size/2, -size/2, -size/2);
    glVertex3f(-size/2, size/2, -size/2);
    glVertex3f(size/2, size/2, -size/2);
    glVertex3f(size/2, -size/2, -size/2);
    
    // Sisi kiri
    glVertex3f(-size/2, -size/2, -size/2);
    glVertex3f(-size/2, -size/2, size/2);
    glVertex3f(-size/2, size/2, size/2);
    glVertex3f(-size/2, size/2, -size/2);
    
    // Sisi kanan
    glVertex3f(size/2, -size/2, -size/2);
    glVertex3f(size/2, size/2, -size/2);
    glVertex3f(size/2, size/2, size/2);
    glVertex3f(size/2, -size/2, size/2);
    
    // Sisi atas
    glVertex3f(-size/2, size/2, -size/2);
    glVertex3f(-size/2, size/2, size/2);
    glVertex3f(size/2, size/2, size/2);
    glVertex3f(size/2, size/2, -size/2);
    
    // Sisi bawah
    glVertex3f(-size/2, -size/2, -size/2);
    glVertex3f(size/2, -size/2, -size/2);
    glVertex3f(size/2, -size/2, size/2);
    glVertex3f(-size/2, -size/2, size/2);
    glEnd();
    
    // Garis tepi
    if (lineWidth > 0) {
        glColor3fv(black);            // hitam untuk garis tepi
        glLineWidth(lineWidth);       // ketebalan garis
        
        // outline depan
        glBegin(GL_LINE_LOOP);
        glVertex3f(-size/2, -size/2, size/2);
        glVertex3f(size/2, -size/2, size/2);
        glVertex3f(size/2, size/2, size/2);
        glVertex3f(-size/2, size/2, size/2);
        glEnd();
        
        // outline belakang
        glBegin(GL_LINE_LOOP);
        glVertex3f(-size/2, -size/2, -size/2);
        glVertex3f(-size/2, size/2, -size/2);
        glVertex3f(size/2, size/2, -size/2);
        glVertex3f(size/2, -size/2, -size/2);
        glEnd();
        
        // penghubung
        glBegin(GL_LINES);
        glVertex3f(-size/2, -size/2, size/2);
        glVertex3f(-size/2, -size/2, -size/2);
        
        glVertex3f(size/2, -size/2, size/2);
        glVertex3f(size/2, -size/2, -size/2);
        
        glVertex3f(size/2, size/2, size/2);
        glVertex3f(size/2, size/2, -size/2);
        
        glVertex3f(-size/2, size/2, size/2);
        glVertex3f(-size/2, size/2, -size/2);
        glEnd();
        
        // warna asli
        glColor4fv(currentColor);
        glLineWidth(1.0f);    // ketebalan garis default
    }
}

// Menggambar balok persegi panjang
void drawRectPrism(float width, float height, float depth, float lineWidth) {
    glPushMatrix();
    glScalef(width, height, depth); 
    drawCube(1.0f, lineWidth);
    glPopMatrix();
}

// Menggambar kursi
void drawChair() {
    // Alas kursi
    glColor3fv(lighterOrange);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    drawRectPrism(2.5f, 0.3f, 2.5f, 2.0f);
    glPopMatrix();
    
    // Sandaran kursi
    glColor3fv(brightOrange); 
    glPushMatrix();
    glTranslatef(0.0f, 1.5f, -1.1f);
    drawRectPrism(2.5f, 2.5f, 0.3f, 2.0f);
    glPopMatrix();
    
    // Penyangga sandaran kursi
    glColor3fv(darkerOrange);
    
    // Penyangga sandaran kiri
    glPushMatrix();
    glTranslatef(-1.0f, 0.0f, -1.1f);
    drawRectPrism(0.3f, 1.2f, 0.3f, 2.0f);
    glPopMatrix();
    
    // Penyangga sandaran kanan
    glPushMatrix();
    glTranslatef(1.0f, 0.0f, -1.1f); 
    drawRectPrism(0.3f, 1.2f, 0.3f, 2.0f);
    glPopMatrix();
    
    // Kaki-kaki kursi
    glColor3fv(darkerOrange);
    
    // Kaki depan-kiri
    glPushMatrix();
    glTranslatef(-1.0f, -1.0f, 1.0f);
    drawRectPrism(0.3f, 1.7f, 0.3f, 2.0f);
    glPopMatrix();
    
    // Kaki depan-kanan
    glPushMatrix();
    glTranslatef(1.0f, -1.0f, 1.0f);
    drawRectPrism(0.3f, 1.7f, 0.3f, 2.0f);
    glPopMatrix();
    
    // Kaki belakang-kiri
    glPushMatrix();
    glTranslatef(-1.0f, -1.0f, -1.0f);
    drawRectPrism(0.3f, 1.7f, 0.3f, 2.0f);
    glPopMatrix();
    
    // Kaki belakang-kanan
    glPushMatrix();
    glTranslatef(1.0f, -1.0f, -1.0f);
    drawRectPrism(0.3f, 1.7f, 0.3f, 2.0f);
    glPopMatrix();
    
    // Dekorasi pada sandaran kursi (batang horizontal)
    glColor3fv(orangeHighlight);
    glPushMatrix();
    glTranslatef(0.0f, 1.5f, -1.05f);
    drawRectPrism(2.3f, 0.2f, 0.1f, 1.0f);
    glPopMatrix();
}

// Sumbu koordinat
void drawAxes() {
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    
    // Sumbu X (merah)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(10.0f, 0.0f, 0.0f);
    
    // Sumbu Y (hijau)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 10.0f, 0.0f);
    
    // Sumbu Z (biru)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 10.0f);
    glEnd();
    glLineWidth(1.0f);
}


void setProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    float aspectRatio = (float)windowWidth / (float)windowHeight;
    
    switch (projectionMode) {
        case 0: // Tampilan plan (ortografik dari atas)
            glOrtho(-10.0f * aspectRatio, 10.0f * aspectRatio, -10.0f, 10.0f, -100.0f, 100.0f);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(0.0f, 10.0f, 0.0f,
                      0.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 1.0f);
            break;
            
        case 1: // Tampilan depan (ortografik)
            glOrtho(-10.0f * aspectRatio, 10.0f * aspectRatio, -10.0f, 10.0f, -100.0f, 100.0f);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(0.0f, 0.0f, 10.0f,
                      0.0f, 0.0f, 0.0f,
                      0.0f, 1.0f, 0.0f);
            break;
            
        case 2: // Tampilan samping (ortografik)
            glOrtho(-10.0f * aspectRatio, 10.0f * aspectRatio, -10.0f, 10.0f, -100.0f, 100.0f);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(10.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 0.0f,
                      0.0f, 1.0f, 0.0f);
            break;
            
        case 3: // Isometrik (semua sudut sama)
            glOrtho(-10.0f * aspectRatio, 10.0f * aspectRatio, -10.0f, 10.0f, -100.0f, 100.0f);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(5.77f, 5.77f, 5.77f,
                      0.0f, 0.0f, 0.0f,
                      0.0f, 1.0f, 0.0f);
            break;
            
        case 4: // Dimetrik (dua sudut sama)
            glOrtho(-10.0f * aspectRatio, 10.0f * aspectRatio, -10.0f, 10.0f, -100.0f, 100.0f);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(8.66f, 5.0f, 5.0f,
                      0.0f, 0.0f, 0.0f,
                      0.0f, 1.0f, 0.0f);
            break;
            
        case 5: // Trimetrik (semua sudut berbeda)
            glOrtho(-10.0f * aspectRatio, 10.0f * aspectRatio, -10.0f, 10.0f, -100.0f, 100.0f);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(7.0f, 4.0f, 6.0f,
                      0.0f, 0.0f, 0.0f,
                      0.0f, 1.0f, 0.0f);
            break;
            
        case 6: // Perspektif 1-Titik
            gluPerspective(45.0f, aspectRatio, 0.1f, 100.0f);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(0.0f, 0.0f, 10.0f, 
                      0.0f, 0.0f, 0.0f,  
                      0.0f, 1.0f, 0.0f); 
            break;
            
        case 7: // Perspektif 2-Titik
            gluPerspective(45.0f, aspectRatio, 0.1f, 100.0f);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(8.0f, 0.0f, 8.0f, 
                      0.0f, 0.0f, 0.0f,
                      0.0f, 1.0f, 0.0f);
            break;
            
        case 8: // Perspektif 3-Titik
            gluPerspective(45.0f, aspectRatio, 0.1f, 100.0f);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(8.0f, 5.0f, 8.0f,
                      0.0f, 0.0f, 0.0f,
                      0.0f, 1.0f, 0.0f);
            break;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    setProjection();

    glRotatef(rotationX, 1.0f, 0.0f, 0.0f); 
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f); 

    drawAxes();
    

    drawChair();
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2i(10, windowHeight - 20);
    const char* projName = projectionNames[projectionMode];
    for (int i = 0; projName[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, projName[i]);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    
    glutSwapBuffers();
}

// perubahan ukuran jendela
void reshape(int w, int h) {
    windowWidth = w; 
    windowHeight = h;
    glViewport(0, 0, w, h);
}

// input keyboard
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // Tombol ESC - keluar dari program
            exit(0);
            break;
        case ' ': // Tombol spasi - ganti mode proyeksi
            projectionMode = (projectionMode + 1) % TOTAL_PROJECTIONS;
            break;
        case 'w': // Rotasi ke atas pada sumbu X
            rotationX += 5.0f;
            break;
        case 's': // Rotasi ke bawah pada sumbu X
            rotationX -= 5.0f;
            break;
        case 'a': // Rotasi ke kiri pada sumbu Y
            rotationY -= 5.0f;
            break;
        case 'd': // Rotasi ke kanan pada sumbu Y
            rotationY += 5.0f;
            break;
        case 'r': // Reset rotasi
            rotationX = 0.0f;
            rotationY = 0.0f;
            break;
        case '1': // Tampilan plan
            projectionMode = 0;
            break;
        case '2': // Tampilan depan
            projectionMode = 1;
            break;
        case '3': // Tampilan samping
            projectionMode = 2;
            break;
        case '4': // Isometrik
            projectionMode = 3;
            break;
        case '5': // Dimetrik
            projectionMode = 4;
            break;
        case '6': // Trimetrik
            projectionMode = 5;
            break;
        case '7': // Perspektif 1-Titik
            projectionMode = 6;
            break;
        case '8': // Perspektif 2-Titik
            projectionMode = 7;
            break;
        case '9': // Perspektif 3-Titik
            projectionMode = 8;
            break;
    }
    glutPostRedisplay();
}

// Fungsi untuk menangani tombol khusus
void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:    // panah atas - rotasi ke atas pada sumbu X
            rotationX += 5.0f;
            break;
        case GLUT_KEY_DOWN:  // panah bawah - rotasi ke bawah pada sumbu X
            rotationX -= 5.0f;
            break;
        case GLUT_KEY_LEFT:  // panah kiri - rotasi ke kiri pada sumbu Y
            rotationY -= 5.0f;
            break;
        case GLUT_KEY_RIGHT: // panah kanan - rotasi ke kanan pada sumbu Y
            rotationY += 5.0f;
            break;
    }
    glutPostRedisplay();
}

// Inisialisasi OpenGL
void init() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    glShadeModel(GL_FLAT);
}

// Fungsi utama
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("3D Stylized Chair Projections Demo");
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    
    printf("Controls:\n");
    printf("Space: Change projection mode\n");
    printf("1-9: Select specific projection\n");
    printf("W/S or Up/Down: Rotate around X-axis\n");
    printf("A/D or Left/Right: Rotate around Y-axis\n");
    printf("R: Reset rotation\n");
    printf("ESC: Exit\n");
    
    glutMainLoop();
    return 0;
}

