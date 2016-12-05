#version 330
#define M_PI 3.1415926535897932384626433832795

uniform float reflectance = 0.2;
uniform float metalness = 0.0;
uniform vec3 spec_color;

uniform sampler2D albedo_texture;
uniform sampler2D roughness_texture;
uniform sampler2D normal_texture;

uniform bool has_normal_texture;

in VS_OUT{
    vec3 position;
    vec2 tex_coord;
    vec3 t_light;
    vec3 t_view;
    vec3 t_position;
    vec3 normal;
} fs_in;

out vec4 out_color;

void main(){
	vec3 view = normalize(fs_in.t_view - fs_in.t_position);
	vec3 light = normalize(fs_in.t_light - fs_in.t_position);
    vec3 half = normalize(light + view);
    vec3 normal;
    if(has_normal_texture){
        normal = texture(normal_texture,fs_in.tex_coord).xyz;
        normal = normalize(normal * 2.0 - 1.0);
    }else{
        normal = fs_in.normal;
    }
    vec3 color = texture(albedo_texture, fs_in.tex_coord).xyz;
    vec3 ambient = 0.1 * color;


    float roughness = 1 - texture(roughness_texture, fs_in.tex_coord).x * 0.7; 

    //D term
    float alpha = roughness * roughness;
    float alpha2 = alpha * alpha;
    float n_dot_h = clamp(dot(normal,half),0.0001,1.0);
    float term = n_dot_h * n_dot_h * (alpha2 - 1) + 1;
    float D = clamp(alpha2 / (M_PI * (term * term)),0.0,1.0);

    float n_dot_v = clamp(dot(normal,view),0.0001,1.0);

    //F term
    vec3 f0 = mix(vec3(0.04),color,metalness);
    vec3 F = clamp(f0 + (1 - f0) * pow(1 - n_dot_v, 5),vec3(0.0),vec3(1.0));

    //temp G term
    float n_dot_l = clamp(dot(normal,light),0.0001,1.0);
    float k = alpha2 / 2;
    float G1 = n_dot_v / (n_dot_v * (1.0 - k) + k);
    float G2 = n_dot_l / (n_dot_l * (1.0 - k) + k);
    vec3 G = clamp(G1*G2,0.0,1.0) * color;
    
    vec3 specular = (D * F * G) / (4 * n_dot_l * n_dot_v);

    vec3 light_color = n_dot_l * specular;
    out_color = vec4(light_color + ambient, 0.0);
}
