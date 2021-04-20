#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>

#define numVAOs 1
GLuint renderingProgram;
GLuint vao[numVAOs];
double size = 0;


// NEW LINES
/////////////////////////////////////////////////////////////////////////////
																		  ///
void printShaderLog(GLuint shader) {									  ///
	int len = 0;														  ///
	int chWrittn = 0;													  ///
	char *log;															  ///
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);					  ///
	if (len > 0) {														  ///
		log = (char*)malloc(len);										  ///
		glGetShaderInfoLog(shader, len, &chWrittn, log);				  ///
		std::cout << "Shader info log: " << log << std::endl;			  ///
		free(log);														  ///
	}																	  ///
	return;																  ///
}																		  ///
																		  ///
void printProgramLog(GLuint program) {									  ///
	int len = 0;														  ///
	int chWrittn = 0;													  ///
	char* log;															  ///
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);					  ///
	if (len > 0) {														  ///
		log = (char*)malloc(len);										  ///
		glGetProgramInfoLog(program, len, &chWrittn, log);				  ///
		std::cout << "Program info log: " << log << std::endl;			  ///
		free(log);														  ///
	}																	  ///
	return;																  ///
}																		  ///
																		  ///
bool checkOpenGLError() {												  ///
	bool foundError = false;											  ///
	int glErr = glGetError();											  ///
	while (glErr != GL_NO_ERROR) {										  ///
		std::cout<< "glError: " << glErr << std::endl;					  ///
		foundError = true;												  ///
		glErr = glGetError();											  ///
	}																	  ///
	return foundError;													  ///
}																		  ///
																		  ///
/////////////////////////////////////////////////////////////////////////////

GLuint createShaderProgram(GLFWwindow* window) {
	const char* vShaderSource =
		"#version 430 \n"
		"void main(void) \n"
		"{gl_Position = vec4(0,0,0,1);}";

	const char* fShaderSource =
		"#version 430 \n"
		"out vec4 color;"
		"void main(void) { \n"
		"	if(gl_FragCoord.x > 300) color = vec4(1.0, 1.0, 1.0, 0.0); \n"
		"   else color = vec4(0.0, 0.0, 0.0, 0.0);"
		"}";

	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vShader, 1, &vShaderSource, NULL);
	glShaderSource(fShader, 1, &fShaderSource, NULL);


	glCompileShader(vShader);
	//////////////////////////////////////////////////////////////////////////////
	checkOpenGLError();														   ///
	GLint vertCompiled;														   ///
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);				   ///
	if (vertCompiled != 1) {												   ///	NEW LINES
		std::cout << "Vertex shader compilation failed.." << std::endl;		   ///
		printShaderLog(vShader);											   ///
	}																		   ///
	//////////////////////////////////////////////////////////////////////////////

	glCompileShader(fShader);
	//////////////////////////////////////////////////////////////////////////////
	checkOpenGLError();														   ///
	GLint fragCompiled;														   ///
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);				   ///
	if (fragCompiled != 1) {												   ///   NEW LINES
		std::cout << "Fragment shader compilation failed.. " << std::endl;	   ///
		printShaderLog(fShader);											   ///
	}																		   ///
	//////////////////////////////////////////////////////////////////////////////

	GLint vfProgram = glCreateProgram();
	glAttachShader(vfProgram, vShader);
	glAttachShader(vfProgram, fShader);

	glLinkProgram(vfProgram);
	///////////////////////////////////////////////////////////////////////////////
	checkOpenGLError();															///
	GLint linked;																///
	glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);							///
	if (linked != 1) {															///   NEW LINES
		std::cout << "Linking Failed.." << std::endl;							///
		printProgramLog(vfProgram);												///
	}																			///
	///////////////////////////////////////////////////////////////////////////////
	return vfProgram;
}

//  initialize the shader program
void init(GLFWwindow* window) {
	renderingProgram = createShaderProgram(window);
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);
}

// display loop
void display(GLFWwindow* window) {
	float r = 0.08, g = r * 2, b = g * 1.5;
	glClearColor(r, g, b, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(renderingProgram);
	bool flag;
	size++;
	double x = abs(255/** sin((3*size/100.0))*/ * cos((5 * size / 100.0)));
	GLint pointsize;
	glGetIntegerv(GL_POINT_SIZE, &pointsize);
	//std::cout << pointsize << std::endl;
	glEnable(GL_PROGRAM_POINT_SIZE);
	glPointSize(x);
	glDrawArrays(GL_POINTS, 0, 1);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	GLFWwindow* window = glfwCreateWindow(600, 600, "Initialize an instance", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) return 1;
	glfwSwapInterval(1);
	init(window);
	while (!glfwWindowShouldClose(window)) {
		display(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}