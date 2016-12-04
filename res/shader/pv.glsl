#version 330

uniform sampler2D NNY_Tex_Diffuse0;
uniform sampler2D NNY_Tex_Normal;

uniform vec3 NNY_diffuse;


uniform vec3 NNY_LightColor;
uniform float NNY_LightIntensity;
uniform vec3 NNY_LightDirection;
uniform vec3 NNY_LightPosition;
uniform float NNY_LightAngle;

uniform vec3 Ligpos = vec3(10,10.0,10.0);

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textureCoords;

uniform mat4 NNY_MVPMat;
uniform mat4 NNY_MVMat;
uniform mat4 NNY_PMat;



out VS_OUT{
	vec3 N;
	vec3 L;
	vec3 V;
	vec3 color;
        vec2 texturePos;
} vs_out;

void main()
{
	vec4 P = NNY_MVMat * vec4(position,1.0);
	vs_out.N = mat3(NNY_MVMat) * normal;
    vs_out.L = (NNY_MVMat * vec4(Ligpos,1.0) - P).xyz;
	vs_out.V = P.xyz * -1;
	vs_out.color = NNY_diffuse;
    vs_out.texturePos = position.xy;

    gl_Position = NNY_PMat * P;
}
