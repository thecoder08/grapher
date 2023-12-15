#include <3d-engine/engine-wl.h>
#define __USE_MISC 1
#include <math.h>

vec3 vertices[10*10];
int indices[9*9*2*3];

mat3 rotationMatrixA;
int upPressed = 0;
int downPressed = 0;
int leftPressed = 0;
int rightPressed = 0;
int homePressed = 0;
int endPressed = 0;
int wireframe = 0;

void key_change(unsigned int key, unsigned int state) {
    if (key == 103) {
        upPressed = state;
    }
    if (key == 108) {
        downPressed = state;
    }
    if (key == 105) {
        leftPressed = state;
    }
    if (key == 106) {
        rightPressed = state;
    }
    if (key == 102) {
        homePressed = state;
    }
    if (key == 107) {
        endPressed = state;
    }
    if (key == 1 && state == 1) {
        if (wireframe) {
            wireframe = 0;
        }
        else {
            wireframe = 1;
        }
    }
}

void draw() {
    renderObject(vertices, 100, indices, 486, rotationMatrixA, wireframe);
}

int main() {
    float t = 0;
    float angleX = 0;
    float angleY = 0;
    float angleZ = 0;
    vec3 lightPosition = {2, 2, -2};
    int lightIntensity = 2;
    initEngine(640, 480, "Grapher", lightPosition, lightIntensity, draw, key_change);
    while(dispatch() != -1) {
        if (upPressed) {
            angleX += 0.04;
        }
        if (downPressed) {
            angleX -= 0.04;
        }
        if (leftPressed) {
            angleY += 0.04;
        }
        if (rightPressed) {
            angleY -= 0.04;
        }
        if (homePressed) {
            angleZ += 0.04;
        }
        if (endPressed) {
            angleZ -= 0.04;
        }
        if (angleX >= M_PI * 2) {
                angleX -= M_PI * 2;
        }
        if (angleY >= M_PI * 2) {
                angleX -= M_PI * 2;
        }
        if (angleZ >= M_PI * 2) {
                angleX -= M_PI * 2;
        }
        rotationMatrixXYZ(angleX, angleY, angleZ, rotationMatrixA);
        for (int x = 0; x < 10; x++) {
            for (int z = 0; z < 10; z++) {
                int position = x * 10 + z;
                float xF = (float)(x-5)/2.0;
                float zF = (float)(z-5)/2.0;
                vertices[position][0] = xF;
                vertices[position][1] = sin(xF*xF + zF*zF + t); // this is our equation
                vertices[position][2] = zF;
                if ((x < 9) && (z < 9)) {
                    int index_pos = x * 9 + z;
                    indices[index_pos * 6] = position;
                    indices[index_pos * 6 + 1] = position + 1;
                    indices[index_pos * 6 + 2] = position + 10;
                    indices[index_pos * 6 + 3] = position + 11;
                    indices[index_pos * 6 + 4] = position + 1;
                    indices[index_pos * 6 + 5] = position + 10;
                }
            }
        }
        t += 0.05;
    }
}
