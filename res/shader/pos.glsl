#version 330
uniform sampler2D input;
uniform float exposure;

in vec2 tex_coord;
out vec4 color;

void main(){
    color = vec4(texture(input, tex_coord).rgb/500.0, 1.0f);
}
