#include "pch.h"
#include "Rasterizer.h"
#include "Camera.h"
#include "Triangle.h"
#include "objloader.h"
#include "Struct.h"
Rasterizer::Rasterizer(int width, int height, float fovY, Vector3 viewFrom, Vector3 viewAt) {
	this->camera = Camera(width, height, fovY, viewFrom, viewAt, 1.0f, 99.0f);

	//this->light = std::make_shared<Directional>(Vector3{ -200, -300, 200 }, Vector3{ 0, 0, 0 }, deg2rad(45), 1024, 1024);
	//this->light = std::make_shared<Directional>(Vector3 {50, 0, 0}, Vector3 {0, 0, 0}, deg2rad(45), 1024, 1024);
}

/* OpenGL check state */
bool check_gl_1(const GLenum error) {
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
void glfw_callback_1(const int error, const char* description) {
	printf("GLFW Error (%d): %s\n", error, description);
}

/* OpenGL messaging callback */
void GLAPIENTRY gl_callback_1(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* user_param) {
	printf("GL %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "Error" : "Message"),
		type, severity, message);
}

/* invoked when window is resized */
void framebuffer_resize_callback_1(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

int Rasterizer::initOpenGL(int width, int height) {
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

	this->window = glfwCreateWindow(width, height, "PG2 OpenGL", nullptr, nullptr);
	if (!this->window)
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwSetFramebufferSizeCallback(this->window, framebuffer_resize_callback_1); // zavola se resize callback
	glfwMakeContextCurrent(this->window); //fukce opengl muzeme volat jen z vlakna, ze ktereho jsme hoh vytvorili. Drahe, ale funkcni.


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

int Rasterizer::loadMesh(const std::string& file_name) {
	SceneGraph scene; // scena a materialy
	MaterialLibrary materials;
	//TODO nechce nacist tridni scene a material
	LoadOBJ(file_name, scene, materials);
	struct Vertex {
		Vector3 position; /* vertex position */
		Vector3 normal; /* vertex normal */
		Vector3 color; /* vertex color */
		Vector2 texture_coord; /* vertex texture coordinate */
		Vector3 tangent; /* vertex tangent */
		int material_index; /* material index */
	};

	struct TriangleWithAdjacency {
		std::array<Vertex, 6> vertices;
	} dst_triangle;

	std::vector<TriangleWithAdjacency> triangles;
	// dostat se k jedotlivym geometriim z .obj
	for (SceneGraph::iterator iter = scene.begin();iter != scene.end();++iter) {// pro kazdy mesh
		const std::string& node_name = iter->first;
		const auto& node = iter->second;

		const auto& mesh = std::static_pointer_cast<Mesh>(node);

		if (mesh) {
			for (Mesh::iterator iter = mesh->begin(); iter != mesh->end(); ++iter){ // pro kazdy trojuhelnik
			
				const auto& src_triangle = Triangle3i(**iter);
				std::shared_ptr<Material> material = iter.triangle_material();
				const int material_index = int(std::distance(std::begin(materials), materials.find(material->name())));

				printf("Triangle:\n");

				for (int i = 0; i < 3; ++i){ //pro kazdy bod
					//data.push_back(Vertex{ src_triangle.position(i) });
					dst_triangle.vertices[i * 2].position = src_triangle.position(i);
					dst_triangle.vertices[i * 2].position.Print();
					dst_triangle.vertices[i * 2].normal = src_triangle.normal(i);
					dst_triangle.vertices[i * 2].color = Vector3(1.0f, 1.0f, 1.0f);
					dst_triangle.vertices[i * 2].texture_coord = Vector2(src_triangle.texture_coord(i).x, src_triangle.texture_coord(i).y);
					dst_triangle.vertices[i * 2].tangent = src_triangle.tangent(i);
					dst_triangle.vertices[i * 2].material_index = material_index;

					dst_triangle.vertices[i * 2 + 1].position = src_triangle.adjacent_vertex_position(i).value_or(Vector3());
					dst_triangle.vertices[i * 2 + 1].normal = Vector3();
					dst_triangle.vertices[i * 2 + 1].color = Vector3();
					dst_triangle.vertices[i * 2 + 1].texture_coord = Vector2();
					dst_triangle.vertices[i * 2 + 1].tangent = Vector3();
					dst_triangle.vertices[i * 2 + 1].material_index = -1;
				}

				triangles.push_back(dst_triangle);


				printf("Adjacent vertices:\n");

				for (int i = 0; i < 3; ++i) {
					std::optional<Vector3> av = src_triangle.adjacent_vertex_position(i);
					if (av.has_value()) {
						av.value().Print();
					} else {
						printf("-\n");
					}
				}
			}
		}
	}

	return 0;
}
int Rasterizer::initBuffer() {
	GLuint vao = 0;
	glGenVertexArrays(1, &vao); //vygeneruj mi jeden vertex array, dej mi jeho ID do vao. Vao udrzuje info okolo vsecho
	glBindVertexArray(vao); // "odted pouzivej vao pro vsec o potrebujes."
	GLuint vbo = 0;
	glGenBuffers(1, &vbo); // generate vertex buffer object (one of OpenGL objects) and get the unique ID corresponding to that buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // bind the newly created buffer to the GL_ARRAY_BUFFER target
	auto vertices = this->getVertices();
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // copies the previously defined vertex data into the buffer's memory
	//glBufferData( GL_ARRAY_BUFFER, sizeof( Vertex )*verticies.size(), verticies.data(), GL_STATIC_DRAW ); // copies the previously defined vertex data into the buffer's memory
	// vertex position
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertex_stride, 0); // definujeme co jsme do bufferu na grafiku prave nasypali
	// první 3 jsou nenormalizovane floaty, se skokem vertexh_stride (fyzicka velikost v bitech (tady 20), ne delka pole)
	// 0, 3 = jakoby ID toho pointeru ve strukture
	glEnableVertexAttribArray(0);
	// vertex texture coordinates
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertex_stride, (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	// indexy nepouzivame
	GLuint ebo = 0; // optional buffer of indices
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// a máme model natazeny na grafice.
	// 
	return 0;
}
int Rasterizer::initShaders() {
	return 0;
}
int Rasterizer::mainLoop() {
	return 0;
}