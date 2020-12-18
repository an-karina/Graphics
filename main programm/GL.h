#ifndef		GL_H

# define	GL_H

//Libraries
# include <iostream>
# include <cmath>

# define GLEW_STATIC					//GLEW

# include <GL/glew.h>					//GLEW
# include <GLFW/glfw3.h>				//GLFW
# include <SOIL/SOIL.h>					// Textures
# include <glm/glm.hpp>					//Matrix, vectors and ect.
# include <glm/gtc/matrix_transform.hpp>//Matrix, vectors and ect.
# include <glm/gtc/type_ptr.hpp>		//Matrix, vectors and e t.

//Functions
void			key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void			do_movement();
void			mouse_callback(GLFWwindow *window, double xpos, double ypos);
void			scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

//Global values
const GLuint	WIDTH = 800;
const GLuint	HEIGHT = 600;

glm::vec3		cameraPos = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3		cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3		cameraUp = glm::vec3(0.0f, 1.0f,  0.0f);
bool 			keys[1024];

GLfloat 		deltaTime = 0.0f;		// time between last end current frame
GLfloat 		lastFrame = 0.0f;		//time for current frame

GLfloat 		yaw   = glm::radians(-90.0f);
GLfloat 		pitch = glm::radians(0.0f);
GLfloat 		lastX = 400;
GLfloat 		lastY = 300;
bool 			firstMouse = true;
GLfloat			fov =  glm::radians(45.0f);

#endif
