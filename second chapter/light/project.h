#ifndef	PROJECT_H
#define	PROJECT_H

	#include	<iostream>
	#include	<cmath>

	#define		GLEW_STATIC		//GLEW
	#include	<GL/glew.h>
	#include	<GLFW/glfw3.h>	// GLFW
	#include	<SOIL/SOIL.h>	//For textures
	#include	<glm/glm.hpp>	// GLM Mathematics
	#include 	<glm/gtc/matrix_transform.hpp>
	#include	<glm/gtc/type_ptr.hpp>
	#include	"Shader.h"		//Class shader
	#include	"Camera.h"		//Class Camera

	void 			key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	void 			mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void 			scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void 			do_movement();
	unsigned int	loadCubemap(std::vector <std::string> cube);

	const GLuint	WIDTH = 900, HEIGHT = 800;//Camera
	Camera			camera(glm::vec3(0.0f, 0.0f, 3.0f));
	GLfloat			lastX  =  WIDTH  / 2.0;
	GLfloat			lastY  =  HEIGHT / 2.0;
	bool			keys[1024];
	glm::vec3		lightPos(1.2f, 1.0f, 2.0f);// Light attributes
	GLfloat			deltaTime = 0.0f;	// Time between current frame and last frame
	GLfloat			lastFrame = 0.0f;  	// Time of last frame

#endif