#include "stdafx.h"
#include "GApp.h"
#include "GameScene.h"

using namespace Glory;

int main()
{
	GApp::Instance()->InitWindow(1366, 768, "Project2");
	GApp::Instance()->SetScene(new GameScene());
	GApp::Instance()->MainLoop();

	return 0;
}

//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow *window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//}