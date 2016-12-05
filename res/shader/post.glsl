#version 330
uniform sampler2D input;
uniform float exposure;

in vec2 tex_coord;
out vec4 color;

void main(){
    const float gamma = 2.2;
    vec3 hdr_color = texture(input, tex_coord).rgb;

    vec3 result = vec3(1.0) - exp(-hdr_color * exposure);
    result = pow(result, vec3(1.0 / gamma));
    color = vec4(result, 1.0f);
}
