#pragma once
#include "main.h"
#include "renderer.h"
#include "game_object.h"
#include "texture.h"
#include "shader.h"
#include "manager.h"
#include "Camera.h"

class CScene;
class CField : public CGameObject
{
private:

	ID3D11Buffer*	m_VertexBuffer = NULL;
	CShader*		m_Shader;
	float Rot_Speed = 0.2f;
	CTexture*		m_Texture;
	bool inputValue;
public:
	CField();
	~CField();

	void Init();
	void Uninit();
	void Update();
	void Draw();
	bool CheckInput();
};