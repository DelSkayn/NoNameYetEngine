layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textureCoords;

uniform mat4 uni_MVPMat;
uniform mat4 uni_MVMat;
uniform mat4 uni_PMat;

uniform sampler2D tex_Diffuse;
uniform sampler2D tex_Normal;

uniform float uni_reflectance 1.0;
uniform float uni_roughness 0.5;

uniform vec3 uni_specColor = vec3(1.0,1.0,1.0);

