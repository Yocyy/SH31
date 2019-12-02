////======================================================================
////
//// FBX���f���Ǘ�[fbxManager.cpp]
////
////======================================================================
//
////**********************************************************************
//// �C���N���[�h�w�b�_�[
////**********************************************************************
//#include "main.h"
//#include "renderer.h"
//#include "fbxManager.h"
//#include "fbx.h"
//#include "shader.h"
//#include <map>
//#include <string>
//
//
////======================================================================
//// �R���X�g���N�^
////======================================================================
//CFBxManager::CFBxManager() {
//}
//
////======================================================================
//// �f�X�g���N�^
////======================================================================
//CFBxManager::~CFBxManager() {
//
//}
//
////======================================================================
//// FBX�̃��[�h
////======================================================================
//void CFBxManager::Load(const char* FileName) {
//	m_Shader = new CShader();
//	CFBX* pFBX;
//	pFBX = new CFBX();
//	m_Models[FileName] = pFBX->Load(FileName);
//	delete pFBX;
//}
//
////======================================================================
//// ���f���̎擾
////======================================================================
//MODEL_* CFBxManager::GetModel(const char* FineName) {
//	return &m_Models[FineName];
//}
//
////======================================================================
//// ���f���̕`��
////======================================================================
//void CFBxManager::Draw(XMMATRIX* pWorld, const char* FileName) {
//	// �|���S���̕`�揇
//	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//
//	// �}�g���N�X�ݒ�
//	XMFLOAT4X4 World4x4;
//	XMStoreFloat4x4(&World4x4,*pWorld);
//	m_Shader->SetWorldMatrix(&World4x4);
//
//	for (MESH mesh : m_Models[FileName].mesh) {
//			// ���_�o�b�t�@�ݒ�
//			CRenderer::SetVertexBuffers(mesh.buffer.vertexBuffer);
//
//			// �C���f�b�N�X�o�b�t�@�ݒ�
//			CRenderer::SetIndexBuffer(mesh.buffer.indexBuffer);
//
//			if(!mesh.texture)
//				CRenderer::SetTexture(mesh.texture);
//
//			// �|���S���`��
//			CRenderer::DrawIndexed(mesh.buffer.indexCount, 0, 0);
//	}
//}
