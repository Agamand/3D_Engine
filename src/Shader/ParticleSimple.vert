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

uniform vec3 v2;
uniform float time;
uniform float repeat;
uniform vec3 v0;

const float g = -9.80665;

out vec4 Color;

void main(void)
{	
	vec4 vertex = gl_Vertex;
		
	float t = max(time, 0.0);
	t = t - repeat * floor(t * (1.0 / repeat));
	
	vertex += vec4(v0.xyz*t,0.0)+ vec4(v2.xyz*t*t*0.5,0.0);

	Color = gl_Color;
	Color = vec4(Color.xyz,1.0-t/repeat);
	gl_Position = gl_ModelViewProjectionMatrix * vertex;
}
