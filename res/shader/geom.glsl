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
    mat3 tbn;
    vec3 normal;
} fs_in;

layout (location = 0) out vec4 out_albedo_roughness;
layout (location = 1) out vec3 out_normal;
layout (location = 2) out vec3 out_position;


void main(){
    vec3 normal;
    if(has_normal_texture){
        normal = texture(normal_texture,fs_in.tex_coord).xyz;
        normal = normalize(normal * 2.0 - 1.0);
        normal = fs_in.tbn * normal;
    }else{
        normal = fs_in.normal;
    }
    out_normal = normal;
    vec3 color = texture(albedo_texture, fs_in.tex_coord).xyz;
    float roughness = 1 - texture(roughness_texture, fs_in.tex_coord).x * 0.7; 
    out_albedo_roughness = vec4(color,roughness);
    out_position = fs_in.position;
}
