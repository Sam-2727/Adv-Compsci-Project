#define dt 0.15
//radius
#define r

//user-defined per


Vec2 advect(sampler2D prevField, vec2 uv, vec4 curMouse, vec4 prevMouse){
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

double vorticity (sampler2D velocityField, vec2 pos, vec2 stepSize) {
  //returns double vorticity at point
  //Technically vorticity is a 3d vector, but in this 2d setting it will
  //Always be (0, 0, z) for some z, so we just use that z

  //dFy_dx is (dF_y)/(dx) [i.e. an approximation of it]
  double dFy_dx = (textureLod(velocityField, pos + vec2(stepSize.x, 0.), 0.).y -
        textureLod(velocityField, pos + vec2(stepSize.x, 0.), 0.).y) /
      (2*stepSize.x)

  //Similar for dFx_dy
  double dFx_dy = (textureLod(velocityField, pos + vec2(0, stepSize.y), 0.).x -
        textureLod(velocityField, pos + vec2(0, stepSize.y), 0.).x) /
      (2*stepSize.y)

  //Return vorticity
  return dFy_dx - dFx_dy;
}

//Calculates vorticity everywhere and puts it into a 2d array (not really?)
//Trying to use arrays with samplers with fail horribly. We need to revamp
//our architecture or scrap this and use an array for velocities too.

//ALSO BE CAREFUL OF MEMORY LEAK
double** vorticity_everywhere(sampler2D velocityField, vec2 stepSize) {
  int xsize = floor(1 / stepSize.x);
  int ysize = floor(1 / stepSize.y);

  double** vortField = new double*[xsize];

  for (int i = 0; i < xsize; i++) {
    vortField[i] = new double[ysize];

    for (int j = 0; j < ysize; j++) {
      vortField[i][j] = vorticity(velocityField, vec2(i * stepSize.x, j * stepSize.y), stepSize);
    }
  }

  return vortField;
}


vec2 vorticityConfinement (sampler2D velocityField, vec2 vorticity, vec2 spacing, vec2 pos){
  //returns vec2 corrective force from "vorticity confinement"
}
