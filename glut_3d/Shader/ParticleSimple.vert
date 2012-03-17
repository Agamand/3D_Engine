//
// Vertex shader for a particle fountain.
//
// Author: Philip Rideout
//
// Copyright (c) 2002-2006 3Dlabs Inc. Ltd.
//
// See 3Dlabs-License.txt for license information
//
#version 140
 
uniform float time;
uniform float repeat;
uniform vec3 v0;
const float g = -9.80665;

out vec4 Color;

void main(void)
{	
	vec4 vertex = gl_Vertex;
		
	float t = max(time - gl_Color.a, 0.0);
	t = t - repeat * floor(t * (1.0 / repeat));
	
	vertex += vec4(v0.xy*t,0.5*g*t*t+v0.z*t,0.0);

	Color = vec4(1.0-v0.x/2.0,gl_Color.gb, 1.0 - t);
	gl_Position = gl_ModelViewProjectionMatrix * vertex;
}
