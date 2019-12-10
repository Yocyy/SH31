#pragma once

#include "game_object.h"

class CShader;
class CPolygon : public CGameObject
{
private:

	ID3D11Buffer*	m_VertexBuffer = NULL;
	CShader*		m_Shader;

	CTexture*		m_Texture[2];

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};