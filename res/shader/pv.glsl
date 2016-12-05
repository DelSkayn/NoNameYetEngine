#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 tex_coord;
layout (location = 3) in vec3 tangent;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 light_position = vec3(0.0,10.0,0.0);
uniform vec3 view_position;

out VS_OUT{
    vec3 position;
    vec2 tex_coord;
    vec3 t_light;
    vec3 t_view;
    vec3 t_position;
    vec3 normal;
} vs_out;

void main(){
    gl_Position = projection * view * model * vec4(position, 1.0);
    vs_out.position = vec3(model * vec4(position,1.0));
    vs_out.tex_coord = tex_coord;

    mat3 normal_matrix = transpose(inverse(mat3(model)));
    vec3 t = normalize(normal_matrix * tangent);
    vec3 n = normalize(normal_matrix * normal);
    vec3 b = normalize(cross(t,n));

    mat3 tbn = transpose(mat3(t,b,n));
    vs_out.t_light = tbn * light_position;
    vs_out.t_view = tbn * view_position;
    vs_out.t_position = tbn * vs_out.position;
    vs_out.normal = tbn * n;
}
