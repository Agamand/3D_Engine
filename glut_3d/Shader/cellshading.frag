



uniform sampler2D Texture0;
uniform vec3 LightDir;
varying vec3 Normal;

void main (void)
{

vec4 color = texture2D( Texture0 , vec2( gl_TexCoord[0] ) );
color = CelShading ( color );
gl_FragColor = color;
}

vec4 CelShading ( vec4 color )
{
float Intensity = dot( LightDir , normalize(Normal) );

float factor = Intensity;

color *= vec4 ( factor, factor, factor, 1.0 );

return color;
}