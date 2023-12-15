#include <3d-engine/engine.h>
#define __USE_MISC 1
#include <math.h>
#include <xgfx/window.h>

#define EVENT_BUFFER_SIZE 100
XEvent eventBuffer[EVENT_BUFFER_SIZE];

vec3 vertices[10*10];
int indices[9*9*2*3];

int main() {
    float t = 0;
    float angleX = 0;
    float angleY = 0;
    float angleZ = 0;
    int upPressed = 0;
    int downPressed = 0;
    int leftPressed = 0;
    int rightPressed = 0;
    int homePressed = 0;
    int endPressed = 0;
    int wireframe = 0;
    vec3 lightPosition = {2, 2, -2};
    int lightIntensity = 2;
    initEngine(640, 480, "Grapher", lightPosition, lightIntensity);
    while(1) {
        int eventsRead = checkWindowEvents(eventBuffer, EVENT_BUFFER_SIZE);
        for (int i = 0; i < eventsRead; i++) {
            XEvent event = eventBuffer[i];
            if (event.type == ClosedWindow) {
                return 0;
            }
            if (event.type == KeyPress) {
                if (event.xkey.keycode == 111) {
                    upPressed = 1;
                }
                if (event.xkey.keycode == 116) {
                    downPressed = 1;
                }
                if (event.xkey.keycode == 113) {
                    leftPressed = 1;
                }
                if (event.xkey.keycode == 114) {
                    rightPressed = 1;
                }
                if (event.xkey.keycode == 110) {
                    homePressed = 1;
                }
                if (event.xkey.keycode == 115) {
                    endPressed = 1;
                }
                if (event.xkey.keycode == 9) {
                    if (wireframe) {
                        wireframe = 0;
                    }
                    else {
                        wireframe = 1;
                    }
                }
            }
            if (event.type == KeyRelease) {
                if (event.xkey.keycode == 111) {
                    upPressed = 0;
                }
                if (event.xkey.keycode == 116) {
                    downPressed = 0;
                }
                if (event.xkey.keycode == 113) {
                    leftPressed = 0;
                }
                if (event.xkey.keycode == 114) {
                    rightPressed = 0;
                }
                if (event.xkey.keycode == 110) {
                    homePressed = 0;
                }
                if (event.xkey.keycode == 115) {
                    endPressed = 0;
                }
            }
        }

        if (upPressed) {
            angleX += 0.0625;
        }
        if (downPressed) {
            angleX -= 0.0625;
        }
        if (leftPressed) {
            angleY += 0.0625;
        }
        if (rightPressed) {
            angleY -= 0.0625;
        }
        if (homePressed) {
            angleZ += 0.0625;
        }
        if (endPressed) {
            angleZ -= 0.0625;
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
        mat3 rotationMatrixA;
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
        t += 0.1;
        renderObject(vertices, 100, indices, 486, rotationMatrixA, wireframe);
        updateWindow3D();
    }
}
