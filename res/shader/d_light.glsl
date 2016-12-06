#version 330
#define M_PI 3.1415926535897932384626433832795
uniform sampler2D in_position;
uniform sampler2D in_normal;
uniform sampler2D in_albedo;
uniform float exposure;

uniform vec3 light_direction;
uniform vec3 light_color;
uniform float light_intensity;
uniform vec3 view_pos;
uniform float gamma = 2.2;

in vec2 tex_coord;
out vec4 out_color;

void main(){
    const float metalness = 0;
    vec3 position = texture(in_position, tex_coord).rgb;
    vec3 normal = texture(in_normal, tex_coord).rgb;
    vec4 temp = texture(in_albedo, tex_coord);
    vec3 color = temp.rgb;
    float roughness = temp.a;

    vec3 view = normalize(view_pos - position);
    vec3 light = normalize(light_direction);
    vec3 half = normalize(light + view);

    vec3 ambient = 0.1 * color;
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

    vec3 hdr_color = n_dot_l * specular + ambient;

    float att = light_intensity;

    vec3 result = vec3(1.0) - exp(-hdr_color * exposure);
    result = pow(result, vec3(1.0 / gamma));
    result *= att + 0.03;
    out_color = vec4(result*light_color,0.0);
}
