
#define M_PI 3.1415926535897932384626433832795

vec3 calcSpecular(in vec3 N,in vec3 V,in vec3 L,in vec3 H,in float roughness,in vec3 specColor){

    float alpha = NNY_Roughness * NNY_Roughness;
    float alpha2 = alpha * alpha;
    float NdotH = clamp(dot(N,H),0.0,1.0);
    float VdotH = clamp(dot(V,H),0.0,1.0);
    float NdotL = clamp(dot(N,L),0.0,1.0);

    //Freshnell
    vec3 f0 = NNY_specColor;
    vec3 F = f0 + (1 - f0) * pow(1-VdotH,5);

    term = NdotH * NdotH * (alpha2 -1) +1;
    float D = alpha2 / (M_PI * (term * term));

    //temp G term
    float k = alpha /2;
    float G1 = NdotV / (NdotV * (1.0 -k) + k);
    float G2 = NdotL / (NdotV * (1.0 -k) + k);
    float G = clamp(G1*G2,0.0,1.0));
    
    vec3 specular = (D* F * G) / 4 * NdotL*NdotV;
}
