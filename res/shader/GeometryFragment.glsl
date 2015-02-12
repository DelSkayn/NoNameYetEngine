#version 430

uniform sampler2D sampler;

in FS_OUT {
	vec3 normal;
} vs_in;

out vec4 color;


void main(){
		color = vec4(vs_in.normal,0.0);
} 