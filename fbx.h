//======================================================================
//
// FBX�ǂݍ���[fbx.h]
//
//======================================================================
#ifndef FBX_H_
#define FBX_H_

//**********************************************************************
// �C���N���[�h�w�b�_�[
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
// FBX�N���X
//**********************************************************************
class CFBX
{
public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	CFBX();
	~CFBX();

	// FBX�̓ǂݍ���
	MODEL_ Load(const char* FileName);

private:
	// ���b�V�����擾
	void GetMesh(FbxNode* pNode);

	// ���b�V���f�[�^�̎擾
	HRESULT GetMeshData(FbxNode* pNode, MODEL_& model);

	// ���_���W�̎擾
	void GetPosition(FbxMesh* pMesh);

	// ���b�V���ɓ����Ă�}�e���A�����X�g�̎擾
	void GetMeshMaterialList(FbxMesh* pMesh);

	// �{�[���̎擾
	void GetBone(FbxMesh* pMesh);

	// �@���̎擾
	void GetVertexNormal(FbxMesh* pMesh);

	// �^���W�F���g�̎擾
	void GetVertexTangent(FbxMesh* pMesh);

	// �e�N�X�`�����W�̎擾
	void GetVertexUV(FbxMesh* pMesh);

	// �e�N�X�`��
	void GetTextureNames(FbxMesh* pMesh, const char* materialType, std::string& get);				// �e�N�X�`��

	// ���_�F�擾
	void GetVertexColor(FbxMesh* pMesh);
	
	// 
	HRESULT CreateModelData(MODEL_& model);

	// 
	HRESULT CreateVeretx(MODEL_& model, int indexNum, const int* index, UVSet uv, std::vector<UVSet>& uvset);

	// 
	void CreateMtx(XMMATRIX& mtx, const FbxMatrix fbxMtx);

	// �ꎞ���̉��
	void ReleaseTempObj();

	// �ꎞ���̉��
	void ReleaseTempAnimObj();


	// �ϐ�
	std::string			m_FileName;						// �t�@�C����
	int					m_PointCount;					// ���_��
	int					m_PolygonCount;					// �|���S����
	int					m_IndexCount;					// �C���f�b�N�X��
	std::vector<int>	m_MeshMaterialList;				// ���b�V���}�e���A�����X�g
	int					m_MaterialCount[2] = { 0, 0 };	// �}�e���A���̐�(0 = CountMesh, 1 = GetMesh)

	std::vector<VERTEXPOINTBONE>	m_TempPoint;	// ���_
	std::vector<VERTEXPOINTBONE>	m_TempVertex;	// ���_
	std::vector<XMFLOAT3>			m_TempNormal;	// �@��
	std::vector<XMFLOAT3>			m_TempTangent;	// �^���W�F���g
	std::vector<FBXUV>				m_TempTexcoord;	// UV
	std::vector<UVSet>				m_TempUVSet;	// UV�Z�b�g(?)
	std::vector<COLOR>				m_TempColor;	// ���_�F
	std::vector<FBXANIMATION>		m_TempAnim;		// �A�j��(?)

	std::vector<BONE>				m_BoneList;

	std::vector<FbxNode*>			m_TempNode;
	std::string						m_TempName;
};

#endif // !FBX_H_
