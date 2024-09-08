#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);}
	bool* getsKeys() { return keys; }
	GLfloat getXChange();
	GLfloat getYChange();
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }
	GLfloat getrotay() { return rotay; }
	GLfloat getrotax() { return rotax; }
	GLfloat getrotaz() { return rotaz; }
	GLfloat getarticulacion1() { return articulacion1; }
	GLfloat getarticulacion2() { return articulacion2; }
	GLfloat getarticulacion3() { return articulacion3; }
	GLfloat getarticulacion4() { return articulacion4; }
	GLfloat getarticulacion5() { return articulacion5; }
	GLfloat getarticulacion6() { return articulacion6; }
	GLfloat getllanta1() { return llanta1; }
	GLfloat getllanta2() { return llanta2; }
	GLfloat getllanta3() { return llanta3; }
	GLfloat getllanta4() { return llanta4; }
	GLfloat getpatasup1() { return ps1; }
	GLfloat getpatasup2() { return ps2; }
	GLfloat getpatainf1() { return pi1; }
	GLfloat getpatainf2() { return pi2; }
	GLfloat getpalma1() { return pl1; }
	GLfloat getpalma2() { return pl2; }
	GLfloat getpalma3() { return pl3; }
	GLfloat getpalma4() { return pl4; }
	GLfloat getoreja1() { return o1; }
	GLfloat getoreja2() { return o2; }

	~Window();
private: 
	GLFWwindow *mainWindow;
	GLint width, height;
	GLfloat rotax,rotay,rotaz, articulacion1, articulacion2, articulacion3, articulacion4, articulacion5, articulacion6, llanta1,
		llanta2, llanta3, llanta4, ps1, ps2, pi1, pi2, pl1, pl2, pl3, pl4, o1, o2;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	bool mouseFirstMoved;
	void createCallbacks();
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);
};

