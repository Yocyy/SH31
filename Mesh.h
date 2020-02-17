#pragma once
#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

class CShader;

struct Vertex {
	XMFLOAT3 Position;
	XMFLOAT3 Normal;
	XMFLOAT2 TexCoords;
};

struct Texture {
	unsigned int id;
	std::string type;
};

class Mesh
{
private:
	CShader* m_Shader;
	/*  Render data  */
	ID3D11Buffer* m_VertexBuffer;
	ID3D11Buffer* m_IndexBuffer;
	unsigned int m_IndexNum;
	//デフォルトコンストラクタの禁止
	Mesh();
	/*  Functions    */
	void setupMesh();
public:
	/* Mesh Data */
	std::vector<Vertex> vertices;
	std::vector<DWORD> indices;
	std::vector<Texture> textures;
	/* Functions */
	Mesh(std::vector<Vertex> vertices, std::vector<DWORD> indices, std::vector<Texture> textures);
	void Draw();
};