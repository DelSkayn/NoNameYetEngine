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
    mat3 tbn;
    vec3 normal;
} vs_out;

void main(){
    mat4 mv = view * model;
    gl_Position = projection * mv * vec4(position, 1.0);

    vs_out.position = (model * vec4(position,1.0)).xyz;
    vs_out.tex_coord = tex_coord;

    mat3 normal_matrix = transpose(inverse(mat3(model)));
    vec3 t = normalize(normal_matrix * tangent);
    vec3 n = normalize(normal_matrix * normal);
    vec3 b = normalize(cross(t,n));

    mat3 tbn = transpose(mat3(t,b,n));
    vs_out.tbn = tbn;
    vs_out.normal = n;
}
