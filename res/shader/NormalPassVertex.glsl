
out VS_OUT {
    vec3 normal;
} vs_out;

void main(){
   vs_out.normal = mat3(NNY_MVMat) * normal; 
   gl_Position = NNY_MVPMat * vec4(position,0);
}
