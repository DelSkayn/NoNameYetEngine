#version 330
#define M_PI 3.1415926535897932384626433832795

uniform sampler2D NNY_Tex_Diffuse0;
uniform sampler2D NNY_Tex_Normal;

uniform float NNY_reflectance = 0.2;
uniform float NNY_roughness = 0.80;

uniform float NNY_metalness = 1.0;
uniform vec3 NNY_spec_color = vec3(1.0,0.86,0.57);

in VS_OUT{
	vec3 N;
	vec3 L;
	vec3 V;
	vec3 color;
    vec2 texturePos;
} fs_in;

out vec4 color;

void main(){ vec3 N = normalize(fs_in.N); vec3 V = normalize(fs_in.V);
	vec3 L = normalize(fs_in.L);
    vec3 H = normalize(L + V);

    //D term
    float alpha = NNY_roughness * NNY_roughness;
    float alpha2 = alpha * alpha;
    float n_dot_h = clamp(dot(N,H),0.0,1.0);
    float term = n_dot_h * n_dot_h * (alpha2 -1) +1;
    vec3 D = vec3(alpha2 / (M_PI * (term * term)));

    //F term
    vec3 f0 = NNY_spec_color;
    vec3 F = f0 + (1 - f0) * pow(1-dot(N,V),5);

    //temp G term
    float k = alpha /2;
    float n_dot_l = clamp(dot(N,L),0.0,1.0);
    float n_dot_v = clamp(dot(N,V),0.0,1.0);
    float G1 = n_dot_v / (n_dot_v * (1.0 -k) + k);
    float G2 = n_dot_l / (n_dot_l * (1.0 -k) + k);
    vec3 G = vec3(clamp(G1*G2,0.0,1.0));
    
    vec3 specular =(D * F* G) / (4 * dot(N,L)*dot(N,V));
    vec3 diffuse = vec3(NNY_reflectance/M_PI);
    diffuse = NNY_spec_color * diffuse * n_dot_l;

    vec3 light_color = specular + mix(diffuse,vec3(0,0,0),NNY_metalness);

    color = vec4(light_color+fs_in.color,0) + vec4(0.1,0.1,0.1,0.0);

}
