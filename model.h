#pragma once
#include <string>
#include <vector>
//#include <assimp/Importer.hpp>
#include <assimp/cimport.h>    
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//#include <assimp/cimport.h>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
//#include <assimp/matrix4x4.h>
#include <map>

struct MESH
{
	ID3D11Buffer* m_VertexBuffer;
	ID3D11Buffer* m_IndexBuffer;
	unsigned int m_IndexNum;
};

class CModel
{
private:
	MESH* m_Mesh;
	unsigned int m_MeshNum;
	const aiScene* m_Scene;
	std::map<std::string, aiQuaternion> m_NodeRotation;
	std::map<std::string, aiVector3D>   m_NodePosition;

public:
	void Draw(XMMATRIX matrix);
	void DrawMesh(aiNode* node, XMMATRIX Matrix);
	void Load(const char* FileName);
	void Unload();
	void Update(int Animation,int Frame);
};