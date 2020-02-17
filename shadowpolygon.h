#pragma once

#include "game_object.h"

class CShader;
class CShadowPolygon : public CGameObject
{
private:

	ID3D11Buffer*	m_VertexBuffer = NULL;
	CShader*		m_Shader;
	float size_x, size_y;
public:
	CShadowPolygon()
		:size_x(SCREEN_WIDTH/4)
		, size_y(SCREEN_HEIGHT/4) {}
	void Init();
	void Uninit();
	void Update();
	void Draw();

};