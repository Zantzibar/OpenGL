#version 410

layout (location = 0) in vec3 vertexPosition_modelspace;
layout (location = 1) in vec3 vertexColor;

// constant for the whole mash
uniform mat4 MVP;

// pass color to fragment shader
out vec3 fragmentColor;

void main() {
    gl_Position = MVP * vec4(vertexPosition_modelspace, 1.0);
    fragmentColor = vertexColor;
}