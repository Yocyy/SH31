#pragma once

#include "game_object.h"

class CScene;
class CShader;

class CField : public CGameObject
{
private:

	ID3D11Buffer*	m_VertexBuffer = NULL;
	CShader*		m_Shader;
	float Rot_Speed = 0.2f;
	CTexture*		m_Texture;
	bool inputValue;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	bool CheckInput();
};