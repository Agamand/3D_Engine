#version 150
#define MAX_BONE 10
#define MAX_LINK 4
#define CHECK(x) ( (x) > MAX_LINK ? MAX_LINK : x ) 

struct AfterBone
{
	vec4 vertex;
	vec3 normal;
};


uniform bool boneSkinning = false;
uniform mat4 bone[MAX_BONE];
uniform mat4 inverse_bone[MAX_BONE];
uniform mat4 transform = mat4(1.0);
uniform int uselight, usetexture;
in vec4 weight;
in vec4 bone_indices;

out vec3 normal, vVertex;
out int _uselight, _usetexture;

out VertexNormal
{
	vec3 normal;
	vec3 pos;
} VertexNormal;


AfterBone linkMesh(vec4 vertex, vec3 normal)
{
	float sumWeight = 0;
	AfterBone b;
	b.vertex = vertex;
	b.normal = normal;
	mat4 transfo = mat4(0);
	int _max = MAX_LINK;//::CHECK(n_link);
	
	for(int i = 0; i < _max; i++)
	{
		if(weight[i] == -1)
			continue;
		sumWeight += weight[i];
	}
	
	for(int i = 0; i < _max; i++)
	{	
		if(weight[i] == -1)
			continue;
		transfo += bone[int(bone_indices[i])]*inverse_bone[int(bone_indices[i])]/sumWeight*weight[i];
	}
	if(transfo == mat4(0))
		return b;
	b.vertex = transfo*vertex;
	b.normal = normalize((transfo*vec4(normal,0)).xyz);
	return b;
}

void main()
{
	
	vec4 vertex = transform*gl_Vertex;
	vec3 _normal = (transform*vec4(gl_Normal.xyz,0)).xyz;
	if(boneSkinning)
	{
		AfterBone b = linkMesh(vertex,_normal);
		vertex = b.vertex;
		_normal = b.normal;
	}
	normal = gl_NormalMatrix*_normal;
	 
	vVertex = vec3(gl_ModelViewMatrix * vec4(vertex.xyz,1.0));

	VertexNormal.pos = vVertex.xyz;
	VertexNormal.normal = normal;
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Position    = gl_ModelViewProjectionMatrix * vec4(vertex.xyz,1.0);
	_uselight = uselight;
	_usetexture = usetexture;

}
