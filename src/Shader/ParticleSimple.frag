// simple fragment shader

// 'time' contains seconds since the program was linked.

#version 140
uniform float time;

in vec4 Color;

void main()
{
	gl_FragColor = Color;
}
