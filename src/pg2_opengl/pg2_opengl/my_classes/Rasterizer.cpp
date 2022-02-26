#include "pch.h"
#include "Rasterizer.h"
#include "Camera.h"

Rasterizer::Rasterizer(int width, int height, float fovY, Vector3 viewFrom, Vector3 viewAt) {
	this->camera = Camera(width, height, fovY, viewFrom, viewAt, 1.0f, 99.0f);

	//this->light = std::make_shared<Directional>(Vector3{ -200, -300, 200 }, Vector3{ 0, 0, 0 }, deg2rad(45), 1024, 1024);
	//this->light = std::make_shared<Directional>(Vector3 {50, 0, 0}, Vector3 {0, 0, 0}, deg2rad(45), 1024, 1024);
}

/* OpenGL check state */
bool check_gl_1(const GLenum error)
{
	if (error != GL_NO_ERROR)
	{
		//const GLubyte * error_str;
		//error_str = gluErrorString( error );
		//printf( "OpenGL error: %s\n", error_str );

		return false;
	}

	return true;
}

/* glfw callback */
void glfw_callback_1(const int error, const char* description)
{
	printf("GLFW Error (%d): %s\n", error, description);
}

/* OpenGL messaging callback */
void GLAPIENTRY gl_callback_1(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* user_param)
{
	printf("GL %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "Error" : "Message"),
		type, severity, message);
}

/* invoked when window is resized */
void framebuffer_resize_callback_1(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int Rasterizer::initOpenGL(int width, int height)
{
	glfwSetErrorCallback(glfw_callback_1);

	if (!glfwInit())
	{
		return(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 8); // 8 samplu na pixel
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(width, height, "PG2 OpenGL", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback_1); // zavola se resize callback
	glfwMakeContextCurrent(window); //fukce opengl muzeme volat jen z vlakna, ze ktereho jsme hoh vytvorili. Drahe, ale funkcni.


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) // umozni folani funkci z opengl
	{
		if (!gladLoadGL())
		{
			return EXIT_FAILURE;
		}
	}

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(gl_callback_1, nullptr); // debugging je nahovno, tak tady aspon nejake zpravy o chybach

	printf("OpenGL %s, ", glGetString(GL_VERSION));
	printf("%s", glGetString(GL_RENDERER));
	printf(" (%s)\n", glGetString(GL_VENDOR));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	check_gl_1();

	glEnable(GL_MULTISAMPLE);

	// map from the range of NDC coordinates <-1.0, 1.0>^2 to <0, width> x <0, height>
	glViewport(0, 0, width, height);
	// GL_LOWER_LEFT (OpenGL) or GL_UPPER_LEFT (DirectX, Windows) and GL_NEGATIVE_ONE_TO_ONE or GL_ZERO_TO_ONE
	glClipControl(GL_UPPER_LEFT, GL_NEGATIVE_ONE_TO_ONE); // od -1 do 1




	return 0;
}
int Rasterizer::loadMash(const std::string& file_name) {
	return 0;
}
int Rasterizer::initBuffer() {
	return 0;
}
int Rasterizer::initShaders() {
	return 0;
}
int Rasterizer::mainLoop() {
	return 0;
}