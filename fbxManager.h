//======================================================================
//
// FBXモデル管理[fbxManager.h]
//
//======================================================================
#ifndef FBXMANAGER_H_
#define FBXMANAGER_H_

//**********************************************************************
// 前方宣言
//**********************************************************************
//class CFBX;

#include "fbx.h"
#include <map>
#include <string>

//**********************************************************************
// FBX管理クラス
//**********************************************************************
class CShader;
class CFBxManager
{
public:
	// コンストラクタとデストラクタ
	CFBxManager();
	~CFBxManager();

	// FBXのロード
	void Load(const char* FileName);

	// モデルの取得
	MODEL_* GetModel(const char* FineName);

	// モデルの描画
	void Draw(XMMATRIX* pWorld, const char* FileName);

private:
	// 変数
	std::map<std::string, MODEL_> m_Models;	// モデルのファイルパスとモデルのポインタ
	CShader* m_Shader;
};

#endif // !FBXMANAGER_H_
