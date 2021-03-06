#define dt 0.15
//radius
#define r
vec2 advect(sampler2D prevField, vec2 uv, vec4 curMouse, vec4 prevMouse){
    //eq 13
    vec2 uCur = textureLod(prevField,uv,0.).xyz;
    vec2 posPrev = uv - dt*uCur;
    return textureLod(prevField,posPrev,0.);
    
}
//rBeta is the reciprocal of beta
vec2 jacobi(sampler2D field,int alpha,int rbeta,int b,vec2 stepSize){
    vec4 fr = textureLod(field, uv + vec2(stepSize.x, 0.), 0.);
    vec4 fl = textureLod(field, uv - vec2(stepSize.x, 0.), 0.);
    vec4 ft = textureLod(field, uv + vec2(0., stepSize.y), 0.);
    vec4 fd = textureLod(field, uv - vec2(0., stepSize.y), 0.);
    vec4 center = textureLod(field, uv, 0.);
    return (fr+fl.xyz+ft.xyz+fd.xyz+alpha*center)*rBeta;
}
vec2 addForce(sampler2D field, vec2 uv, vec2 posForce){
    vec3 uCur = textureLod(field,uv,0.).xyz;
    return uCur + exp(distance(posForce,uCur)/r);
    
    
}
vec2 divergence(sampler2D field, vec2 uv,vec2 stepSize){

}
vec2 solvePoissonPressure(sampler2D field, vec2 uv){
    //calculate jacobian of pressure 
    //jacobi method (30 iterations)
    //take result and subtract gradient of w
    //return that result
}
