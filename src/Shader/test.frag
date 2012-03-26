
#version 140
uniform float time;
in float color;

void main()
{
    if(color >= 0)
		gl_FragColor = vec4(color,1.0-color,0.0,1.0);
	else if(color < 0)
		gl_FragColor = vec4(0.0,1.0+color,-color,1.0);
}
