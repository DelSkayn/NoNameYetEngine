#version 330 

#define M_PI 3.1415926535897932384626433832795

uniform float uni_reflectance = 0.9;
uniform float uni_roughness = 0.1;
uniform vec3 uni_specColor = vec3(1.0,1.0,1.0);
uniform vec3 ambient = vec3(0.1,0.1,0.1);


in VS_OUT{
	vec3 N;
	vec3 L;
	vec3 V;
	vec3 color;
    vec2 texturePos;
} fs_in;

out vec4 color;

void main(){
	vec3 N = normalize(fs_in.N);
	vec3 V = normalize(fs_in.V);
	vec3 L = normalize(fs_in.L);
    vec3 H = normalize(L + V);

    //D
    float alpha = uni_roughness * uni_roughness;
    float alpha2 = alpha * alpha;
    float NdotH = dot(N,H);
    float term = NdotH * NdotH * (alpha2 -1) +1;
    vec3 D = vec3(alpha2 / (M_PI * (term * term)));

    //F
    vec3 f0 = uni_specColor;
    vec3 F = f0 + (1 - f0) * pow(2, (-5.55473 * (dot(V, H)) - 6.98316) * (dot(V, H)));         

    //temp G
    float k = alpha /2;
    float G1 = dot(N,V) / (dot(N,V) * (1.0 -k) + k);
    float G2 = dot(N,L) / (dot(N,L) * (1.0 -k) + k);
    vec3 G = vec3(G1*G2);
    
    vec3 specular = D * F * G / 4 * (dot(N,L)*dot(N,V));
    float NdotL = dot(N,L);
    vec3 diffuse = vec3(uni_reflectance/M_PI);
    diffuse = diffuse * NdotL;

    vec3 lightColor = specular + diffuse + fs_in.color + ambient;

    color = vec4(lightColor,0);
}
