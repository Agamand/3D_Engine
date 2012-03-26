
#version 140
uniform float time;
out float color;
float dist(vec4 pos)
{
	float r = pos.x*pos.x+pos.y*pos.y+pos.z*pos.z;
    return sqrt(r);
}
float onde(float t, float p)
{
    float f = 2.0;
	return 0.2*exp(-t*2.0)*sin(3.14159*2.0*f*t-p*20);
}
void main()
{
    float coef = dist(gl_Vertex);
    float signe = gl_Vertex.x == 0.0 ? 0.0 : abs(gl_Vertex.x)/gl_Vertex.x;

	gl_Position    = gl_ModelViewProjectionMatrix * gl_Vertex; //vec4(gl_Vertex.xy,gl_Vertex.z+onde(coef,time),1.0);
	gl_FrontColor  = vec4(1.0,0.0,1.0,1.0);
	gl_TexCoord[0] = gl_MultiTexCoord0;
    color = 5*onde(coef,time);
}



