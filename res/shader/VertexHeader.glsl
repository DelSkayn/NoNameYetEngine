#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textureCoords;

uniform mat4 NNY_MVPMat;
uniform mat4 NNY_MVMat;
uniform mat4 NNY_PMat;
