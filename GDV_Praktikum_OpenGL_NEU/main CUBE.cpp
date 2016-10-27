//
//  main.cpp
//  GDVTest
//
//  Created by Stephan Gimbel on 12/03/16.
//  Modified by Björn Frömmer on 07/04/16.
//  Copyright (c) 2016 Hochschule Darmstadt. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <string>

using namespace glm;

// window size
//int g_gl_width  = 1024;
//int g_gl_height =  768;

int g_gl_width  = 600;
int g_gl_height = 600;


// helper function to load, compile and link shaders. Returns a valid shader program
GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path){
	// Create the shaders
	GLuint VertexShaderID   = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if( VertexShaderStream.is_open() ){
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	} else {
		printf("Cannot open %s.\n", vertex_file_path);
		getchar();
		return 0;
	}
	
	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if( FragmentShaderStream.is_open() ){
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;
	
	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const* FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}
	
	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);
	
	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}
	
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	
	return ProgramID;
}

// callback function for resizing window
void glfw_window_size_callback (GLFWwindow* window, int width, int height) {
	g_gl_width = width;
	g_gl_height = height;
	
	/* update any perspective matrices used here */
}

void _update_fps_counter (GLFWwindow* window) {
	static double previous_seconds = glfwGetTime ();
	static int frame_count;
	double current_seconds = glfwGetTime ();
	double elapsed_seconds = current_seconds - previous_seconds;
	if (elapsed_seconds > 0.25) {
		previous_seconds = current_seconds;
		double fps = (double)frame_count / elapsed_seconds;
		char tmp[128];
		sprintf_s (tmp, "opengl @ fps: %.2f", fps);
		glfwSetWindowTitle (window, tmp);
		frame_count = 0;
	}
	frame_count++;
}

int main(int argc, const char * argv[])
{
	if (!glfwInit ()) {
		fprintf (stderr, "Failed to initialize GLFW3\n");
		return -1;
	}
	
	//glfwWindowHint(GLFW_SAMPLES, 4); // enable 4x AA
	
	// Force specific OpenGL version on OS X
	#ifdef __APPLE__
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#endif
	
	GLFWwindow* window = glfwCreateWindow (g_gl_width, g_gl_height, "GDV Praktikum", NULL, NULL);
	if (!window) {
		fprintf (stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent (window); // initialize GLEW
	glewExperimental = GL_TRUE;      // for core profile
	
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}
	
	// capture keys
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	
	// get version info (for debug purpose)
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version  = glGetString(GL_VERSION);
	printf ("Renderer: %s\n", renderer);
	printf ("OpenGL version supported %s\n", version);
	
	// create vertex array object (VAO)
	GLuint VertexArrayID = 0;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	
	// cube
	static const GLfloat g_vertex_buffer_data[] = {
		// Vorderseite
		-1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		// Rechte Seite
		 1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		//Rueckseite
		-1.0f, 1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		// Linke Seite
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		// Deckflaeche
		-1.0f, 1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		// Bodenflaeche
		-1.0f,-1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f
	};
	
	static const GLfloat g_color_buffer_data[] = {
		// Vorderseite
		1.0f,  0.0f,  1.0f, // magenta
		1.0f,  1.0f,  1.0f, // weiss
		1.0f,  0.0f,  0.0f, // rot
		1.0f,  1.0f,  1.0f, // weiss
		1.0f,  1.0f,  0.0f, // gelb
		1.0f,  0.0f,  0.0f, // rot
		// Rechte Seite
		1.0f,  1.0f,  1.0f, // weiss
		0.0f,  1.0f,  1.0f, // cyan
		1.0f,  1.0f,  0.0f, // gelb
		0.0f,  1.0f,  1.0f, // cyan
		0.0f,  1.0f,  0.0f, // gruen
		1.0f,  1.0f,  0.0f, // gelb
		// Rueckseite
		0.0f,  0.0f,  1.0f, // blau
		0.0f,  1.0f,  1.0f, // cyan
		0.0f,  0.0f,  0.0f, // schwarz
		0.0f,  1.0f,  1.0f, // cyan
		0.0f,  1.0f,  0.0f, // gruen
		0.0f,  0.0f,  0.0f, // schwarz
		// Linke Seite
		1.0f,  0.0f,  1.0f, // magenta
		0.0f,  0.0f,  1.0f, // blau
		1.0f,  0.0f,  0.0f, // rot
		0.0f,  0.0f,  1.0f, // blau
		0.0f,  0.0f,  0.0f, // schwarz
		1.0f,  0.0f,  0.0f, // rot
		// Deckflaeche
		0.0f,  0.0f,  1.0f, // blau
		0.0f,  1.0f,  1.0f, // cyan
		1.0f,  0.0f,  1.0f, // magenta
		0.0f,  1.0f,  1.0f, // cyan
		1.0f,  1.0f,  1.0f, // weiss
		1.0f,  0.0f,  1.0f, // magenta
		// Bodenflaeche
		0.0f,  0.0f,  0.0f, // schwarz
		0.0f,  1.0f,  0.0f, // gruen
		1.0f,  0.0f,  0.0f, // rot
		0.0f,  1.0f,  0.0f, // gruen
		1.0f,  1.0f,  0.0f, // gelb
		1.0f,  0.0f,  0.0f, // rot
	};
	
	// create a vertex buffer to pass triangle to OpenGL
	GLuint vertexbuffer = 0;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	
	// create color buffer to pass on colors
	GLuint colorbuffer = 0;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
	
	// clear color for background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	
	// create shader program
	GLuint programID = LoadShaders( "SimpleVertexShader.vs", "SimpleFragmentShader.fs" );
	
	// create MVP Matrix

	// Projection matrix : 45° Field of View, 1:1 ratio, display range : 0.1 unit <-> 100 units
	//glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 1.0f / 1.0f, 0.1f, 100.0f);
	
	// for ortho camera:
	glm::mat4 Projection = glm::ortho(-2.0f,2.0f,-2.0f,2.0f,0.0f,100.0f);
	
	// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(2,2,5), // Camera pos in World Space
		glm::vec3(0,0,0), // looks at
		glm::vec3(0,1,0)  // up vector
	);
	
	// Model matrix: identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);
	
	// rotation
	//Model = glm::rotate(Model, glm::radians(-30.0f), glm::vec3(0,1,0));
	//Model = glm::rotate(Model, glm::radians(-20.0f), glm::vec3(1,0,0));
	//Model = glm::rotate(Model, glm::radians(-30.0f), glm::vec3(0,1,0));

	glm::mat4 mvp = Projection * View * Model;
	
	// handle for MVP uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);
		
		// send mvp matrix to shader
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
		
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0 for layout
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized
			0,                  // stride
			(void*)0            // array buffer offset
		);
		
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(
			1,                  // attribute for layout 1
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized
			0,                  // stride
			(void*)0            // array buffer offset
		);
		
		glDrawArrays(GL_TRIANGLES, 0, 12*3); // draw with proper size
		
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		
		
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	} while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );
	
	
	// cleanup
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);
	
	glfwTerminate();
	
	return 0;
}

