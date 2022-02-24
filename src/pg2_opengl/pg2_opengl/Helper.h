#pragma once
class Helper
{
	bool check_gl(const GLenum error);

	/* glfw callback */
	void glfw_callback(const int error, const char* description);

	/* OpenGL messaging callback */
	void GLAPIENTRY gl_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* user_param);

	/* invoked when window is resized */
	void framebuffer_resize_callback(GLFWwindow* window, int width, int height);
};

