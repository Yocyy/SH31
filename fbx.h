//======================================================================
//
// FBX読み込み[fbx.h]
//
//======================================================================
#ifndef FBX_H_
#define FBX_H_

//**********************************************************************
// インクルードヘッダー
//**********************************************************************
#include "renderer.h"
#include "texture.h"
#include <vector>
#include <fbxsdk.h>
#include <string>

struct BONE
{
	std::string	name;
	XMMATRIX	initMtx;
	std::vector<std::vector<XMMATRIX>>	animMtx;
};

struct FBXANIMATION
{
	std::string			name;
	std::vector<BONE>	bone;
	int					frameNum;
	int					endFrame;
	FbxTime				framePeriod;
};

struct VERTEXFBX
{
	XMFLOAT3	position;
	XMFLOAT3	normal;
	COLOR		color;
	XMFLOAT2	texcoord;
	XMFLOAT3	positionDefault;
};

struct VERTEXBONE
{
	float	boneIndex;
	float	weight;
};

struct VERTEXPOINTBONE
{
	XMFLOAT3	position;
	VERTEXBONE	boneData[4];
};

enum class MaterialType
{
	Diffuse = 0,
	Normal = 1,
	MAX
};

struct UVSet
{
	MaterialType	type;
	std::string		uvSetName;
	std::string		texName;
};

struct FBXUV
{
	std::string				uvSetName;
	std::vector<XMFLOAT2>	texcoord;
};

struct MESH_
{
	int 					pointCount;
	int 					polygonCount;
	int 					indexCount;
	UVSet					uvSet;
	UINT					vertexShader;
	std::vector<VERTEXFBX>	vertex;
	std::vector<BONE>		bone;
};

struct VERTEX
{
	XMFLOAT3	position;
	XMFLOAT3	normal;
	COLOR		color;
	XMFLOAT2	texcoord;
	XMFLOAT3	tangent;
	XMFLOAT4	boneIndex;
	XMFLOAT4	weight;
};

struct MATERIAL_
{
	COLOR		ambient;
	COLOR		diffuse;
	COLOR		specular;
	COLOR		emission;
	float		power;
	UINT		texture[static_cast<int>(MaterialType::MAX)];
	std::string	textureName[static_cast<int>(MaterialType::MAX)];
};

struct BUFFER_ {
	ID3D11Buffer*		vertexBuffer;
	ID3D11Buffer*		indexBuffer;
	int					indexCount;
};

struct MESH
{
	std::string			name;
	XMMATRIX			frameTransMtx;
	std::vector<VERTEX>	vertex;
	std::vector<USHORT>	index;
	BUFFER_				buffer;
	MATERIAL_			material;
	CTexture*			texture;
};

struct MODEL_
{
	XMMATRIX			frameTransMtx;
	std::vector<MESH>	mesh;
	std::vector<BONE>	bone;
};

//**********************************************************************
// FBXクラス
//**********************************************************************
class CFBX
{
public:
	// コンストラクタとデストラクタ
	CFBX();
	~CFBX();

	// FBXの読み込み
	MODEL_ Load(const char* FileName);

private:
	// メッシュを取得
	void GetMesh(FbxNode* pNode);

	// メッシュデータの取得
	HRESULT GetMeshData(FbxNode* pNode, MODEL_& model);

	// 頂点座標の取得
	void GetPosition(FbxMesh* pMesh);

	// メッシュに入ってるマテリアルリストの取得
	void GetMeshMaterialList(FbxMesh* pMesh);

	// ボーンの取得
	void GetBone(FbxMesh* pMesh);

	// 法線の取得
	void GetVertexNormal(FbxMesh* pMesh);

	// タンジェントの取得
	void GetVertexTangent(FbxMesh* pMesh);

	// テクスチャ座標の取得
	void GetVertexUV(FbxMesh* pMesh);

	// テクスチャ
	void GetTextureNames(FbxMesh* pMesh, const char* materialType, std::string& get);				// テクスチャ

	// 頂点色取得
	void GetVertexColor(FbxMesh* pMesh);
	
	// 
	HRESULT CreateModelData(MODEL_& model);

	// 
	HRESULT CreateVeretx(MODEL_& model, int indexNum, const int* index, UVSet uv, std::vector<UVSet>& uvset);

	// 
	void CreateMtx(XMMATRIX& mtx, const FbxMatrix fbxMtx);

	// 一時情報の解放
	void ReleaseTempObj();

	// 一時情報の解放
	void ReleaseTempAnimObj();


	// 変数
	std::string			m_FileName;						// ファイル名
	int					m_PointCount;					// 頂点数
	int					m_PolygonCount;					// ポリゴン数
	int					m_IndexCount;					// インデックス数
	std::vector<int>	m_MeshMaterialList;				// メッシュマテリアルリスト
	int					m_MaterialCount[2] = { 0, 0 };	// マテリアルの数(0 = CountMesh, 1 = GetMesh)

	std::vector<VERTEXPOINTBONE>	m_TempPoint;	// 頂点
	std::vector<VERTEXPOINTBONE>	m_TempVertex;	// 頂点
	std::vector<XMFLOAT3>			m_TempNormal;	// 法線
	std::vector<XMFLOAT3>			m_TempTangent;	// タンジェント
	std::vector<FBXUV>				m_TempTexcoord;	// UV
	std::vector<UVSet>				m_TempUVSet;	// UVセット(?)
	std::vector<COLOR>				m_TempColor;	// 頂点色
	std::vector<FBXANIMATION>		m_TempAnim;		// アニメ(?)

	std::vector<BONE>				m_BoneList;

	std::vector<FbxNode*>			m_TempNode;
	std::string						m_TempName;
};

#endif // !FBX_H_
