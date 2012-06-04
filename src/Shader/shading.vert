// simple vertex shader
#version 130

out vec3 normal,lightVec,viewVec;
out vec4 tex_coord;

void main()
{
	// on travaille dans le rep�re de la cam�ra (car on ne peut pas r�cup�rer les vertex dans le rep�re monde)
	// donc on passe toutes les coordonn�es ds le rep�re de la cam
	// (sauf gl_LightSource[0].position qui est entr�e dans le rep�re de la cam)
	normal=gl_NormalMatrix*gl_Normal;
	viewVec=-(gl_ModelViewMatrix*gl_Vertex).xyz;
	lightVec=(gl_LightSource[0].position).xyz+viewVec;	
		
	gl_Position=ftransform();
	tex_coord=gl_MultiTexCoord0 ;
	gl_FrontColor = gl_Color;	
} 