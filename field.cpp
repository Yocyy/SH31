#include "field.h"
#include "scene.h"



CField::CField()
{
}


CField::~CField()
{
}

void CField::Init()
{
	VERTEX_3D vertex[4];

	vertex[0].Position = XMFLOAT3(-10.0f, 0.0f, 10.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(10.0f, 0.0f, 10.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(-10.0f, 0.0f, -10.0f);
	vertex[2].Diffuse = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(10.0f, 0.0f, -10.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);


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
	m_Texture->Load("data/TEXTURE/cocoon.tga");

	m_Shader = new CShader();
	m_Shader->Init("x64/Debug/shader3DTestVS.cso", "x64/Debug/shader3DTestPS.cso");
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

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	CRenderer::SetTexture(m_Texture);

	XMMATRIX world;
	world = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	world *= XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);
	world *= XMMatrixTranslation(0.0f, -5.0f, 0.0f);

	XMFLOAT4X4 projection;
	XMFLOAT4X4 matrix;
	DirectX::XMStoreFloat4x4(&projection, XMMatrixPerspectiveFovLH(XM_PI / 2, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000.0f));
	XMStoreFloat4x4(&matrix, world);
	m_Shader->SetWorldMatrix(&matrix);
	CCamera* camera = CManager::GetScene()->GetGameObject<CCamera>();
	XMStoreFloat4x4(&matrix, camera->GetViewMatrix());
	m_Shader->SetViewMatrix(&matrix);
	m_Shader->SetProjectionMatrix(&projection);

	m_Shader->Set();


	// �v���~�e�B�u�g�|���W�ݒ�
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`��
	CRenderer::GetDeviceContext()->Draw(4, 0);
}