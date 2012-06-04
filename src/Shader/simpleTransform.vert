#version 150
uniform mat4 transform = mat4(1.0);

void main()
{
	
	vec4 vertex = transform*gl_Vertex;
	vec3 vVertex = vec3(gl_ModelViewMatrix * vec4(vertex.xyz,1.0));
	gl_Position    = gl_ModelViewProjectionMatrix * vec4(vertex.xyz,1.0);


}
