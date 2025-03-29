#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PI 3.1415926535898

float angle=0.0, deltaAngle = 0.0, ratio;
float x=0.0f,y=1.75f,z=15.0f; // posisi awal kamera
float lx=0.0f,ly=0.0f,lz=-1.0f;
int deltaMove = 0,h,w;
int bitmapHeight=12;
float busAngle = 0.0; // Untuk rotasi roda

// Fungsi untuk membuat lingkaran
void drawCircle(float cx, float cy, float cz, float radius, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(cx, cy, cz); // Titik tengah
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * PI * i / segments;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex3f(cx + x, cy + y, cz);
    }
    glEnd();
}

// Fungsi untuk membuat silinder (roda 3D)
void drawCylinder(float cx, float cy, float cz, float radius, float height, int segments) {
    // Sisi atas
    glPushMatrix();
    glTranslatef(cx, cy, cz);
    drawCircle(0, 0, height/2, radius, segments);
    
    // Sisi bawah
    drawCircle(0, 0, -height/2, radius, segments);
    
    // Dinding silinder
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * PI * i / segments;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        
        glVertex3f(x, y, height/2);
        glVertex3f(x, y, -height/2);
    }
    glEnd();
    glPopMatrix();
}

// Fungsi untuk menggambar roda 3D
void drawWheel3D(float cx, float cy, float cz, float radius, float width) {
    glPushMatrix();
    glTranslatef(cx, cy, cz);
    
    // Rotasi roda
    glRotatef(busAngle * -360, 0.0, 0.0, 1.0);
    
    // Ban luar (hitam)
    glColor3f(0.1, 0.1, 0.1);
    drawCylinder(0, 0, 0, radius, width, 30);
    
    // Velg (abu-abu)
    glColor3f(0.7, 0.7, 0.7);
    drawCylinder(0, 0, 0, radius * 0.6, width+0.01, 30);
    
    // Pusat velg
    glColor3f(0.5, 0.5, 0.5);
    drawCylinder(0, 0, 0, radius * 0.2, width+0.02, 20);
    
    // Jari-jari velg
    glColor3f(0.6, 0.6, 0.6);
    for (int i = 0; i < 6; i++) {
        float angle = i * PI / 3;
        glPushMatrix();
        glRotatef(angle * 180/PI, 0, 0, 1);
        glBegin(GL_QUADS);
            glVertex3f(-0.03, radius*0.2, width/2+0.01);
            glVertex3f(0.03, radius*0.2, width/2+0.01);
            glVertex3f(0.03, radius*0.6, width/2+0.01);
            glVertex3f(-0.03, radius*0.6, width/2+0.01);
            
            glVertex3f(-0.03, radius*0.2, -width/2-0.01);
            glVertex3f(0.03, radius*0.2, -width/2-0.01);
            glVertex3f(0.03, radius*0.6, -width/2-0.01);
            glVertex3f(-0.03, radius*0.6, -width/2-0.01);
        glEnd();
        glPopMatrix();
    }
    
    glPopMatrix();
}

void drawBus3D() {
    // MEMPERBESAR UKURAN BUS
    float length = 3.5;  // Panjang bus
    float width = 1.5;   // Lebar bus
    float height = 1.8;  // Tinggi bus
    float cabinHeight = 0.7; // Tinggi kabin
    
    // BADAN BUS - DENGAN WARNA LEBIH CERAH DI BAGIAN ATAS
    // Bagian bawah bus (body) - menggunakan warna coklat keemasan seperti di 2D
    glColor3f(0.8, 0.5, 0.0); // Warna lebih gelap untuk bagian bawah
    
    // Sisi depan
    glBegin(GL_QUADS);
        glVertex3f(length/2, -height/2, width/2);
        glVertex3f(length/2, -height/2, -width/2);
        glVertex3f(length/2, -height/2 + 0.25*height, -width/2);
        glVertex3f(length/2, -height/2 + 0.25*height, width/2);
    glEnd();
    
    // Sisi belakang
    glBegin(GL_QUADS);
        glVertex3f(-length/2, -height/2, width/2);
        glVertex3f(-length/2, -height/2, -width/2);
        glVertex3f(-length/2, -height/2 + 0.25*height, -width/2);
        glVertex3f(-length/2, -height/2 + 0.25*height, width/2);
    glEnd();
    
    // Sisi kanan
    glBegin(GL_QUADS);
        glVertex3f(-length/2, -height/2, width/2);
        glVertex3f(length/2, -height/2, width/2);
        glVertex3f(length/2, -height/2 + 0.25*height, width/2);
        glVertex3f(-length/2, -height/2 + 0.25*height, width/2);
    glEnd();
    
    // Sisi kiri
    glBegin(GL_QUADS);
        glVertex3f(-length/2, -height/2, -width/2);
        glVertex3f(length/2, -height/2, -width/2);
        glVertex3f(length/2, -height/2 + 0.25*height, -width/2);
        glVertex3f(-length/2, -height/2 + 0.25*height, -width/2);
    glEnd();
    
    // Alas bus
    glBegin(GL_QUADS);
        glVertex3f(-length/2, -height/2, width/2);
        glVertex3f(length/2, -height/2, width/2);
        glVertex3f(length/2, -height/2, -width/2);
        glVertex3f(-length/2, -height/2, -width/2);
    glEnd();
    
    // Bagian tengah bus (body) - warna kuning cerah seperti di 2D
    glColor3f(1.0, 0.8, 0.0);
    
    // Sisi depan
    glBegin(GL_QUADS);
        glVertex3f(length/2, -height/2 + 0.25*height, width/2);
        glVertex3f(length/2, -height/2 + 0.25*height, -width/2);
        glVertex3f(length/2, 0, -width/2);
        glVertex3f(length/2, 0, width/2);
    glEnd();
    
    // Sisi belakang
    glBegin(GL_QUADS);
        glVertex3f(-length/2, -height/2 + 0.25*height, width/2);
        glVertex3f(-length/2, -height/2 + 0.25*height, -width/2);
        glVertex3f(-length/2, 0, -width/2);
        glVertex3f(-length/2, 0, width/2);
    glEnd();
    
    // Sisi kanan
    glBegin(GL_QUADS);
        glVertex3f(-length/2, -height/2 + 0.25*height, width/2);
        glVertex3f(length/2, -height/2 + 0.25*height, width/2);
        glVertex3f(length/2, 0, width/2);
        glVertex3f(-length/2, 0, width/2);
    glEnd();
    
    // Sisi kiri
    glBegin(GL_QUADS);
        glVertex3f(-length/2, -height/2 + 0.25*height, -width/2);
        glVertex3f(length/2, -height/2 + 0.25*height, -width/2);
        glVertex3f(length/2, 0, -width/2);
        glVertex3f(-length/2, 0, -width/2);
    glEnd();
    
    // Bagian atas bus (cabin) - warna kuning cerah seperti di 2D
    glColor3f(1.0, 0.8, 0.0);
    
    // Interior (top)
    glBegin(GL_QUADS);
        glVertex3f(-length/2, 0, width/2);
        glVertex3f(length/2 - 0.6, 0, width/2);
        glVertex3f(length/2 - 0.6, 0, -width/2);
        glVertex3f(-length/2, 0, -width/2);
    glEnd();
    
    // Atap cabin
    glBegin(GL_QUADS);
        glVertex3f(-length/2, cabinHeight, width/2);
        glVertex3f(length/2 - 0.6, cabinHeight, width/2);
        glVertex3f(length/2 - 0.6, cabinHeight, -width/2);
        glVertex3f(-length/2, cabinHeight, -width/2);
    glEnd();
    
    // Sisi kanan kabin
    glBegin(GL_QUADS);
        glVertex3f(-length/2, 0, width/2);
        glVertex3f(length/2 - 0.6, 0, width/2);
        glVertex3f(length/2 - 0.6, cabinHeight, width/2);
        glVertex3f(-length/2, cabinHeight, width/2);
    glEnd();
    
    // Sisi kiri kabin
    glBegin(GL_QUADS);
        glVertex3f(-length/2, 0, -width/2);
        glVertex3f(length/2 - 0.6, 0, -width/2);
        glVertex3f(length/2 - 0.6, cabinHeight, -width/2);
        glVertex3f(-length/2, cabinHeight, -width/2);
    glEnd();
    
    // Belakang kabin
    glBegin(GL_QUADS);
        glVertex3f(-length/2, 0, width/2);
        glVertex3f(-length/2, 0, -width/2);
        glVertex3f(-length/2, cabinHeight, -width/2);
        glVertex3f(-length/2, cabinHeight, width/2);
    glEnd();
    
    // Depan kabin
    glBegin(GL_QUADS);
        glVertex3f(length/2 - 0.6, 0, width/2);
        glVertex3f(length/2 - 0.6, 0, -width/2);
        glVertex3f(length/2 - 0.6, cabinHeight, -width/2);
        glVertex3f(length/2 - 0.6, cabinHeight, width/2);
    glEnd();
    
    // Garis atap/trim bus (top rim) - warna oranye seperti di 2D
    glColor3f(1.0, 0.6, 0.0);
    glBegin(GL_QUADS);
        glVertex3f(-length/2, cabinHeight, width/2);
        glVertex3f(length/2 - 0.6, cabinHeight, width/2);
        glVertex3f(length/2 - 0.7, cabinHeight + 0.12, width/2 - 0.15);
        glVertex3f(-length/2 + 0.1, cabinHeight + 0.12, width/2 - 0.15);
        
        glVertex3f(-length/2, cabinHeight, -width/2);
        glVertex3f(length/2 - 0.6, cabinHeight, -width/2);
        glVertex3f(length/2 - 0.7, cabinHeight + 0.12, -width/2 + 0.15);
        glVertex3f(-length/2 + 0.1, cabinHeight + 0.12, -width/2 + 0.15);
        
        glVertex3f(-length/2, cabinHeight, width/2);
        glVertex3f(-length/2, cabinHeight, -width/2);
        glVertex3f(-length/2 + 0.1, cabinHeight + 0.12, -width/2 + 0.15);
        glVertex3f(-length/2 + 0.1, cabinHeight + 0.12, width/2 - 0.15);
        
        glVertex3f(length/2 - 0.6, cabinHeight, width/2);
        glVertex3f(length/2 - 0.6, cabinHeight, -width/2);
        glVertex3f(length/2 - 0.7, cabinHeight + 0.12, -width/2 + 0.15);
        glVertex3f(length/2 - 0.7, cabinHeight + 0.12, width/2 - 0.15);
    glEnd();
    
    // Atap trim
    glBegin(GL_QUADS);
        glVertex3f(-length/2 + 0.1, cabinHeight + 0.12, width/2 - 0.15);
        glVertex3f(length/2 - 0.7, cabinHeight + 0.12, width/2 - 0.15);
        glVertex3f(length/2 - 0.7, cabinHeight + 0.12, -width/2 + 0.15);
        glVertex3f(-length/2 + 0.1, cabinHeight + 0.12, -width/2 + 0.15);
    glEnd();
    
    // GARIS TENGAH (horizontal stripe) seperti di bus 2D
    glColor3f(1.0, 0.6, 0.0);
    glBegin(GL_QUADS);
        // Sisi kanan
        glVertex3f(-length/2, -height/4, width/2 + 0.01);
        glVertex3f(length/2 - 0.8, -height/4, width/2 + 0.01);
        glVertex3f(length/2 - 0.8, -height/4 + 0.05, width/2 + 0.01);
        glVertex3f(-length/2, -height/4 + 0.05, width/2 + 0.01);
        
        // Sisi kiri
        glVertex3f(-length/2, -height/4, -width/2 - 0.01);
        glVertex3f(length/2 - 0.8, -height/4, -width/2 - 0.01);
        glVertex3f(length/2 - 0.8, -height/4 + 0.05, -width/2 - 0.01);
        glVertex3f(-length/2, -height/4 + 0.05, -width/2 - 0.01);
    glEnd();
    
    // GARIS BAWAH JENDELA seperti di bus 2D
    glColor3f(1.0, 0.6, 0.0);
    glBegin(GL_QUADS);
        // Sisi kanan
        glVertex3f(-length/2, 0.1, width/2 + 0.01);
        glVertex3f(length/2 - 0.6, 0.1, width/2 + 0.01);
        glVertex3f(length/2 - 0.6, 0.1 + 0.02, width/2 + 0.01);
        glVertex3f(-length/2, 0.1 + 0.02, width/2 + 0.01);
        
        // Sisi kiri
        glVertex3f(-length/2, 0.1, -width/2 - 0.01);
        glVertex3f(length/2 - 0.6, 0.1, -width/2 - 0.01);
        glVertex3f(length/2 - 0.6, 0.1 + 0.02, -width/2 - 0.01);
        glVertex3f(-length/2, 0.1 + 0.02, -width/2 - 0.01);
    glEnd();

    // JENDELA BUS - UKURAN DAN JARAK YANG DIPERBARUI
    glColor3f(0.7, 0.9, 1.0);
    
    // Ukuran jendela yang lebih kecil
    float windowWidth = 0.35;  // Ukuran jendela tetap sama
    float windowHeight = 0.5;
    float windowY = 0.15;
    float windowSpacing = 0.15; // Jarak antar jendela diperkecil dari 0.25 menjadi 0.15
    int windowCount = 5; // Jumlah jendela
    
    // Jendela sisi kanan
    for (int i = 0; i < windowCount; i++) {
        float windowX = -length/2 + 0.2 + i * (windowWidth + windowSpacing);
        
        // Posisi pintu dipindahkan ke posisi window[3] (index 3)
        if (i == 3) continue;
        
        glBegin(GL_QUADS);
            glVertex3f(windowX, windowY, width/2 + 0.01);
            glVertex3f(windowX + windowWidth, windowY, width/2 + 0.01);
            glVertex3f(windowX + windowWidth, windowY + windowHeight, width/2 + 0.01);
            glVertex3f(windowX, windowY + windowHeight, width/2 + 0.01);
        glEnd();
    }
    
    // Jendela sisi kiri (sama dengan kanan)
    for (int i = 0; i < windowCount; i++) {
        float windowX = -length/2 + 0.2 + i * (windowWidth + windowSpacing);
        
        // Posisi pintu dipindahkan ke posisi window[3] (index 3)
        if (i == 3) continue;
        
        glBegin(GL_QUADS);
            glVertex3f(windowX, windowY, -width/2 - 0.01);
            glVertex3f(windowX + windowWidth, windowY, -width/2 - 0.01);
            glVertex3f(windowX + windowWidth, windowY + windowHeight, -width/2 - 0.01);
            glVertex3f(windowX, windowY + windowHeight, -width/2 - 0.01);
        glEnd();
    }
    
    // Jendela depan bus
    glBegin(GL_QUADS);
        glVertex3f(length/2 - 0.6, windowY + 0.2, width/4);
        glVertex3f(length/2 - 0.6, windowY + 0.2, -width/4);
        glVertex3f(length/2 - 0.6, windowY + windowHeight, -width/4);
        glVertex3f(length/2 - 0.6, windowY + windowHeight, width/4);
    glEnd();
    
    // PINTU BUS - DIPERLEBAR
    // Posisi pintu dipindahkan ke posisi window[3] (index 3)
    float doorX = -length/2 + 0.2 + 3 * (windowWidth + windowSpacing);
    float doorWidth = windowWidth * 1.5; // Pintu diperlebar 50% dari lebar jendela
    float doorHeight = cabinHeight - 0.1;
    
    // Frame pintu (bagian luar) - warna oranye
    glColor3f(1.0, 0.6, 0.0);
    glBegin(GL_QUADS);
        glVertex3f(doorX, -height/3, width/2 + 0.01);
        glVertex3f(doorX + doorWidth, -height/3, width/2 + 0.01);
        glVertex3f(doorX + doorWidth, doorHeight, width/2 + 0.01);
        glVertex3f(doorX, doorHeight, width/2 + 0.01);
    glEnd();
    
    // Bagian dalam pintu - warna kuning cerah
    glColor3f(1.0, 0.8, 0.0);
    glBegin(GL_QUADS);
        glVertex3f(doorX + 0.02, -height/3, width/2 + 0.02);
        glVertex3f(doorX + doorWidth - 0.02, -height/3, width/2 + 0.02);
        glVertex3f(doorX + doorWidth - 0.02, doorHeight - 0.02, width/2 + 0.02);
        glVertex3f(doorX + 0.02, doorHeight - 0.02, width/2 + 0.02);
    glEnd();
    
    // Garis tengah pintu seperti di 2D
    glColor3f(1.0, 0.6, 0.0);
    glBegin(GL_QUADS);
        glVertex3f(doorX + doorWidth/2 - 0.03, -height/3, width/2 + 0.03);
        glVertex3f(doorX + doorWidth/2 + 0.03, -height/3, width/2 + 0.03);
        glVertex3f(doorX + doorWidth/2 + 0.03, doorHeight - 0.02, width/2 + 0.03);
        glVertex3f(doorX + doorWidth/2 - 0.03, doorHeight - 0.02, width/2 + 0.03);
    glEnd();
    
    // Jendela pintu - dua panel jendela
    glColor3f(0.7, 0.9, 1.0);
    
    // Jendela kiri pintu
    glBegin(GL_QUADS);
        glVertex3f(doorX + 0.05, windowY, width/2 + 0.04);
        glVertex3f(doorX + doorWidth/2 - 0.05, windowY, width/2 + 0.04);
        glVertex3f(doorX + doorWidth/2 - 0.05, doorHeight - 0.05, width/2 + 0.04);
        glVertex3f(doorX + 0.05, doorHeight - 0.05, width/2 + 0.04);
    glEnd();
    
    // Jendela kanan pintu
    glBegin(GL_QUADS);
        glVertex3f(doorX + doorWidth/2 + 0.05, windowY, width/2 + 0.04);
        glVertex3f(doorX + doorWidth - 0.05, windowY, width/2 + 0.04);
        glVertex3f(doorX + doorWidth - 0.05, doorHeight - 0.05, width/2 + 0.04);
        glVertex3f(doorX + doorWidth/2 + 0.05, doorHeight - 0.05, width/2 + 0.04);
    glEnd();
    
    // GARIS BAWAH DAN TRIM
    glColor3f(0.0, 0.0, 0.0);
    
    // Garis bawah kanan - Membuat garis hitam seperti di 2D
    glBegin(GL_QUADS);
        glVertex3f(-length/2, -height/2 + 0.2, width/2 + 0.01);
        glVertex3f(length/2, -height/2 + 0.2, width/2 + 0.01);
        glVertex3f(length/2, -height/2 + 0.35, width/2 + 0.01);
        glVertex3f(-length/2, -height/2 + 0.35, width/2 + 0.01);
    glEnd();
    
    // Garis bawah kiri
    glBegin(GL_QUADS);
        glVertex3f(-length/2, -height/2 + 0.2, -width/2 - 0.01);
        glVertex3f(length/2, -height/2 + 0.2, -width/2 - 0.01);
        glVertex3f(length/2, -height/2 + 0.35, -width/2 - 0.01);
        glVertex3f(-length/2, -height/2 + 0.35, -width/2 - 0.01);
    glEnd();
    
    // LAMPU BUS
    // Lampu depan - putih kekuningan
    glColor3f(1.0, 1.0, 0.8);
    glBegin(GL_QUADS);
        glVertex3f(length/2 + 0.01, -height/2 + 0.6, width/3);
        glVertex3f(length/2 + 0.01, -height/2 + 0.6, width/6);
        glVertex3f(length/2 + 0.01, -height/2 + 0.9, width/6);
        glVertex3f(length/2 + 0.01, -height/2 + 0.9, width/3);
        
        glVertex3f(length/2 + 0.01, -height/2 + 0.6, -width/3);
        glVertex3f(length/2 + 0.01, -height/2 + 0.6, -width/6);
        glVertex3f(length/2 + 0.01, -height/2 + 0.9, -width/6);
        glVertex3f(length/2 + 0.01, -height/2 + 0.9, -width/3);
    glEnd();
    
    // Lampu belakang - merah seperti di 2D
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
        glVertex3f(-length/2 - 0.03, -height/2 + 0.38, width/3);
        glVertex3f(-length/2 - 0.01, -height/2 + 0.38, width/3);
        glVertex3f(-length/2 - 0.01, -height/2 + 0.55, width/3);
        glVertex3f(-length/2 - 0.03, -height/2 + 0.55, width/3);
        
        glVertex3f(-length/2 - 0.03, -height/2 + 0.38, -width/3);
        glVertex3f(-length/2 - 0.01, -height/2 + 0.38, -width/3);
        glVertex3f(-length/2 - 0.01, -height/2 + 0.55, -width/3);
        glVertex3f(-length/2 - 0.03, -height/2 + 0.55, -width/3);
    glEnd();
    
    // RODA BUS
    float wheelRadius = 0.4;
    float wheelWidth = 0.2;
    
    // Roda depan kanan
    drawWheel3D(length/3, -height/2 - 0.05, width/2 + wheelWidth/2, wheelRadius, wheelWidth);
    
    // Roda depan kiri
    drawWheel3D(length/3, -height/2 - 0.05, -width/2 - wheelWidth/2, wheelRadius, wheelWidth);
    
    // Roda belakang kanan
    drawWheel3D(-length/3, -height/2 - 0.05, width/2 + wheelWidth/2, wheelRadius, wheelWidth);
    
    // Roda belakang kiri
    drawWheel3D(-length/3, -height/2 - 0.05, -width/2 - wheelWidth/2, wheelRadius, wheelWidth);
}

void Reshape(int w1, int h1){
	// Fungsi reshape
	if(h1 == 0) h1 = 1;
	w = w1;
	h = h1;
	ratio = 1.0f * w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45,ratio,0.1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
	x, y, z,
	x + lx,y + ly,z + lz, 0.0f,1.0f,0.0f);
}

void orientMe(float ang){
	// Fungsi ini untuk memutar arah kamera (tengok kiri/kanan)
	lx = sin(ang);
	lz = -cos(ang);
	glLoadIdentity();
	gluLookAt(x, y, z,
	x + lx,y + ly,z + lz, 0.0f,1.0f,0.0f);
}

void moveMeFlat(int i){
	// Fungsi ini untuk maju mundur kamera
	x = x + i*(lx)*0.1;
	z = z + i*(lz)*0.1;
	glLoadIdentity();
	
	gluLookAt(x, y, z,
	x + lx,y + ly,z + lz, 0.0f,1.0f,0.0f);
}

void Grid() {
	// Fungsi untuk membuat grid di "lantai"
	double i;
	const float Z_MIN = -50, Z_MAX = 50;
	const float X_MIN = -50, X_MAX = 50;
	const float gap = 1.5;
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_LINES);
	for(i=Z_MIN;i<Z_MAX;i+=gap){
		glVertex3f(i, 0, Z_MIN);
		glVertex3f(i, 0, Z_MAX);
	}
	for(i=X_MIN;i<X_MAX;i+=gap){
		glVertex3f(X_MIN, 0, i);
		glVertex3f(X_MAX, 0, i);
	}
	glEnd();
}

void display() {
	// Kalau move dan angle tidak nol, gerakkan kamera...
	if (deltaMove)
		moveMeFlat(deltaMove);
	if (deltaAngle) {
		angle += deltaAngle;
		orientMe(angle);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Gambar grid
	Grid();
	
//	// Animasi bus (rotasi roda)
//	busAngle += 0.01;
//	if (busAngle > 1.0) busAngle = 0.0;
	
	// Gambar bus 3D
	glPushMatrix();
	glTranslatef(0, 0.9, 0); // Posisikan bus di atas grid (dinaikan dari 0.4 menjadi 0.9)
	drawBus3D();
	glPopMatrix();
	
	glutSwapBuffers();
	glFlush();
}

void pressKey(int key, int x, int y) {
	// Fungsi ini akan dijalankan saat tombol keyboard ditekan dan belum dilepas
	// Selama tombol ditekan, variabel angle dan move diubah => kamera bergerak
	switch (key) {
		case GLUT_KEY_LEFT : deltaAngle = -0.01f;break;
		case GLUT_KEY_RIGHT : deltaAngle = 0.01f;break;
		case GLUT_KEY_UP : deltaMove = 1;break;
		case GLUT_KEY_DOWN : deltaMove = -1;break;
	}
}

void releaseKey(int key, int x, int y) {
	// Fungsi ini akan dijalankan saat tekanan tombol keyboard dilepas
	// Saat tombol dilepas, variabel angle dan move diset nol => kamera berhenti
	switch (key) {
		case GLUT_KEY_LEFT :
			if (deltaAngle < 0.0f)
				deltaAngle = 0.0f;
			break;
		case GLUT_KEY_RIGHT : if (deltaAngle > 0.0f)
			deltaAngle = 0.0f;
			break;
		case GLUT_KEY_UP : if (deltaMove > 0)
			deltaMove = 0;
			break;
		case GLUT_KEY_DOWN : if (deltaMove < 0)
			deltaMove = 0;
			break;
	}
}

// Variable untuk pencahayaan
const GLfloat light_ambient[] = { 0.5f, 0.5f, 0.5f, 0.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 0.0f, 20.0f, 10.0f, 1.0f };
const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

void lighting(){
	// Fungsi mengaktifkan pencahayaan
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

void init(void){
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,480);
	glutCreateWindow("3D Bus with Lighting");
	glutIgnoreKeyRepeat(1); // Mengabaikan key repeat (saat tombol keyboard dipencet terus)
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);
	glutDisplayFunc(display);
	
	glutIdleFunc(display); // Fungsi display-nya dipanggil terus-menerus
	
	glutReshapeFunc(Reshape);
	lighting();
	init();
	glutMainLoop();
	return(0);
}
