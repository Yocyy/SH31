#include "main.h"
#include "input.h"
#include "field.h"
#include "scene.h"
#include "renderer.h"
#include "texture.h"
#include "shader.h"
#include "manager.h"
#include "Camera.h"
#include "light.h"

void CField::Init()
{
	VERTEX_3D vertex[4];

	vertex[0].Position = XMFLOAT3(-50.0f, 0.0f, 50.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(50.0f, 0.0f, 50.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(-50.0f, 0.0f, -50.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(50.0f, 0.0f, -50.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	m_Position = XMFLOAT3(0,-5,0);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	m_Texture = new CTexture();
	m_Texture->Load("data/TEXTURE/field004.tga");

	m_Shader = new CShader();
	//shader3DTestVS shader3DShadowPS
	m_Shader->Init("x64/Debug/shader3DShadowVS.cso", "x64/Debug/shader3DShadowPS.cso");
}

void CField::Uninit()
{
	m_Shader->Uninit();
	delete m_Shader;

	m_VertexBuffer->Release();

	m_Texture->Unload();
	delete m_Texture;
}

void CField::Update()
{
}

void CField::Draw()
{
	CRenderer::SetShadowTexture(0);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	//CRenderer::SetTexture(m_Texture);

	XMMATRIX world;
	world = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	XMFLOAT4X4 matrix;
	XMStoreFloat4x4(&matrix, world);
	m_Shader->SetWorldMatrix(&matrix);

	CCamera* camera = CManager::GetScene()->GetGameObject<CCamera>();
	XMStoreFloat4x4(&matrix, camera->GetViewMatrix());
	m_Shader->SetViewMatrix(&matrix);

	XMStoreFloat4x4(&matrix, camera->GetProjectionMatrix());
	m_Shader->SetProjectionMatrix(&matrix);

	m_Shader->SetCameraPosition(&camera->GetCameraPosition4f());

	CLight* light = CManager::GetScene()->GetGameObject<CLight>();
	LIGHT ConsLight;
	ConsLight.Direction = XMFLOAT4(0.0f, -1.0f, 0.0f, 0.0f);	//ライトベクトル
	ConsLight.Diffuse = COLOR(0.0f, 0.0f, 0.0f, 0.0f);	//ライトカラー
	ConsLight.Ambient = COLOR(0.0f, 0.0f, 0.0f, 0.0f);	//環境光;
	ConsLight.ViewMatrix = light->GetViewMatrix();
	ConsLight.ProjectionMatrix = light->GetProjectionMatrix();
	m_Shader->SetLight(&ConsLight);

	m_Shader->Set();


	// プリミティブトポロジ設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	CRenderer::GetDeviceContext()->Draw(4, 0);
}

void CField::DrawShadow()
{
	CRenderer::SetShadowTexture(0);
	CLight* light = CManager::GetScene()->GetGameObject<CLight>();
	XMFLOAT4X4 TempMatrix;
	XMStoreFloat4x4(&TempMatrix, light->GetViewMatrix());
	m_Shader->SetViewMatrix(&TempMatrix);

	XMStoreFloat4x4(&TempMatrix, light->GetProjectionMatrix());
	m_Shader->SetProjectionMatrix(&TempMatrix);

	m_Shader->Set();

	// プリミティブトポロジ設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	CRenderer::GetDeviceContext()->Draw(4, 0);

}

