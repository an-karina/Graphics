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
