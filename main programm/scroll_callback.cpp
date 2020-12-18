void	scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	if (fov >= glm::radians(1.0f) && fov <= glm::radians(45.0f))
		fov -= yoffset;
	if (fov <= glm::radians(1.0f))
		fov = glm::radians(1.0f);
	if (fov >= glm::radians(45.0f))
		fov = glm::radians(45.0f);
}
