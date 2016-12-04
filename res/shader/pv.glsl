#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 tex_coords;
layout (location = 3) in vec3 tangent;

uniform mat4 MVPMat;
uniform mat4 MVMat;
uniform mat4 PMat;

uniform vec3 Ligpos = vec3(0,1000,0.0);

out VS_OUT{
    vec3 N;
    vec3 L;
    vec3 V;
    vec2 coords;
    mat3 TBN;
} vs_out;

void main()
{
    gl_Position = MVPMat * vec4(position,1.0);
    vec3 T = normalize(tangent);
    vec3 N = normalize(normals);
    vec3 B = normalize(cross(N,T));
    vs_out.TBN = mat3(T,B,N);

    vec4 P = MVMat * vec4(position,1.0);
    vs_out.N = mat3(MVMat) * N;

    vs_out.L = (vec4(mat3(MVMat) * Ligpos,1.0) - P).xyz;
    vs_out.V = P.xyz * -1;
    vs_out.coords = tex_coords;
}
