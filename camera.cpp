#include "main.h"
#include "renderer.h"
#include "game_object.h"
#include "input.h"
#include "shader.h"
#include "camera.h"


void CCamera::Init()
{
	m_Position = XMFLOAT3(0.0f, 5.0f, -10.0f);
	m_Rotation = XMFLOAT3(0.5f, 0.0f, 0.0f);
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

	CRenderer::GetDeviceContext()->RSSetViewports(1, &dxViewport);

	// プロジェクションマトリクス設定
	m_ProjectionMatrix = XMMatrixPerspectiveFovLH(1.0f, dxViewport.Width / dxViewport.Height, 1.0f, 1000.0f);

	// ビューマトリクス設定
	m_InvViewMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	m_InvViewMatrix *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	XMVECTOR det;
	m_ViewMatrix = XMMatrixInverse(&det, m_InvViewMatrix);

}

void CCamera::Uninit()
{
}


void CCamera::Update()
{
	inputValid = CheckInput();

	if (inputValid)
	{
		// ビューマトリクス設定
		m_InvViewMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
		m_InvViewMatrix *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

		XMVECTOR det;
		m_ViewMatrix = XMMatrixInverse(&det, m_InvViewMatrix);
	}
}

bool CCamera::CheckInput()
{
	if (CInput::GetKeyPress(VK_UP))
	{
		m_Position.z += Move_Speed;
		return true;
	}
	if (CInput::GetKeyPress(VK_DOWN))
	{
		m_Position.z -= Move_Speed;
		return true;
	}
	if (CInput::GetKeyPress(VK_RIGHT))
	{
		m_Position.x += Move_Speed;
		return true;
	}
	if (CInput::GetKeyPress(VK_LEFT))
	{
		m_Position.x -= Move_Speed;
		return true;
	}
	if (CInput::GetKeyPress(VK_PRIOR))
	{
		m_Position.y += Move_Speed;
		return true;
	}
	if (CInput::GetKeyPress(VK_NEXT))
	{
		m_Position.y -= Move_Speed;
		return true;
	}
	return false;
}

XMMATRIX & CCamera::GetViewMatrix()
{
	return m_ViewMatrix;
}

XMMATRIX & CCamera::GetProjectionMatrix()
{
	return m_ProjectionMatrix;
}

XMFLOAT4 CCamera::GetCameraPosition4f()
{
	return XMFLOAT4(m_Position.x,m_Position.y,m_Position.z,NULL);
}

void CCamera::Draw()
{
}