#include <GL/glut.h>
#include <math.h>

#define PI 3.1415926535898

float busX = 0.0;

void drawCircle(float cx, float cy, float radius, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < segments; i++) {
        float angle = 2.0f * PI * i / segments;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void drawWheel(float cx, float cy, float radius) {
    glPushMatrix();
    	glTranslatef(cx, cy, 0);
    	glRotatef(busX * -100, 0.0, 0.0, 1.0);

	    // Roda luar (hitam)
	    glColor3f(0.0, 0.0, 0.0);
	    drawCircle(0, 0, radius, 30);
	
	    // Velg (abu-abu)
	    glColor3f(0.7, 0.7, 0.7);
	    drawCircle(0, 0, radius * 0.5, 30);
	
	    // Garis-garis velg
	    glColor3f(1.0, 1.0, 1.0);
	    glBegin(GL_LINES);
		    for (int i = 0; i < 6; i++) {
		        float angle = i * PI / 3;
		        glVertex2f(0, 0);
		        glVertex2f(radius * 0.5 * cos(angle), radius * 0.5 * sin(angle));
		    }
	    glEnd();

    glPopMatrix();
}


void drawBus() {
    // BADAN BUS
    //Bagian bawah
    glColor3f(1.0, 0.8, 0.0);
    glBegin(GL_QUADS);
        glVertex2f(-0.8, -0.1);
        glVertex2f(0.6, -0.1);
        glVertex2f(0.6, 0.3);
        glVertex2f(-0.8, 0.3);
    glEnd();
    
    //bagian atas
	glColor3f(1.0, 0.8, 0.0);
    glBegin(GL_QUADS);
        glVertex2f(-0.8, 0.2);
        glVertex2f(0.35, 0.2);
        glVertex2f(0.35, 0.6);
        glVertex2f(-0.8, 0.6);
    glEnd();
    
    //Kabin bus
    glColor3f(1.0, 0.6, 0.0);
    glBegin(GL_QUADS);
        glVertex2f(-0.8, 0.6);
        glVertex2f(0.35, 0.6);
        glVertex2f(0.3, 0.65);
        glVertex2f(-0.75, 0.65);
    glEnd();
    
    //Garis tengah
    glColor3f(1.0, 0.6, 0.0);
    glBegin(GL_QUADS);
        glVertex2f(-0.8, 0.25);
        glVertex2f(-0.1, 0.25);
        glVertex2f(-0.1, 0.2);
        glVertex2f(-0.8, 0.2);
    glEnd();
    
    //bagian bawah bus
    glColor3f(0.8, 0.5, 0.0);
    glBegin(GL_QUADS);
        glVertex2f(-0.8, 0.15);
        glVertex2f(0.6, 0.15);
        glVertex2f(0.6, -0.1);
        glVertex2f(-0.8, -0.1);
    glEnd();
    
    //Garis bawah jendela
	glColor3f(1.0, 0.6, 0.0);
    glBegin(GL_QUADS);
        glVertex2f(-0.8, 0.33);
        glVertex2f(0.35, 0.33);
        glVertex2f(0.35, 0.31);
        glVertex2f(-0.8, 0.31);
    glEnd();
    
    
    // RODA BUS
    glPushMatrix();
    	glTranslatef(-0.55, -0.10, 0);
    	drawWheel(0.0, 0.0, 0.15);
    glPopMatrix();
    
    glPushMatrix();
    	glTranslatef(0.4, -0.10, 0);
    	drawWheel(0.0, 0.0, 0.15);
    glPopMatrix();
    
	
	// PINTU BUS
	
	//pintu bagian luar (warna gelap)
	glColor3f(1.0, 0.6, 0.0);
	glBegin(GL_QUADS);
	    glVertex2f(-0.15, -0.1);
	    glVertex2f(0.2, -0.1);
	    glVertex2f(0.2, 0.5);
	    glVertex2f(-0.15, 0.5);
	glEnd();
	
	//pintu bagian dalam (warna terang)
	glColor3f(1.0, 0.8, 0.0);
	glBegin(GL_QUADS);
	    glVertex2f(-0.14, -0.1);
	    glVertex2f(0.19, -0.1);
	    glVertex2f(0.19, 0.49);
	    glVertex2f(-0.14, 0.49);
	glEnd();
	
	//Garis tengah pintu
	glColor3f(1.0, 0.6, 0.0);
	glBegin(GL_QUADS);
	    glVertex2f(0.021, -0.1);
	    glVertex2f(0.027, -0.1);
	    glVertex2f(0.027, 0.49);
	    glVertex2f(0.021, 0.49);
	glEnd();
	
	//Jendela di Pintu
    glColor3f(0.7, 0.9, 1.0);
    glBegin(GL_QUADS);
	    glVertex2f(-0.12, 0.25);
	    glVertex2f(0.01, 0.25);
	    glVertex2f(0.01, 0.47);
	    glVertex2f(-0.12, 0.47);
	glEnd();
	
	glColor3f(0.7, 0.9, 1.0);
    glBegin(GL_QUADS);
	    glVertex2f(0.04, 0.25);
	    glVertex2f(0.17, 0.25);
	    glVertex2f(0.17, 0.47);
	    glVertex2f(0.04, 0.47); 
	glEnd();
	
	//Jendela depan
	glColor3f(0.7, 0.9, 1.0);
	glBegin(GL_QUADS);
	    glVertex2f(0.25, 0.55);
	    glVertex2f(0.35, 0.55);
	    glVertex2f(0.35, 0.35);
	    glVertex2f(0.25, 0.35);
	glEnd();
	
	// JENDELA BUS
    for (int i = -5.0; i < -1; i++) {
        glColor3f(0.7, 0.9, 1.0);
        glBegin(GL_QUADS);
            glVertex2f(i * 0.15, 0.55);
            glVertex2f(i * 0.15 + 0.12, 0.55);
            glVertex2f(i * 0.15 + 0.12, 0.35);
            glVertex2f(i * 0.15, 0.35);
        glEnd();
    }
	
	//Lampu bus
	glColor3f(0.7, 0.9, 1.0);
    glBegin(GL_QUADS);
        glVertex2f(0.5, 0.17);
        glVertex2f(0.6, 0.17);
        glVertex2f(0.6, 0.27);
        glVertex2f(0.5, 0.27);
    glEnd();
    
    //Garis depan
	glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_QUADS);
        glVertex2f(0.4, 0.06);
        glVertex2f(0.6, 0.06);
        glVertex2f(0.6, 0.12);
        glVertex2f(0.4, 0.12);
    glEnd();
    
    //Garis belakang
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_QUADS);
        glVertex2f(-0.8, 0.06);
        glVertex2f(-0.7, 0.06);
        glVertex2f(-0.7, 0.12);
        glVertex2f(-0.8, 0.12);
    glEnd();
    
    //Lampu belakang
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
        glVertex2f(-0.83, 0.06);
        glVertex2f(-0.8, 0.06);
        glVertex2f(-0.8, 0.15);
        glVertex2f(-0.83, 0.15);
    glEnd();
    
	
}

void RenderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // LANGIT
    glColor3f(0.5, 0.8, 1.0);
    glBegin(GL_QUADS);
        glVertex2f(-1.0, -1.0);
        glVertex2f(1.0, -1.0);
        glVertex2f(1.0, 1.0);
        glVertex2f(-1.0, 1.0);
    glEnd();
    
    //MATAHARI
	glPushMatrix();
	    glColor3f(1.0, 1.0, 0.0);
	    drawCircle(0.6, 0.7, 0.15, 30);
	glPopMatrix();

    // TANAH
    glColor3f(0.3, 0.7, 0.3);
    glBegin(GL_QUADS);
        glVertex2f(-1.0, -0.5);
        glVertex2f(1.0, -0.5);
        glVertex2f(1.0, -1.0);
        glVertex2f(-1.0, -1.0);
    glEnd();

    // BUS
    glPushMatrix();
	    glPushMatrix();
	        glTranslatef(busX, -0.3, 0.0);
	        drawBus();
	    glPopMatrix();
	glPopMatrix();

    glutSwapBuffers();
    
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 640);
    glutCreateWindow("Bus Sekolah");

    glClearColor(0.5, 0.8, 1.0, 1.0);
    gluOrtho2D(-1, 1, -1, 1);

    glutDisplayFunc(RenderScene);

    glutMainLoop();
    return 0;
}

