//
// bumpmap.frag: Fragment shader for bump mapping in surface local coordinates
//
// Author: Randi Rost
//
// Copyright (c) 2002-2006 3Dlabs Inc. Ltd.
//
// See 3Dlabs-License.txt for license information
//
#version 130
uniform sampler2D texture;
uniform sampler2D NormalMap;
uniform float DiffuseFactor;
uniform float SpecularFactor;
//uniform vec3 BaseColor;

in vec3 lightDir;    // interpolated surface local coordinate light direction 
in vec3 viewDir;     // interpolated surface local coordinate view direction
in vec3 tex_c;

void main (void)
{
    vec3 norm;
    vec3 r;
	vec3 BaseColor = texture2D(texture,gl_TexCoord[0].st).xyz;
    vec3 color;
    float intensity;
    float spec;
    float d;

    // Fetch normal from normal map
    norm = vec3(texture2D(NormalMap, vec2(gl_TexCoord[0])));
    norm = (norm - 0.5) * 2.0;
    norm.y = -norm.y;
    intensity = max(dot(lightDir, norm), 0.0) * DiffuseFactor;

    // Compute specular reflection component
    d = 2.0 * dot(lightDir, norm);
    r = d * norm;
    r = lightDir - r;
    spec = pow(max(dot(r, viewDir), 0.0) , 6.0) * SpecularFactor;
    intensity += min(spec, 1.0);

     // Compute color value
    color = clamp(BaseColor * intensity, 0.0, 1.0);
 
    // Write out final fragment color
	
    gl_FragColor = vec4(color, 1.0);
}
