
#pragma once
#include "main.h"
#include "renderer.h"
#include "game_object.h"
class CShader;
class CCamera : public CGameObject
{
	// XMFLOAT3					m_Position;
	XMFLOAT3					m_Rotation;
	XMMATRIX	m_ViewMatrix;
	XMMATRIX	m_InvViewMatrix;
	XMMATRIX	m_ProjectionMatrix;

	bool inputValid;
	RECT m_Viewport;
	XMFLOAT3	m_Front, m_Right, m_Up;
	float Move_Speed;
	CShader* m_Shader;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool CheckInput();
	XMMATRIX& GetViewMatrix();

};