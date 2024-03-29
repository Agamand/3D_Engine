//
// bumpmap.vert: Vertex shader for bump mapping in surface local coordinates
//
// Author: Randi Rost
//
// Copyright (c) 2002-2006 3Dlabs Inc. Ltd.
//
// See 3Dlabs-License.txt for license information
//
#version 130

out vec3 lightDir; 	  // interpolated surface local coordinate light direction 
out vec3 viewDir;     // interpolated surface local coordinate view direction
out vec4 tex_c;

attribute vec3 Tangent;
attribute vec3 Binormal;



void main(void)
{
    vec3 b;
    vec3 n;
    vec3 t;
    vec3 pos;
    vec3 lightVec;
    vec3 r;
    vec3 v;
	vec3 LightPosition = gl_LightSource[0].position.xyz;

    // Do standard vertex stuff
    gl_Position  = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_TexCoord[0] = gl_MultiTexCoord0;

    // Transform the input vectors
    t = normalize(gl_NormalMatrix * Tangent);
    b = normalize(gl_NormalMatrix * Binormal);
    n = normalize(gl_NormalMatrix * gl_Normal);

    // Transform light position into surface local coordinates
    v.x = dot(LightPosition, t);
    v.y = dot(LightPosition, b);
    v.z = dot(LightPosition, n);
    lightDir = normalize(v);

    pos = vec3(gl_ModelViewMatrix * gl_Vertex);
    v.x = dot(pos, t);
    v.y = dot(pos, b);
    v.z = dot(pos, n);
    viewDir = normalize(v);
}
