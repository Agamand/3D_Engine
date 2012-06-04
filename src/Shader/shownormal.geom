#version 150
#extension GL_EXT_geometry_shader4 : enable
layout (triangles) in;
layout (line_strip, max_vertices = 2) out;

in VertexNormal
{
	vec3 normal;
	vec3 pos;
} VertexNormal[];


void drawLine( vec4 color, vec3 from, vec3 to )
{
	gl_FrontColor = color;
	gl_Position = gl_ProjectionMatrix * vec4( from, 1.0 );
	EmitVertex();

	gl_FrontColor = color;
	gl_Position = gl_ProjectionMatrix * vec4( to, 1.0 );
	EmitVertex();

	EndPrimitive();
}

void main( void )
{
	for( int i = 0 ; i < gl_VerticesIn ; i++ )
	{
		drawLine(vec4(1,0,0,1),VertexNormal[i].pos, VertexNormal[i].pos + VertexNormal[i].normal);
	}
	EndPrimitive ();
}
