//======================================================================
//
// FBX���f���Ǘ�[fbxManager.h]
//
//======================================================================
#ifndef FBXMANAGER_H_
#define FBXMANAGER_H_

//**********************************************************************
// �O���錾
//**********************************************************************
//class CFBX;

#include "fbx.h"
#include <map>
#include <string>

//**********************************************************************
// FBX�Ǘ��N���X
//**********************************************************************
class CShader;
class CFBxManager
{
public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	CFBxManager();
	~CFBxManager();

	// FBX�̃��[�h
	void Load(const char* FileName);

	// ���f���̎擾
	MODEL_* GetModel(const char* FineName);

	// ���f���̕`��
	void Draw(XMMATRIX* pWorld, const char* FileName);

private:
	// �ϐ�
	std::map<std::string, MODEL_> m_Models;	// ���f���̃t�@�C���p�X�ƃ��f���̃|�C���^
	CShader* m_Shader;
};

#endif // !FBXMANAGER_H_
