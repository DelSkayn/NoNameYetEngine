
in VS_OUT{
    vec3 normal;
} fs_in;

//TODO add normal texture
out vec3 normal;
void main(){
   normal = fs_in.normal; 
}
