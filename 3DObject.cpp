#include "main.h"
#include "input.h"
#include "3DObject.h"
#include "scene.h"
#include "renderer.h"
#include "OBJmodel.h"
#include "shader.h"
#include "manager.h"
#include "Camera.h"
#include "Light.h"

void C3DObject::Init()
{
	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);	//float(rand() % 10)
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	m_Model = new COBJModel();
	m_Model->Load("model/sphere_smooth.obj");
	m_Shader = new CShader();
	m_Shader->Init("x64/Debug/shader3DTestVS.cso", "x64/Debug/shader3DTestPS.cso");
}

void C3DObject::Uninit()
{
	m_Shader->Uninit();
	delete m_Shader;

	m_Model->Unload();
	delete m_Model;
}

void C3DObject::Update()
{
	//if (CInput::GetKeyPress('W'))
	//{
	//	m_Position.z += Move_Speed;
	//}
	//if (CInput::GetKeyPress('S'))
	//{
	//	m_Position.z -= Move_Speed;
	//}
	//if (CInput::GetKeyPress('D'))
	//{
	//	m_Position.x += Move_Speed;
	//}
	//if (CInput::GetKeyPress('A'))
	//{
	//	m_Position.x -= Move_Speed;
	//}

	if (CInput::GetKeyPress('W'))
	{
		m_Rotation.x += Rot_Speed;
	}
	if (CInput::GetKeyPress('S'))
	{
		m_Rotation.x -= Rot_Speed;
	}
	if (CInput::GetKeyPress('D'))
	{
		m_Rotation.y += Rot_Speed;
	}
	if (CInput::GetKeyPress('A'))
	{
		m_Rotation.y -= Rot_Speed;
	}


	if (CInput::GetKeyPress('I'))
	{
		m_Position.z += Rot_Speed;
	}
	if (CInput::GetKeyPress('K'))
	{
		m_Position.z -= Rot_Speed;
	}

	if (CInput::GetKeyPress('L'))
	{
		m_Position.x += Rot_Speed;
	}
	if (CInput::GetKeyPress('J'))
	{
		m_Position.x -= Rot_Speed;
	}

	//if (CInput::GetKeyPress(VK_UP))
	//{
	//	m_Position.z += Rot_Speed;
	//}
	//if (CInput::GetKeyPress(VK_DOWN))
	//{
	//	m_Position.z -= Rot_Speed;
	//}
	//if (CInput::GetKeyPress(VK_RIGHT))
	//{
	//	m_Position.x += Rot_Speed;
	//}
	//if (CInput::GetKeyPress(VK_LEFT))
	//{
	//	m_Position.x -= Rot_Speed;
	//}
}

void C3DObject::Draw()
{

	CCamera* camera = CManager::GetScene()->GetGameObject<CCamera>();

	// マトリクス設定
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	XMFLOAT4X4 world4x4;
	XMStoreFloat4x4(&world4x4, world);
	m_Shader->SetWorldMatrix(&world4x4);
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	XMFLOAT4X4 viewmatrix4x4;
	XMStoreFloat4x4(&viewmatrix4x4, camera->GetViewMatrix());
	m_Shader->SetViewMatrix(&viewmatrix4x4);

	XMFLOAT4X4 promatrix4x4;
	XMStoreFloat4x4(&promatrix4x4, camera->GetProjectionMatrix());
	m_Shader->SetProjectionMatrix(&promatrix4x4);

	m_Shader->SetCameraPosition(&camera->GetCameraPosition4f());

	//CLight* c_light = CManager::GetScene()->GetGameObject<CLight>();
	//LIGHT* light = {};
	//light->ProjectionMatrix = c_light->GetProjectionMatrix();
	//light->ViewMatrix = c_light->GetViewMatrix();
	//m_Shader->SetLight(light);

	m_Shader->Set();
	m_Model->Draw();
}

void C3DObject::DrawShadow()
{
	CRenderer::SetShadowTexture(0);

	// マトリクス設定
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	XMFLOAT4X4 world4x4;
	XMStoreFloat4x4(&world4x4, world);
	m_Shader->SetWorldMatrix(&world4x4);

	CLight* light = CManager::GetScene()->GetGameObject<CLight>();
	XMFLOAT4X4 TempMatrix;
	XMStoreFloat4x4(&TempMatrix, light->GetViewMatrix());
	m_Shader->SetViewMatrix(&TempMatrix);

	XMStoreFloat4x4(&TempMatrix, light->GetProjectionMatrix());
	m_Shader->SetProjectionMatrix(&TempMatrix);

	m_Shader->Set();
	m_Model->Draw();
}