//
//  main.cpp
//  GDVTest
//
//  Created by Stephan Gimbel on 12/03/16.
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
#include <vector>

using namespace glm;

// window size
int g_gl_width  = 1024;
int g_gl_height =  768;

// helper function to load, compile and link shaders. Returns a valid shader program
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){
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
    char const * VertexSourcePointer = VertexShaderCode.c_str();
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
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
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
        sprintf (tmp, "opengl @ fps: %.2f", fps);
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
    
    // create a simple triangle
    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f,
    };
    
    // create a vertex buffer to pass triangle to OpenGL
    GLuint vertexbuffer = 0;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    

    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );
    
    // clear color for background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    
    // create shader program
    GLuint programID = LoadShaders( "SimpleVertexShader.vs", "SimpleFragmentShader.fs" );
    
    // create MVP Matrix

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    
    // for ortho camera:
    //glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f);
    
    // Camera matrix
    glm::mat4 View = glm::lookAt(
        glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
        glm::vec3(0,0,0), // and looks at the origin
        glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    
    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model = glm::mat4(1.0f);
    
    glm::mat4 mvp = Projection * View * Model;
    
    // handle for MVP uniform
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    
    
    
    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);
        
        // send mvp matrix to shader
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
        
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );
        
        // Draw nothing, see you in tutorial 2 !
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);
        
        
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    } while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );
    
    
    // cleanup
    glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);
    
	glfwTerminate();
    
    
//    // get version info
//    const GLubyte* renderer = glGetString (GL_RENDERER); // get renderer string
//    const GLubyte* version = glGetString (GL_VERSION); // version as a string
//    printf ("Renderer: %s\n", renderer);
//    printf ("OpenGL version supported %s\n", version);
//    
//    
//    // enable depth test
//    glEnable (GL_DEPTH_TEST);
//    glDepthFunc (GL_LESS);  // smaller value is "closer"
//    //glDepthFunc (GL_GREATER);  // smaller value is "closer"
//    
//    // set callback function for resize
//    glfwSetWindowSizeCallback (window, glfw_window_size_callback);
//    
//    /* OTHER STUFF GOES HERE NEXT */
//    
//    // triangle
//    float points[] = {
//        // 1st front
//        0.0f,  0.5f,  0.0f,
//        0.5f, -0.5f,  0.0f,
//        -0.5f, -0.5f,  0.0f
//    };
//    
//    // colour
//    float colours[] = {
//        1.0f, 0.0f,  0.0f,
//        0.0f, 1.0f,  0.0f,
//        0.0f, 0.0f,  1.0f
//    };
//    
//    static const GLfloat cube[] = {
//             -1.0f,-1.0f,-1.0f, // triangle 1 : begin
//             -1.0f,-1.0f, 1.0f,
//             -1.0f, 1.0f, 1.0f, // triangle 1 : end
//             1.0f, 1.0f,-1.0f, // triangle 2 : begin
//             -1.0f,-1.0f,-1.0f,
//             -1.0f, 1.0f,-1.0f, // triangle 2 : end
//             1.0f,-1.0f, 1.0f,
//             -1.0f,-1.0f,-1.0f,
//             1.0f,-1.0f,-1.0f,
//             1.0f, 1.0f,-1.0f,
//             1.0f,-1.0f,-1.0f,
//             -1.0f,-1.0f,-1.0f,
//             -1.0f,-1.0f,-1.0f,
//             -1.0f, 1.0f, 1.0f,
//             -1.0f, 1.0f,-1.0f,
//             1.0f,-1.0f, 1.0f,
//             -1.0f,-1.0f, 1.0f,
//             -1.0f,-1.0f,-1.0f,
//             -1.0f, 1.0f, 1.0f,
//             -1.0f,-1.0f, 1.0f,
//             1.0f,-1.0f, 1.0f,
//             1.0f, 1.0f, 1.0f,
//             1.0f,-1.0f,-1.0f,
//             1.0f, 1.0f,-1.0f,
//             1.0f,-1.0f,-1.0f,
//             1.0f, 1.0f, 1.0f,
//             1.0f,-1.0f, 1.0f,
//             1.0f, 1.0f, 1.0f,
//             1.0f, 1.0f,-1.0f,
//             -1.0f, 1.0f,-1.0f,
//             1.0f, 1.0f, 1.0f,
//             -1.0f, 1.0f,-1.0f,
//             -1.0f, 1.0f, 1.0f,
//             1.0f, 1.0f, 1.0f,
//             -1.0f, 1.0f, 1.0f,
//             1.0f,-1.0f, 1.0f
//         };
//    
//    static const GLfloat cube_colours[] = {
//             0.583f,  0.771f,  0.014f,
//             0.609f,  0.115f,  0.436f,
//             0.327f,  0.483f,  0.844f,
//             0.822f,  0.569f,  0.201f,
//             0.435f,  0.602f,  0.223f,
//             0.310f,  0.747f,  0.185f,
//             0.597f,  0.770f,  0.761f,
//             0.559f,  0.436f,  0.730f,
//             0.359f,  0.583f,  0.152f,
//             0.483f,  0.596f,  0.789f,
//             0.559f,  0.861f,  0.639f,
//             0.195f,  0.548f,  0.859f,
//             0.014f,  0.184f,  0.576f,
//             0.771f,  0.328f,  0.970f,
//             0.406f,  0.615f,  0.116f,
//             0.676f,  0.977f,  0.133f,
//             0.971f,  0.572f,  0.833f,
//             0.140f,  0.616f,  0.489f,
//             0.997f,  0.513f,  0.064f,
//             0.945f,  0.719f,  0.592f,
//             0.543f,  0.021f,  0.978f,
//             0.279f,  0.317f,  0.505f,
//             0.167f,  0.620f,  0.077f,
//             0.347f,  0.857f,  0.137f,
//             0.055f,  0.953f,  0.042f,
//             0.714f,  0.505f,  0.345f,
//             0.783f,  0.290f,  0.734f,
//             0.722f,  0.645f,  0.174f,
//             0.302f,  0.455f,  0.848f,
//             0.225f,  0.587f,  0.040f,
//             0.517f,  0.713f,  0.338f,
//             0.053f,  0.959f,  0.120f,
//             0.393f,  0.621f,  0.362f,
//             0.673f,  0.211f,  0.457f,
//             0.820f,  0.883f,  0.371f,
//             0.982f,  0.099f,  0.879f
//         };
//    
////    // cube
////    static const GLfloat cube[] = {
//////        // Front
//////        -0.5f, 0.5f, 0.5f,
//////        0.5f, 0.5f, 0.5f,
//////        -0.5f,-0.5f, 0.5f,
//////        0.5f, 0.5f, 0.5f,
//////        0.5f,-0.5f, 0.5f,
//////        -0.5f,-0.5f, 0.5f,
////        
////        // Back
////        -0.5f, 0.5f, 0.5f,
////        0.5f, 0.5f, 0.5f,
////        -0.5f,-0.5f, 0.5f,
////        0.5f, 0.5f, 0.5f,
////        0.5f,-0.5f, 0.5f,
////        -0.5f,-0.5f, 0.5f,
////        
////        // Front
////        -0.5f, 0.5f, -0.5f,
////         0.5f, 0.5f, -0.5f,
////        -0.5f,-0.5f, -0.5f,
////         0.5f, 0.5f, -0.5f,
////         0.5f,-0.5f, -0.5f,
////        -0.5f,-0.5f, -0.5f
////    };
////    
////    float cube_colours[] = {
//////        // Front
//////        1.0f, 0.0f,  1.0f,
//////        1.0f, 1.0f,  1.0f,
//////        1.0f, 0.0f,  0.0f,
//////        1.0f, 1.0f, 1.0f,
//////        1.0f, 1.0f,  0.0f,
//////        1.0f, 0.0f,  0.0f,
////        
////        // Back
////        0.0f, 0.0f,  1.0f,
////        0.0f, 1.0f,  1.0f,
////        0.0f, 0.0f,  0.0f,
////        0.0f, 1.0f, 1.0f,
////        0.0f, 1.0f,  0.0f,
////        0.0f, 0.0f,  0.0f,
////        
////        // Front
////        1.0f, 0.0f,  1.0f,
////        1.0f, 1.0f,  1.0f,
////        1.0f, 0.0f,  0.0f,
////        1.0f, 1.0f, 1.0f,
////        1.0f, 1.0f,  0.0f,
////        1.0f, 0.0f,  0.0f
////    };
//    
//    
//    GLuint points_vbo = 0;
//    glGenBuffers (1, &points_vbo);
//    glBindBuffer (GL_ARRAY_BUFFER, points_vbo);
//    //glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (float), points, GL_STATIC_DRAW); // triangle
//    glBufferData (GL_ARRAY_BUFFER,  12*9 * sizeof (float), cube, GL_STATIC_DRAW); // cube
//    
//    GLuint colours_vbo = 0;
//    glGenBuffers (1, &colours_vbo);
//    glBindBuffer (GL_ARRAY_BUFFER, colours_vbo);
//    // glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (float), cube_colours, GL_STATIC_DRAW); // triangle
//    glBufferData (GL_ARRAY_BUFFER,  12*9 * sizeof (float), cube_colours, GL_STATIC_DRAW); // cube
//    
//    GLuint vao = 0;
//    glGenVertexArrays (1, &vao);
//    glBindVertexArray (vao);
////    glEnableVertexAttribArray (0);
//    glBindBuffer (GL_ARRAY_BUFFER, points_vbo);
//    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//    glBindBuffer (GL_ARRAY_BUFFER, colours_vbo);
//    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//    
//  
//    glEnableVertexAttribArray (0);
//    glEnableVertexAttribArray (1);
//    
//    const char* vertex_shader =
//    "#version 410\n"
//    "layout(location = 0) in vec3 vertex_position;"
//    "layout(location = 1) in vec3 vertex_colour;"
//    "out vec3 colour;"
//    "void main () {"
//    "  colour = vertex_colour;"
//    "  gl_Position = vec4 (vertex_position, 1.0);"
//    "}";
//    
//    const char* fragment_shader =
//    "#version 410\n"
//    "in vec3 colour;"
//    "out vec4 frag_colour;"
//    "void main () {"
//    "  frag_colour = vec4 (colour, 1.0);"
//    "}";
//    
//    // enable culling
//    glEnable (GL_CULL_FACE);
//    glCullFace (GL_BACK);
//    glFrontFace (GL_CW);
//    
//    /* original vertex shader
//    const char* vertex_shader =
//    "#version 410\n"
//    "in vec3 vp;"
//    "void main () {"
//    "  gl_Position = vec4 (vp, 1.0);"
//    "}"; 
//     */
//    
//    /* original fragement shader
//    const char* fragment_shader =
//    "#version 410\n"
//    "out vec4 frag_colour;"
//    "void main () {"
//    "  frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
//    "}";
//     */
//    
//    // create and compile vertex and fragment shaders
//    GLuint vs = glCreateShader (GL_VERTEX_SHADER);
//    glShaderSource (vs, 1, &vertex_shader, NULL);
//    glCompileShader (vs);
//    GLuint fs = glCreateShader (GL_FRAGMENT_SHADER);
//    glShaderSource (fs, 1, &fragment_shader, NULL);
//    glCompileShader (fs);
//    
//    // create shader program and link it
//    GLuint shader_programme = glCreateProgram ();
//    glAttachShader (shader_programme, fs);
//    glAttachShader (shader_programme, vs);
//    glLinkProgram (shader_programme);
//    
//    
//    while (!glfwWindowShouldClose (window)) {
//        _update_fps_counter (window); // show fps
//        //glClearColor(0.0, 1.0, 0.0, 1.0); // clear color
//        // wipe the drawing surface clear
//        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        //glClear (GL_COLOR_BUFFER_BIT);
//        glViewport (0, 0, g_gl_width, g_gl_height); // set viewport size in case of resize
//        
//        glUseProgram (shader_programme);
//        glBindVertexArray (vao);
//        // draw points 0-3 from the currently bound VAO with current in-use shader
//        glDrawArrays (GL_TRIANGLES, 0, 12*3);
//        // update other events like input handling
//        glfwPollEvents ();
//        // put the stuff we've been drawing onto the display
//        glfwSwapBuffers (window);
//        
//        if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_ESCAPE)) { // escape
//            glfwSetWindowShouldClose (window, 1);
//        }
//    }
//    
//    
//    
//    
//    
//    // close GL context and any other GLFW resources
//    glfwTerminate();
//
//    // insert code here...
////    std::cout << "Hello, World!\n";
    return 0;
}

