# include "GL.h"
# include "Shader.h"
int		main(void)
{
	glfwInit();																	//This function initializes the GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);								//sets hints for the next call
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glewExperimental = GL_TRUE;
	glewInit();	

	GLFWwindow		*window;
	GLuint 			VBO;
	GLuint			VAO;
	GLuint			texture1;
	GLuint			texture2;
	int				width;
	int				height;
	unsigned char	*image;
	glm::mat4		view;
	GLfloat			radius;
	GLfloat			camX;
	GLfloat			camZ;
	glm::mat4		projection;
	GLint			modelLoc;
	GLint			viewLoc;
	GLint			projLoc;
	GLfloat			vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};
    glm::vec3		cubePositions[] = {
		glm::vec3( 0.0f,  0.0f,  0.0f),
		glm::vec3( 2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3( 2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3( 1.3f, -2.0f, -2.5f),
		glm::vec3( 1.5f,  2.0f, -2.5f),
		glm::vec3( 1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);	//Creats window and its associated context
	glfwMakeContextCurrent(window);												//context
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glViewport(0, 0, WIDTH, HEIGHT);											//(0,0) bottom left corner and width, height
	glfwSetKeyCallback(window, key_callback);
	glEnable(GL_DEPTH_TEST);													//for 3D elements
	Shader ourShader("shader.vs", "shader.frag");								//using class Shader
	// glGenVertexArrays(1, &VAO);
	// glGenBuffers(1, &VBO);
	// glBindVertexArray(VAO);
	// glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	// glEnableVertexAttribArray(0);
	// glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	// glEnableVertexAttribArray(2);
	// glBindVertexArray(0);
	// glGenTextures(1, &texture1);
	// glBindTexture(GL_TEXTURE_2D, texture1);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// image = SOIL_load_image("container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	// glGenerateMipmap(GL_TEXTURE_2D);
	// SOIL_free_image_data(image);
	// glBindTexture(GL_TEXTURE_2D, 0);
	// glGenTextures(1, &texture2);
    // glBindTexture(GL_TEXTURE_2D, texture2);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// image = SOIL_load_image("awesomeface.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	// glGenerateMipmap(GL_TEXTURE_2D);
	// SOIL_free_image_data(image);
	// glBindTexture(GL_TEXTURE_2D, 0);
	while (!glfwWindowShouldClose(window))
	{
	// 	GLfloat currentFrame = glfwGetTime();
	// 	deltaTime = currentFrame - lastFrame;
	// 	lastFrame = currentFrame;
	 	glfwPollEvents();
	// 	do_movement();
	 	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 	glActiveTexture(GL_TEXTURE0);
	// 	glBindTexture(GL_TEXTURE_2D, texture1);
	// 	glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);
	// 	glActiveTexture(GL_TEXTURE1);
	// 	glBindTexture(GL_TEXTURE_2D, texture2);
	// 	glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture2"), 1);
	// 	ourShader.Use();
	// 	radius = 10.0f;
	// 	camX = sin(glfwGetTime()) * radius;
	// 	camZ = cos(glfwGetTime()) * radius;
	// 	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	// 	projection = glm::perspective(fov, (GLfloat)WIDTH/(GLfloat)HEIGHT, 0.1f, 100.0f);
	// 	modelLoc = glGetUniformLocation(ourShader.Program, "model");
	// 	viewLoc = glGetUniformLocation(ourShader.Program, "view");
	// 	projLoc = glGetUniformLocation(ourShader.Program, "projection");
	// 	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	// 	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	// 	glBindVertexArray(VAO);
	// 	for (GLuint i = 0; i < 10; i++)
	// 	{
	// 		glm::mat4 model = glm::mat4(1.0f);
	// 		model = glm::translate(model, cubePositions[i]);
	// 		GLfloat angle =glm::radians(20.0f * i);
	// 		model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
	// 		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	// 		glDrawArrays(GL_TRIANGLES, 0, 36);
	// 	}

	// 	glBindVertexArray(0);
	 	glfwSwapBuffers(window);
	}

	// glDeleteVertexArrays(1, &VAO);
	// glDeleteBuffers(1, &VBO);
	// glfwTerminate();
	//return (0);
}

void	key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else
			if (action == GLFW_RELEASE)
				keys[key] = false;
	}
}

void	do_movement()
{
	GLfloat cameraSpeed = 5.0f * deltaTime;
	if (keys[GLFW_KEY_W])
		cameraPos += cameraSpeed * cameraFront;
	if (keys[GLFW_KEY_S])
		cameraPos -= cameraSpeed * cameraFront;
	if (keys[GLFW_KEY_A])
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (keys[GLFW_KEY_D])
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
	GLfloat		xoffset;
	GLfloat		yoffset;
	GLfloat		sensitivity;
	glm::vec3	front;

	if(firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	xoffset = xpos - lastX;
	yoffset = lastY - ypos; 
	lastX = xpos;
	lastY = ypos;

	sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	yaw   += xoffset;
	pitch += yoffset;
	
	if (pitch > glm::radians(89.0f))
		pitch =  glm::radians(89.0f);
	if (pitch < glm::radians(-89.0f))
		pitch = glm::radians(-89.0f);

	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

void	scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	if (fov >= glm::radians(1.0f) && fov <= glm::radians(45.0f))
		fov -= yoffset;
	if (fov <= glm::radians(1.0f))
		fov = glm::radians(1.0f);
	if (fov >= glm::radians(45.0f))
		fov = glm::radians(45.0f);
}
