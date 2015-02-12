#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 textureCoords;

uniform mat4 worldToClipMatrix;
uniform mat4 modelToWorldMatrix;

out FS_OUT{
	vec3 normal;
} fs_out;

void main()
{
	fs_out.normal = normals;
    gl_Position =  worldToClipMatrix * modelToWorldMatrix * vec4(position, 1.0);
}//