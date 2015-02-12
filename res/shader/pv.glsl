
#version 330 
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform vec3 Ligpos = vec3(0,100.0,-100.0);

uniform mat4 transform;

out VS_OUT{
	vec3 N;
	vec3 L;
	vec3 V;
	vec3 color;
        vec2 texturePos;
} vs_out;

void main()
{
	
	vec4 P = transform * vec4(position,1.0);
	
	vs_out.N = mat3(transform) * normal;
	
    vs_out.L = Ligpos - P.xyz;

	vs_out.V = P.xyz;
	vs_out.color = position - vec3(0.9,0.9,0.9);
    vs_out.texturePos = position.xy;

    gl_Position = P;
}
