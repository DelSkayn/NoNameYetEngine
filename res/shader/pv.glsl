
uniform vec3 Ligpos = vec3(10,10.0,10.0);

layout (location = 10) in uint drawid;

layout(std430, binding=0) buffer NNY_mmat{
    mat4 NNY_MMat[];
};

out VS_OUT{
	vec3 N;
	vec3 L;
	vec3 V;
	vec3 color;
        vec2 texturePos;
} vs_out;

void main()
{
    float angle = float(drawid) / 30.0;
    float x = cos(angle) *10;
    float y = sin(angle) *10;
    mat4 t_mat = mat4(
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        x,y,0,1
    ); 
    mat4 NNY_MVMat = NNY_VMat * t_mat;// * NNY_MMat[drawid];
	vec4 P = NNY_MVMat * vec4(position,1.0);
	vs_out.N = mat3(NNY_MVMat) * normal;
    vs_out.L = (NNY_MVMat * vec4(Ligpos,1.0) - P).xyz;
	vs_out.V = P.xyz * -1;
	vs_out.color = normalize(position) /9 ;
    vs_out.texturePos = position.xy;

    gl_Position = NNY_PMat * P;
}
