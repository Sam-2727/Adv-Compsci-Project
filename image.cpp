vec4 returnField (vec2 uv) {return texture(iChannel0,uv/iResolution.xy);}
void mainImage( out vec4 C, in vec2 U )
{

    C.xyz=vec3(returnField(U).x*10.,returnField(U).y*10.,returnField(U).w);
    
    
}
