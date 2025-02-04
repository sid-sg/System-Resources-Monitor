#include <GL/glut.h>

#include <sstream>

void renderText(const char* text, float x, float y) {
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void drawCPUText(float cpu_usage) {
    glColor3f(1.0f, 1.0f, 1.0f);
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "CPU Usage: %.2f%%", cpu_usage);
    renderText(buffer, -0.9f, 0.9f);
}
