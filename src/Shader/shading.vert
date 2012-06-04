// simple vertex shader
#version 130

out vec3 normal,lightVec,viewVec;
out vec4 tex_coord;

void main()
{
	// on travaille dans le repère de la caméra (car on ne peut pas récupérer les vertex dans le repère monde)
	// donc on passe toutes les coordonnées ds le repère de la cam
	// (sauf gl_LightSource[0].position qui est entrée dans le repère de la cam)
	normal=gl_NormalMatrix*gl_Normal;
	viewVec=-(gl_ModelViewMatrix*gl_Vertex).xyz;
	lightVec=(gl_LightSource[0].position).xyz+viewVec;	
		
	gl_Position=ftransform();
	tex_coord=gl_MultiTexCoord0 ;
	gl_FrontColor = gl_Color;	
} 