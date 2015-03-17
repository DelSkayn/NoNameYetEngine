#version 430

uniform sampler2D NNY_Tex_Diffuse0;
uniform sampler2D NNY_Tex_Normal;

uniform float NNY_Reflectance = 0.2;
uniform float NNY_Roughness = 0.80;

uniform vec3 NNY_LightColor;
uniform float NNY_LightIntensity;
uniform vec3 NNY_LightDirection;
uniform vec3 NNY_LightPosition;
uniform float NNY_LightAngle;

