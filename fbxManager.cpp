////======================================================================
////
//// FBXモデル管理[fbxManager.cpp]
////
////======================================================================
//
////**********************************************************************
//// インクルードヘッダー
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
//// コンストラクタ
////======================================================================
//CFBxManager::CFBxManager() {
//}
//
////======================================================================
//// デストラクタ
////======================================================================
//CFBxManager::~CFBxManager() {
//
//}
//
////======================================================================
//// FBXのロード
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
//// モデルの取得
////======================================================================
//MODEL_* CFBxManager::GetModel(const char* FineName) {
//	return &m_Models[FineName];
//}
//
////======================================================================
//// モデルの描画
////======================================================================
//void CFBxManager::Draw(XMMATRIX* pWorld, const char* FileName) {
//	// ポリゴンの描画順
//	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//
//	// マトリクス設定
//	XMFLOAT4X4 World4x4;
//	XMStoreFloat4x4(&World4x4,*pWorld);
//	m_Shader->SetWorldMatrix(&World4x4);
//
//	for (MESH mesh : m_Models[FileName].mesh) {
//			// 頂点バッファ設定
//			CRenderer::SetVertexBuffers(mesh.buffer.vertexBuffer);
//
//			// インデックスバッファ設定
//			CRenderer::SetIndexBuffer(mesh.buffer.indexBuffer);
//
//			if(!mesh.texture)
//				CRenderer::SetTexture(mesh.texture);
//
//			// ポリゴン描画
//			CRenderer::DrawIndexed(mesh.buffer.indexCount, 0, 0);
//	}
//}
