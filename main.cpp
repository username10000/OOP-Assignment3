// Local Headers
#include "glitter.hpp"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>

int main(int argc, char * argv[]) {

    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    auto mWindow = glfwCreateWindow(mWidth, mHeight, "OpenGL", nullptr, nullptr); // Add glfwGetPrimaryMonitor() to the 4th parameter for fullscreen

    // Check for Valid Context
    if (mWindow == nullptr) {
        fprintf(stderr, "Failed to Create OpenGL Context");
        return EXIT_FAILURE;
    }

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(mWindow);
    gladLoadGL();
	fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

    // Rendering Loop
    while (glfwWindowShouldClose(mWindow) == false) {
		// Close if the ESC key is pressed
        if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(mWindow, true);

        // Background Fill Color
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Flip Buffers and Draw
        glfwSwapBuffers(mWindow);
        glfwPollEvents();

		// Triangle Test
		float vertices[] = {
			 0.0f,  0.5f,
			 0.5f, -0.5f,
			-0.5f, -0.5f
		};

		// Create a Vertex Buffer Object(VBO)
		GLuint vbo;
		glGenBuffers(1, &vbo);

		// Make the data active
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		// Copy the data
		/*
		GL_STATIC_DRAW - The vertex data will be uploaded once and drawn many times (e.g. the world).
		GL_DYNAMIC_DRAW - The vertex data will be changed from time to time, but drawn many times more than that.
		GL_STREAM_DRAW - The vertex data will change almost every time it's drawn (e.g. user interface).
		*/
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// Vertex Shader
    }

	glfwTerminate();
    return EXIT_SUCCESS;
}
