#version 410

layout (location = 0) in vec3 vertexPosition_modelspace;

// constant for the whole mash
uniform mat4 MVP;

void main() {
    gl_Position = MVP * vec4(vertexPosition_modelspace, 1.0);
}