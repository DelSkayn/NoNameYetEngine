#version 330
#define M_PI 3.1415926535897932384626433832795

uniform float reflectance = 0.2;
uniform float metalness = 0.0;
uniform vec3 spec_color;

uniform sampler2D albedo_texture;
uniform sampler2D roughness_texture;
uniform sampler2D normal_texture;

in VS_OUT{
	vec3 N;
	vec3 L;
	vec3 V;
    vec2 coords;
    mat3 TBN;
} fs_in;

out vec4 color;

void main(){
	vec3 V = normalize(fs_in.V);
	vec3 L = normalize(fs_in.L);
    vec3 H = normalize(L + V);
    vec3 tangent = normalize(fs_in.tangent);
    vec3 bi_tangent = cross(tangent,N);
    mat3 tbn = mat3(tangent,bi_tangent,N);
    vec3 N = texture(normal_texture,fs_in.coords).xyz;
    N = normalize(N * 2.0 - 1.0);
    N = normalize(fs_in.TBN * N);


    float roughness = 1 - texture(roughness_texture, fs_in.coords).x;

    //D term
    float alpha = roughness * roughness;
    float alpha2 = alpha * alpha;
    float n_dot_h = clamp(dot(N,H),0.0,1.0);
    float term = n_dot_h * n_dot_h * (alpha2 -1) +1;
    vec3 D = vec3(alpha2 / (M_PI * (term * term)));

    //F term
    vec3 f0 = spec_color;
    vec3 F = f0 + (1 - f0) * pow(1-dot(N,V),5);

    //temp G term
    float k = alpha /2;
    float n_dot_l = clamp(dot(N,L),0.0,1.0);
    float n_dot_v = clamp(dot(N,V),0.0,1.0);
    float G1 = n_dot_v / (n_dot_v * (1.0 -k) + k);
    float G2 = n_dot_l / (n_dot_l * (1.0 -k) + k);
    vec3 G = vec3(clamp(G1*G2,0.0,1.0));
    
    vec3 specular = (D * F* G) / (4 * dot(N,L)*dot(N,V));
    vec3 diffuse = texture(albedo_texture, fs_in.coords).xyz;

    vec3 lightColor = n_dot_l * (specular + mix(diffuse,vec3(0,0,0),metalness));
    color = vec4(lightColor,0) + vec4(0.1,0.1,0.1,0.0);
}

