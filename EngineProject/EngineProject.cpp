#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// Default Screen Setup
const unsigned short SCR_WIDTH = 800;
const unsigned short SCR_HEIGHT = 800;
const char* SCREEN_NAME = "LearnOpenGL";

int main()
{
	// Obvious Initialization stuff
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Window Creation with settings params
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, SCREEN_NAME, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Gets current active window as an out param
	glfwMakeContextCurrent(window);

	// Assigns a callback to the window when the scale of it is changed
	// When the window size is changed, the screen scale changes accordingly
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// tho it might not be that relevant, just an INIT To the GLAD tool we use
	// GLAD is a set of delegates
	// glwGetProcAdress - gets adress of the process (PID) of the window process
	// OpenGL source code is not accessable except for the runtime, which this call gains
	// Binds all delegates in GLAD to the code
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Shader currentShader("EngineProject/VertexShader.vert", "EngineProject/FragmentShader.frag");

	// This array contains positions of vertices (will contain also colors eventually)
	float vertices[] = {
		//	[     positions     ] [      colors      ]
			 0.5f, -0.5f,  0.0f,    1.0f, 1.0f, 0.0f, // top right
			-0.5f, -0.5f,  0.0f,    0.0f, 1.0f, 1.0f, // bottom right
			 0.0f,  0.5f,  0.0f,    1.0f, 0.0f, 1.0f  // bottom left
			//-0.5f,  0.5f,  0.0f   // top left 
	};

	// Instructions to what numbers are used for each vertice from the vertices array
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 2,  // first Triangle
		//1, 2, 3  // second Triangle
	};

	// Vertex Array Object
	unsigned int VAO;

	// Vertex Buffer Objects
	unsigned int VBO;

	// Element Buffer Objects
	unsigned int EBO;

	// Generates Vertex Array with ID of VAO
	// 1 - How many arrays
	// &VAO - the ID of the generated array
	glGenVertexArrays(1, &VAO);

	// Generates Buffer object with ID of VBO
	// 1 - How many arrays
	// &VBO - the ID of the generated buffer
	glGenBuffers(1, &VBO);

	// Generates Buffer object with ID of EBO
	// 1 - How many arrays
	// &EBO - the ID of the generated buffer
	glGenBuffers(1, &EBO);

	// Binds VAO, the following Attribute calls will be stored in this currently bound VAO
	glBindVertexArray(VAO);

	// Binds the buffer to the ID
	// GL_ARRAY_BUFFER - enum type of the target buffer object
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Adds the data of the type to the buffer
	// GL_ARRAY_BUFFER - enum type of the target buffer object
	// Size of the array
	// vertices positions to the buffer
	// Draw pattern
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Binds the buffer to the ID
	// VBO - ID of the buffer to bind this type	// GL_ARRAY_BUFFER - enum type of the target buffer object
	// VBO - ID of the buffer to bind this type
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// Adds the data of the type to the buffer
	// GL_ARRAY_BUFFER - enum type of the target buffer object
	// Size of the array
	// vertices indexes to the buffer
	// Draw pattern
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Tells the OpenGL how it should interpret the POSITION buffers when drawing
	// Layout number (using kinda C# attributes)
	// Number of components per vertex attribute, can be 1,2,3,4
	// Data Type
	// bool - Clamp from -1 to 1 (0 to 1 for unsigned)?
	// Stride - byte offset between each vertexes, basically how much memory size will 3 vertex points take?
	// pointer - offset of the first component, where it should start
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	// Enables the vertex attribute to be enabled
	// Index of the vertex Attribute
	glEnableVertexAttribArray(0);

	// Tells the OpenGL how it should interpret the COLOR buffers when drawing
	// Layout number (using kinda C# attributes)
	// Number of components per vertex attribute, can be 1,2,3,4
	// Data Type
	// bool - Clamp from -1 to 1 (0 to 1 for unsigned)?
	// Stride - byte offset between each vertexes, basically how much memory size will 3 vertex points take?
	// pointer - offset of the first component, where it should start in memory size
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	// Enables the vertex attribute to be enabled
	// Index of the vertex Attribute
	glEnableVertexAttribArray(1);

	// Binds the buffer to the ID we have just created
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Binds the Vertex Array we have just created
	glBindVertexArray(0);


	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		currentShader.Use();

		// seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glBindVertexArray(VAO);

		// Enum - What object types should OpenGL Draw
		// int - How many vertices should OpenGL draw
		// type of values in the indices
		// offset of where it should start in the indices buffer
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// de-allocate all resources once they've outlived their purpose:
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
	//glDeleteProgram(shaderProgram);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// Rescale callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}