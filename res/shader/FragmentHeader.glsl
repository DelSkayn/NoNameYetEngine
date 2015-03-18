#version 330

uniform sampler2D NNY_Tex_Diffuse0;
uniform sampler2D NNY_Tex_Normal;

<<<<<<< HEAD
uniform float NNY_Reflectance = 1.0;
uniform float NNY_Roughness = 0.50;
=======
uniform float NNY_Reflectance = 0.2;
uniform float NNY_Roughness = 0.80;
>>>>>>> c3442bab1e57292fc1538c0375d86e917d800214

uniform vec3 NNY_LightColor;
uniform float NNY_LightIntensity;
uniform vec3 NNY_LightDirection;
uniform vec3 NNY_LightPosition;
uniform float NNY_LightAngle;

