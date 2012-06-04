// simple fragment shader

// 'time' contains seconds since the program was linked.
#version 130
in vec3 normal,lightVec,viewVec;
in vec4 tex_coord;
uniform sampler2D texture;

void main()
{
	//vec4 texel=texture2D (texture,tex_coord.st);
	vec4 color = gl_Color;	
	
	vec3 N=normalize(normal);
	vec3 L=normalize(lightVec);		
	vec3 V=normalize(viewVec);	
	vec3 R=normalize(2.0*dot(N,V)*N-V);

	float LdotN=dot(L,N);
	float LdotR=dot(L,R);
	color=vec4(0,0,1,1);

	if(abs(LdotN)<0.40)//0.19
		color=vec4(0,0,0,1);//0.5
	//else if(LdotN<0.8)//0.31
		//color*=0.2;//0.75
	
	// speculaire
	if(LdotN>0.90)
		color=vec4(1);	
		
	if(color.r>1.0) color.r=1.0;
	if(color.g>1.0) color.g=1.0;
	if(color.b>1.0) color.b=1.0;
	//color += texel;
	normalize(color);
	gl_FragColor=color;
} 