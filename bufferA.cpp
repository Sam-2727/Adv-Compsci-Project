vec4 returnField(vec2 uv){
    return texture(iChannel0,uv/iResolution.xy);
}
float constOne = 10.; //change as needed
void mainImage( out vec4 newState, in vec2 prevPos )
{
    
    vec2 upPos = prevPos+vec2(0,1);
    vec2 downPos = prevPos+vec2(0,-1);
    vec2 rightPos = prevPos+vec2(1,0);
    vec2 leftPos = prevPos+vec2(-1,0);
    vec4 prevState = returnField(prevPos);
    vec4 up = returnField(upPos);
    vec4 down = returnField(downPos);
    vec4 right = returnField(rightPos);
    vec4 left = returnField(leftPos);
    
    prevPos -= returnField(prevPos).xy;
    upPos -= up.xy;
    downPos -=down.xy;
    leftPos -=left.xy;
    rightPos -=right.xy;
    

    
    vec4 compressionForce = vec4(length(prevPos-upPos),length(prevPos-downPos)
                            ,length(prevPos-rightPos),length(prevPos-leftPos))-1.0;
    vec2 gradientPressure = vec2(right.z-left.z,up.z-down.z);
    
    //vec4 laplaceField = (down+up+right+left)/4.0;
    prevState = returnField(prevPos);
    up = returnField(upPos);
    down = returnField(downPos);
    right = returnField(rightPos);
    left = returnField(leftPos);
    newState = prevState;
    //newState.z = mix( //blending for continuity
    newState.xy -= gradientPressure/constOne;
    newState.z += (compressionForce.x+compressionForce.y+compressionForce.z+compressionForce.w)/10.;
    if(iFrame<1){
       newState = vec4(0.0);
    }
    //if(mouse.w>0&&length(
    if (iFrame < 14 && length(prevPos-0.5*iResolution.xy) < 20.){
        newState.xyw = vec3(0,.1,1);
    }
    
    
    if(prevPos.x<1.0||prevPos.y<1.0||iResolution.x-prevPos.x<1.0||iResolution.y-prevPos.x<1.0){
            newState.xyw*=0.;
        
    }
    
    
    
    
    
    
    
    
    
}
