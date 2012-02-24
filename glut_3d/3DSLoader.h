
/*#ifndef 3DSLOADER_H
#define 3DSLOADER_H

#include "Util\List.h"
#include "Camera\Vector.h"


//>------ Primary Chunk, at the beginning of each file
#define __H3DS__PRIMARY       0x4D4D

//>------ Main Chunks
#define __H3DS__OBJECTINFO    0x3D3D                // This gives the version of the mesh and is found right before the material and object information
#define __H3DS__VERSION3DS    0x0002                // This gives the version of the .3ds file
#define __H3DS__EDITKEYFRAME  0xB000                // This is the header forall of the key frame info

//>------ sub defines of OBJECTINFO
#define __H3DS__MATERIAL      0xAFFF                // This stored the texture info
#define __H3DS__OBJECT        0x4000                // This stores the faces, vertices, etc...

//>------ sub defines of MATERIAL
#define __H3DS__MATNAME       0xA000                // This holds the material name
#define __H3DS__MATDIFFUSE    0xA020                // This holds the color of the object/material
#define __H3DS__MATMAP        0xA200                // This is a header fora new material
#define __H3DS__MATMAPFILE    0xA300                // This holds the file name of the texture

#define __H3DS__OBJECT_MESH   0x4100                // This lets us know that we are reading a new object

//>------ sub defines of OBJECT_MESH
#define __H3DS__OBJECT_VERTICES     0x4110          // The objects vertices
#define __H3DS__OBJECT_FACES        0x4120          // The objects faces
#define __H3DS__OBJECT_MATERIAL     0x4130          // This is found if the object has a material, either texture map or color
#define __H3DS__OBJECT_UV           0x4140          // The UV texture coordinates


// Here is our structure for our 3DS indicies (since .3DS stores 4 unsigned shorts)
struct tIndices {
    unsigned short a, b, c, bVisible;       // This will hold point1, 2, and 3 index's into the vertex array plus a visible flag
};

// This holds the chunk info
struct tChunk {
    unsigned short int ID;                  // The chunk's ID       
    unsigned int length;                    // The length of the chunk
    unsigned int bytesRead;                 // The amount of bytes read within that chunk
};

// This is our face structure.  This is is used forindexing into the vertex 
// and texture coordinate arrays.  From this information we know which vertices
// from our vertex array go to which face, along with the correct texture coordinates.
struct tFace {
    int vertIndex[3];           // indicies forthe verts that make up this triangle
    int coordIndex[3];          // indicies forthe tex coords to texture this face
};

// This holds the information fora material.  It may be a texture map of a color.
// Some of these are not used, but I left them because you will want to eventually
// read in the UV tile ratio and the UV tile offset forsome models.
struct tMaterialInfo {
    char  strName[255];         // The texture name
    char  strFile[255];         // The texture file name (If this is set it's a texture map)
    unsigned char  color[3];             // The color of the object (R, G, B)
    unsigned int   texureId;             // the texture ID
    float uTile;                // u tiling of texture  (Currently not used)
    float vTile;                // v tiling of texture  (Currently not used)
    float uOffset;              // u offset of texture  (Currently not used)
    float vOffset;              // v offset of texture  (Currently not used)
} ;

// This holds all the information forour model/scene. 
// You should eventually turn into a robust class that 
// has loading/drawing/querying functions like:
// LoadModel(...); DrawObject(...); DrawModel(...); DestroyModel(...);
struct t3DObject {
    int  numOfVerts;            // The number of verts in the model
    int  numOfFaces;            // The number of faces in the model
    int  numTexVertex;          // The number of texture coordinates
    int  materialID;            // The texture ID to use, which is the index into our texture array
    bool bHasTexture;           // This is true if there is a texture map forthis object
    char strName[255];          // The name of the object
	Vector3D  *pVerts;          // The object's vertices
    Vector3D  *pNormals;        // The object's normals
    Vector3D  *pTexVerts;       // The texture's UV coordinates
    tFace *pFaces;              // The faces information of the object
};

// This holds our model information.  This should also turn into a robust class.
// We use STL's (Standard Template Library) vector class to ease our link list burdens. :)
struct t3DModel {
    int numOfObjects;                   // The number of objects in the model
    int numOfMaterials;                 // The number of materials forthe model
    ListCh* pMaterials;   // The list of material information (Textures and colors)
	ListCh* pObject;          // The object list forour model
};

    int Import3DS(t3DModel *pModel, const char *strFileName);

    // This reads the next chunk
    void ReadChunk(tChunk *);

    // This reads the next large chunk
    void ProcessNextChunk(t3DModel *pModel, tChunk *);

    // This reads the object chunks
    void ProcessNextObjectChunk(t3DModel *pModel, t3DObject *pObject, tChunk *);

    // This reads the material chunks
    void ProcessNextMaterialChunk(t3DModel *pModel, tChunk *);

    // This reads the RGB value forthe object's color
    void ReadColorChunk(tMaterialInfo *pMaterial, tChunk *pChunk);

    // This reads the objects vertices
    void ReadVertices(t3DObject *pObject, tChunk *);

    // This reads the objects face information
    void ReadVertexIndices(t3DObject *pObject, tChunk *);

    // This reads the texture coodinates of the object
    void ReadUVCoordinates(t3DObject *pObject, tChunk *);

    // This reads in the material name assigned to the object and sets the materialID
    void ReadObjectMaterial(t3DModel *pModel, t3DObject *pObject, tChunk *pPreviousChunk);
    
    // This computes the vertex normals forthe object (used forlighting)
    void ComputeNormals(t3DModel *pModel);

    // This frees memory and closes the file
    void CleanUp();
    
    // The file pointer
    FILE *m_FilePointer;
    
    // These are used through the loading process to hold the chunk information
    tChunk *m_CurrentChunk;
    tChunk *m_TempChunk;

#endif 
*/