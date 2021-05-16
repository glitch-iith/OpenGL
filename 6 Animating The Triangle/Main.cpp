#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <iterator>
#include <math.h>

#define numVAOs 1
GLuint renderingProgram;
GLuint vao[numVAOs];
double pointSize = 1;
float x = 0.0f;
float inc = 0.01f;

																  
void printShaderLog(GLuint shader) {									  
	int len = 0;														  
	int chWrittn = 0;													  
	char *log;															  
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);					  
	if (len > 0) {														  
		log = (char*)malloc(len);										  
		glGetShaderInfoLog(shader, len, &chWrittn, log);				  
		std::cout << "Shader info log: " << log << std::endl;			  
		free(log);														  
	}																	  
	return;																  
}																		  
																		  
void printProgramLog(GLuint program) {									  
	int len = 0;														  
	int chWrittn = 0;													  
	char* log;															  
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);					  
	if (len > 0) {														  
		log = (char*)malloc(len);										  
		glGetProgramInfoLog(program, len, &chWrittn, log);				  
		std::cout << "Program info log: " << log << std::endl;			  
		free(log);														  
	}																	  
	return;																  
}																		  
																		  
bool checkOpenGLError() {												  
	bool foundError = false;											  
	int glErr = glGetError();											  
	while (glErr != GL_NO_ERROR) {										  
		std::cout<< "glError: " << glErr << std::endl;					  
		foundError = true;												  
		glErr = glGetError();											  
	}																	  
	return foundError;													  
}																		  

std::string readShaderSource(const char* FILENAME) {
	std::ifstream ifs(FILENAME);
	std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
	return content;
}

GLuint createShaderProgram(GLFWwindow* window) {
	
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertShaderStr = readShaderSource("vertShader.glsl");
	std::string fragShaderStr = readShaderSource("fragShader.glsl");

	const char* vShaderSource = vertShaderStr.c_str();
	const char* fShaderSource = fragShaderStr.c_str();


	glShaderSource(vShader, 1, &vShaderSource, NULL);
	glShaderSource(fShader, 1, &fShaderSource, NULL);


	glCompileShader(vShader);

	checkOpenGLError();														   
	GLint vertCompiled;														   
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);				   
	if (vertCompiled != 1) {												   
		std::cout << "Vertex shader compilation failed.." << std::endl;		   
		printShaderLog(vShader);											   
	}

	glCompileShader(fShader);

	checkOpenGLError();														   
	GLint fragCompiled;														   
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);				   
	if (fragCompiled != 1) {												   
		std::cout << "Fragment shader compilation failed.. " << std::endl;	   
		printShaderLog(fShader);											   
	}

	GLint vfProgram = glCreateProgram();
	glAttachShader(vfProgram, vShader);
	glAttachShader(vfProgram, fShader);

	glLinkProgram(vfProgram);

	checkOpenGLError();															
	GLint linked;																
	glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);							
	if (linked != 1) {															
		std::cout << "Linking Failed.." << std::endl;							
		printProgramLog(vfProgram);												
	}
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
	float r = 0.09, g = r * 2, b = g * 1.5;
	glClearColor(r, g, b, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(renderingProgram);
	x += inc;
	if (x > 0.75f) inc = -0.01f;
	if (x < -0.75f) inc = 0.01f;
	GLuint offsetLoc = glGetUniformLocation(renderingProgram, "offset");
	glProgramUniform1f(renderingProgram, offsetLoc, x);
	glDrawArrays(GL_TRIANGLES, 0, 4);
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