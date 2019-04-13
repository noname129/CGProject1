#include "stdafx.h"
#include "GApp.h"
#include "GameScene.h"

using namespace Glory;

int main()
{
	GApp::Instance().InitWindow(1366, 768, "Project1");
	GApp::Instance().SetScene(new GameScene());
	GApp::Instance().MainLoop();

	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


 //02_HelloTriangle
 //- draw a (orange) 2D triangle: using 1 VBO and 1 VAO
 //- ESC to quit

//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//#include "shader.h"
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow *window);
//
//// settings
//unsigned int SCR_WIDTH = 800;
//unsigned int SCR_HEIGHT = 600;
//
//int main()
//{
//	// glfw: initialize and configure
//	// ------------------------------
//	if (!glfwInit())
//	{
//		printf("GLFW initialisation failed!");
//		glfwTerminate();
//		return 1;
//	}
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//
//	// glfw window creation
//	// --------------------
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "HelloTriangle", NULL, NULL);
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//
//	// Allow modern extension features
//	glewExperimental = GL_TRUE;
//
//	if (glewInit() != GLEW_OK)
//	{
//		printf("GLEW initialisation failed!");
//		glfwDestroyWindow(window);
//		glfwTerminate();
//		return 1;
//	}
//
//	//// build and compile our shader program
//	//// ------------------------------------
//
//
//	// set up vertex data (and buffer(s)) and configure vertex attributes
//	// ------------------------------------------------------------------
//	float vertices[] = {
//		-0.5f, -0.5f, 0.0f, // left  
//		0.5f, -0.5f, 0.0f, // right 
//		0.0f,  0.5f, 0.0f  // top   
//	};
//
//	float colors[] = {
//		1.0f, 0.0f, 0.0f, 1.0f, // left  
//		1.0f, 0.0f, 0.0f, 1.0f,// right 
//		1.0f, 0.0f, 0.0f, 1.0f,// top   
//	};
//
//	unsigned int VBO, VAO, VBO2;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &VBO2);
//	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(2);
//
//	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
//	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
//	glBindVertexArray(0);
//
//
//	Shader shader("global.vs", "global.fs");
//
//	// uncomment this call to draw in wireframe polygons.
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//	// render loop
//	// -----------
//	while (!glfwWindowShouldClose(window))
//	{
//
//		// render
//		// ------
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		// draw our first triangle
//		shader.use();
//		shader.setMat4("projection", glm::mat4(1.0f));
//		shader.setMat4("view", glm::mat4(0.5f));
//		shader.setMat4("model", glm::mat4(1.0f));
//		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//		// glBindVertexArray(0); // no need to unbind it every time 
//
//		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//		// -------------------------------------------------------------------------------
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	// optional: de-allocate all resources once they've outlived their purpose:
//	// ------------------------------------------------------------------------
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//
//	// glfw: terminate, clearing all previously allocated GLFW resources.
//	// ------------------------------------------------------------------
//	glfwTerminate();
//	return 0;
//}


//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	// make sure the viewport matches the new window dimensions; note that width and 
//	// height will be significantly larger than specified on retina displays.
//	glViewport(0, 0, width, height);
//	SCR_WIDTH = width;
//	SCR_HEIGHT = height;
//}
