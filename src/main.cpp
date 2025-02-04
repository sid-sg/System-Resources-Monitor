#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>

#include <chrono>
#include <deque>
#include <iomanip>
#include <iostream>
#include <thread>
#include <vector>

#include "cpu_stats.hpp"
#include "graphics.hpp"

const int WIDTH = 800;
const int HEIGHT = 600;
const int MAX_POINTS = 100;

std::deque<float> cpuValues;

GLuint vbo;

void update_graph(float newValue) {
    cpuValues.push_back(newValue);
    if (cpuValues.size() > MAX_POINTS) cpuValues.pop_front();

    std::vector<float> vertices;
    float xStep = 2.0f / MAX_POINTS;

    for (size_t i = 0; i < cpuValues.size(); i++) {
        float x = -1.0f + i * xStep;
        float y = (cpuValues[i] / 100.0f) * 2.0f - 1.0f;
        vertices.push_back(x);
        vertices.push_back(y);
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);
}

int main() {
    // init GLFW
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "CPU Usage Monitor", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // init GLEW 
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // init GLUT 
    int argc = 1;
    char* argv[1] = {(char*)"Something"};
    glutInit(&argc, argv);

    glGenBuffers(1, &vbo);
    glEnableClientState(GL_VERTEX_ARRAY);

    CPUData prev = read_cpu_data();
    while (!glfwWindowShouldClose(window)) {
        
        CPUData current = read_cpu_data();
        double cpu_usage = calculate_cpu_use(prev, current);
        prev = current;

        update_graph(static_cast<float>(cpu_usage));

        glClear(GL_COLOR_BUFFER_BIT);

        // draw graph
        glColor3f(0.0f, 1.0f, 0.0f);  // green
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexPointer(2, GL_FLOAT, 0, 0);
        glDrawArrays(GL_LINE_STRIP, 0, cpuValues.size());

        drawCPUText(cpu_usage);

        glfwSwapBuffers(window);
        glfwPollEvents();

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    glDeleteBuffers(1, &vbo);
    glfwTerminate();
    return 0;
}
