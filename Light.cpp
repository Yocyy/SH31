#include "main.h"
#include "renderer.h"
#include "game_object.h"
#include "input.h"
#include "shader.h"
#include "light.h"


void CLight::Init()
{
	m_Position = XMFLOAT3(0.0f, 20.0f,0.0f);
	m_Rotation = XMFLOAT3(1.0f, 0.0f, 0.0f);
	m_Front = XMFLOAT3(0.0f, 0.0f,1.0f);
	m_Right = XMFLOAT3(0.0f, 1.0f,0.0f);
	m_Up	= XMFLOAT3(1.0f, 0.0f,0.0f);
	Move_Speed = 1.0f;

	m_Viewport.left = 0;
	m_Viewport.top = 0;
	m_Viewport.right = SCREEN_WIDTH;
	m_Viewport.bottom = SCREEN_HEIGHT;


	// ビューポート設定
	D3D11_VIEWPORT dxViewport;
	dxViewport.Width = (float)(m_Viewport.right - m_Viewport.left);
	dxViewport.Height = (float)(m_Viewport.bottom - m_Viewport.top);
	dxViewport.MinDepth = 0.0f;
	dxViewport.MaxDepth = 1.0f;
	dxViewport.TopLeftX = (float)m_Viewport.left;
	dxViewport.TopLeftY = (float)m_Viewport.top;

	// プロジェクションマトリクス設定
	m_ProjectionMatrix = XMMatrixPerspectiveFovLH(1.0f, (dxViewport.Width / dxViewport.Height) , 1.0f, 100000.0f);

	// ビューマトリクス設定
	m_InvViewMatrix = XMMatrixRotationRollPitchYaw(XMConvertToDegrees(-90), m_Rotation.y, m_Rotation.z);
	m_InvViewMatrix *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	//XMFLOAT3 up = XMFLOAT3(0.0f, 0.0f, 1.0f);
	//XMFLOAT3 focus = XMFLOAT3(0.0f, 0.0f, 0.0f);

	//m_InvViewMatrix = XMMatrixLookAtLH(
	//	XMLoadFloat3(&m_Position),
	//	XMLoadFloat3(&focus),
	//	XMLoadFloat3(&up)
	//	);

	XMVECTOR det;
	m_ViewMatrix = XMMatrixInverse(&det, m_InvViewMatrix);

}

void CLight::Uninit()
{


}


void CLight::Update()
{

	if (CInput::GetKeyPress('R'))
	{
		m_Position.y += 0.1f;
	}
	if (CInput::GetKeyPress('F'))
	{
		m_Position.y -= 0.1f;
	}
	// ビューマトリクス設定
	m_InvViewMatrix = XMMatrixRotationRollPitchYaw(XMConvertToDegrees(-90), m_Rotation.y, m_Rotation.z);
	m_InvViewMatrix *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	XMVECTOR det;
	m_ViewMatrix = XMMatrixInverse(&det, m_InvViewMatrix);
}

XMMATRIX & CLight::GetViewMatrix()
{
	return m_ViewMatrix;
}

XMMATRIX & CLight::GetProjectionMatrix()
{
	return m_ProjectionMatrix;
}

XMFLOAT4 CLight::GetCameraPosition4f()
{
	return XMFLOAT4(m_Position.x,m_Position.y,m_Position.z,NULL);
}

void CLight::Draw()
{
}