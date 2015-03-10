#version 330

uniform sampler2D NNY_Tex_Diffuse0;
uniform sampler2D NNY_Tex_Normal;

uniform float NNY_Reflectance = 1.0;
uniform float NNY_Roughness = 0.5;

uniform vec3 NNY_LightColor;
uniform float NNY_LightIntensity;
uniform vec3 NNY_LightDirection;
uniform vec3 NNY_LightPosition;
uniform float NNY_LightAngle;

