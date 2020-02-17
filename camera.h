#pragma once

#include "game_object.h"

class CShader;
class CCamera : public CGameObject
{
	XMMATRIX	m_ViewMatrix;
	XMMATRIX	m_InvViewMatrix;
	XMMATRIX	m_ProjectionMatrix;

	bool inputValid;
	RECT m_Viewport;
	XMFLOAT3	m_Front, m_Right, m_Up;
	float Move_Speed;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool CheckInput();
	XMMATRIX& GetViewMatrix();
	XMMATRIX& GetProjectionMatrix();
	XMFLOAT4  GetCameraPosition4f();
};