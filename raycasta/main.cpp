#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <cmath>

#define SCREENW 640 //horizontal resolution
#define SCREENH 480 //vertical resolution
#define PI 3.14159265
#define PIRAD 0.01745329252

using namespace std;

void setupTexture();
void updateTexture();

unsigned __int8 screenData[SCREENH][SCREENW][3];
unsigned __int8 test[15][15];
float xp = 10.0f;
float yp = 10.0f;
float minang = 15.0f;
float fov = 75.0f;
bool a,d,w,s,q,e;

unsigned int cpal[8] = {
0xFF00FF, 0x707075, 0x959295, 0x663300, 0x593000, 0x660000, 0x550000, 0xAAAAAA
};

void drawline(float angle, int iteration, float x, float y);

/* GLUT callback Handlers */

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

void setupTexture()
{
	// Create a texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, SCREENW, SCREENH, 0, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)screenData);

	// Set up the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	// Enable textures
	glEnable(GL_TEXTURE_2D);
}

void updateTexture()
{
	// Update Texture
	glTexSubImage2D(GL_TEXTURE_2D, 0 ,0, 0, SCREENW, SCREENH, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)screenData);

	glBegin( GL_QUADS );
		glTexCoord2d(0.0, 0.0);		glVertex2d(0.0,			    0.0);
		glTexCoord2d(1.0, 0.0); 	glVertex2d((SCREENW * 1),  0.0);
		glTexCoord2d(1.0, 1.0); 	glVertex2d((SCREENW * 1),  (SCREENH * 1));
		glTexCoord2d(0.0, 1.0); 	glVertex2d(0.0,			    (SCREENH * 1));
	glEnd();
}

float findnewmx(float angle, float x){
    return (x - 0.1*cos(angle * PIRAD));
}
float findnewmy(float angle, float y){
    return (y - 0.1*sin(angle * PIRAD));
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    if(a){
        xp = findnewmx(((fov/2)+minang)+90, xp);
        yp = findnewmy(((fov/2)+minang)+90, yp);}
    if(d){
        xp = findnewmx(((fov/2)+minang)-90, xp);
        yp = findnewmy(((fov/2)+minang)-90, yp);}
    if(w){
        xp = findnewmx(((fov/2)+minang), xp);
        yp = findnewmy(((fov/2)+minang), yp);}
    if(s){
        xp = findnewmx(((fov/2)+minang)+180, xp);
        yp = findnewmy(((fov/2)+minang)+180, yp);}
    if(q){
        minang+=3.0f;}
    if(e){
        minang-=3.0f;}
    // Clear screen
	for(int y = 0; y < SCREENH; y++)
		for(int x = 0; x < SCREENW; x++)
			screenData[y][x][0] = screenData[y][x][1] = screenData[y][x][2] = 50;
    //bottom half of screen blank tex (floor)
    for(int x = 0; x < SCREENW; x++){
        for(int y = SCREENH/2; y < SCREENH; y++){
            screenData[y][x][0] = 20;
            screenData[y][x][1] = 20;
            screenData[y][x][2] = 20;
        }
    }
    for(int i = 0; i < SCREENW; i++){
        drawline(i*(fov/SCREENW) + minang, i, xp, yp);
    }
    updateTexture();
    glutSwapBuffers();
}

float findnewx(float stepsize, float angle, float x){
    return (x - stepsize*cos(angle * PIRAD));
}
float findnewy(float stepsize, float angle, float y){
    return (y - stepsize*sin(angle * PIRAD));
}

void keyboardDown(unsigned char key, int x, int y){
    if(key == 27){   // esc
		exit(0);
    }
    if(key == 'a'){
        a = true;
    }
    if(key == 'd'){
        d = true;
    }
    if(key == 'w'){
        w = true;
    }
    if(key == 's'){
        s = true;
    }
    if(key == 'q'){
        q = true;
    }
    if(key == 'e'){
        e = true;
    }
    return;
}

void keyboardUp(unsigned char key, int x, int y){
    if(key == 'a'){
        a = false;
    }
    if(key == 'd'){
        d = false;
    }
    if(key == 'w'){
        w = false;
    }
    if(key == 's'){
        s = false;
    }
    if(key == 'q'){
        q = false;
    }
    if(key == 'e'){
        e = false;
    }
    return;
}

void drawline(float angle, int iteration, float x, float y){
    float steps = 0.0f;
    int stepcounter = 1;
    int col = 0;
    float xrp = xp;
    float yrp = yp;
    int roundedxrp = int(round(xrp));
    int roundedyrp = int(round(yrp));
    while(test[roundedyrp][roundedxrp] == 0){
        steps += 0.01f * pow(1.0033, stepcounter);
        xrp = findnewx(0.01f * pow(1.0033, stepcounter), angle, xrp);
        yrp = findnewy(0.01f * pow(1.0033, stepcounter), angle, yrp);
        roundedxrp = int(round(xrp));
        roundedyrp = int(round(yrp));
        if(test[roundedyrp][roundedxrp] != 0){
            col = test[roundedyrp][roundedxrp];
        }
        if(steps >= 20){
            col = 0;
            break;
        }
        stepcounter++;
    }
    int wallheight = fmin(SCREENH-1, (SCREENH-steps) * ((((sin(PIRAD*0.5*(180-fov)) ) / sin(PIRAD*(180 - ((minang+fov)-angle) - (0.5*(180-fov)) )) ) )/steps));
    float colchangefactor = ((20.0 - steps)/20.0);
    for(int y = 0; y < wallheight; y++){
        screenData[y + ((SCREENH/2) - int(round(wallheight/2)))][SCREENW - iteration-1][0] = int(round(((cpal[col] & 0xFF0000) >> 16) * colchangefactor));
        screenData[y + ((SCREENH/2) - int(round(wallheight/2)))][SCREENW - iteration-1][1] = int(round(((cpal[col] & 0x00FF00) >> 8) * colchangefactor));
        screenData[y + ((SCREENH/2) - int(round(wallheight/2)))][SCREENW - iteration-1][2] = int(round(((cpal[col] & 0x0000FF)) * colchangefactor));
    }
}


/* Program entry point */

int main(int argc, char *argv[])
{
    cout << hex << ((cpal[1] & 0x00FF00) >> 8) << endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(SCREENW * 1,SCREENH * 1);
    glutInitWindowPosition(640,300);
    glutCreateWindow("Raycasting Game");
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutKeyboardFunc(keyboardDown);
	glutKeyboardUpFunc(keyboardUp);
    //glutOverlayDisplayFunc(display);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( 0.0, 640.0, 480.0, 0.0 );

    setupTexture();

    for(int i = 0; i < 15; i++){
        if(i%2 < 1){
            test[i][14] = 3;
            test[i][0] = 3;
            test[14][i] = 3;
            test[0][i] = 3;
        }
        else{
            test[i][14] = 4;
            test[i][0] = 4;
            test[14][i] = 4;
            test[0][i] = 4;
        }
    }
    for(int i = 1; i < 6; i++){
        if(i % 2 == 0){
            test[6][i] = 5;
        }
        else{
            test[6][i] = 6;
        }
    }
    test[0][0] = 4;
    test[7][9] = 7;

    glutMainLoop();

    Sleep(300000);

    return EXIT_SUCCESS;
}
