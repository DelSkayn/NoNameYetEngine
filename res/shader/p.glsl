#define M_PI 3.1415926535897932384626433832795

uniform float NNY_metalness = 1.0;
uniform vec3 NNY_specColor = vec3(1.0,0.86,0.57);


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

    //D term
    float alpha = NNY_Roughness * NNY_Roughness;
    float alpha2 = alpha * alpha;
    float NdotH = dot(N,H);
    float term = NdotH * NdotH * (alpha2 -1) +1;
    vec3 D = vec3(alpha2 / (M_PI * (term * term)));

    //F term
    vec3 f0 = NNY_specColor;
    vec3 F = f0 + (1 - f0) * pow(dot(V,H),5);

    //temp G term
    float k = alpha /2;
    float NdotL = clamp(dot(N,L),0.0,1.0);
    float NdotV = clamp(dot(N,V),0.0,1.0);
    float G1 = NdotV / (NdotV * (1.0 -k) + k);
    float G2 = NdotL / (NdotL * (1.0 -k) + k);
    float G = min(G1,G2);
    
    vec3 specular = (D * F * G) / (4 * NdotL * NdotV);
    vec3 diffuse = vec3(NNY_Reflectance/M_PI);
    diffuse = diffuse;

    vec3 lightColor = NdotL * (specular + mix(diffuse,vec3(0,0,0),NNY_metalness));
    color = vec4(lightColor*NNY_specColor,0);

}
