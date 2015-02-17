#version 330 
uniform float Ligspecular = 128.7; uniform vec3 Matdiffuse = vec3(10.0,10.01,10.01);
uniform vec3 Matspecular = vec3(0.1);

uniform vec3 ambient = vec3(0.1, 0.1, 0.1);

uniform sampler2D texture;

in VS_OUT{
	vec3 N;
	vec3 L;
	vec3 V;
	vec3 color;
        vec2 texturePos;
	} fs_in;

layout (location = 0) out vec4 FragColor;

void main()
{
	vec3 N = normalize(fs_in.N);
    vec3 L = normalize(fs_in.L);
    vec3 V = normalize(fs_in.V);
	
    vec3 R = reflect(-L, N);
	
	float H = dot(N,L);
	
	
	vec3 diffuse;
	vec3 specular;
	if(H > 0.0){
	
	diffuse =  H * Matdiffuse;
	specular = pow(max(dot(V,R),0.0), Ligspecular)* Matspecular;
	
	} else{
	diffuse = vec3(0.0,0.0,0.0);
	specular = vec3(0.0,0.0,0.0);
	}
	
    FragColor =  vec4(diffuse + specular + ambient,1.0f);
}
