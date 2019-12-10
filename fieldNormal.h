#pragma once
#include "game_object.h"

class CScene;
class CShaderNormal;
class CFieldNormal : public CGameObject
{
private:

	ID3D11Buffer*	m_VertexBuffer = NULL;
	CShaderNormal*		m_Shader;
	float Rot_Speed = 0.2f;
	CTexture*		m_Texture[2];
	bool inputValue;
public:

	void Init();
	void Uninit();
	void Update();
	void Draw();
	bool CheckInput();
};