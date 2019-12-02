//#include "main.h"
//#include "game_object.h"
//#include "texture.h"
//#include "renderer.h"
//#include "input.h"
//#include "fbxManager.h"
//#include "field.h"
//#include "scene.h"
//#include "manager.h"
//#include "player.h"
//
//static float MoveSpeed = 0.1f;
//static float RotationSpeed = 0.1f;
//
//
//
//
//void CPlayer::Init()
//{
//	m_FBXManager = new CFBxManager();
//	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
//
//
//
//
//
//	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
//	m_Scale = XMFLOAT3(0.1f, 0.1f, 0.1f);
//	
//

//	m_Shader = new CShader();
//	m_Shader->Init("x64/Debug/shader3DTestVS.cso", "x64/Debug/shader3DTestPS.cso");
//	m_FBXManager->Load("model/unitychan.fbx");
//}
//
//void CPlayer::Draw()
//{
//	// マトリクス設定
//	XMMATRIX world;
//	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
//	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
//	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
//
//	m_FBXManager->Draw(&world,"model/unitychan.fbx");
//}
//
//void CPlayer::Update()
//{
//
//	////////////////////////////////////////////////////////
//	////				移 動
//	////////////////////////////////////////////////////////
//
//
//	if (CInput::GetKeyPress('W')) {
//		// Wキーが押されている時の処理
//		m_Position.x += MoveSpeed * g_front.x;
//		m_Position.z += MoveSpeed * g_front.z;
//	}
//	if (CInput::GetKeyPress('S')) {
//		// Dキーが押されている時の処理
//		m_Position.x -= MoveSpeed * g_front.x;
//		m_Position.z -= MoveSpeed * g_front.z;
//	}
//	if (CInput::GetKeyPress('D')) {
//		// Aキーが押されている時の処理
//		m_Position.x += MoveSpeed * g_right.x;
//		m_Position.z += MoveSpeed * g_right.z;
//	}
//	if (CInput::GetKeyPress('A')) {
//		// Sキーが押されている時の処理
//		m_Position.x -= MoveSpeed * g_right.x;
//		m_Position.z -= MoveSpeed * g_right.z;
//	}
//
//}
//
//XMFLOAT3 CPlayer::Get_Player_Position()
//{
//	return m_Position;
//}
//XMFLOAT3 CPlayer::Get_Player_Rotation()
//{
//	return m_Rotation;
//}
//XMFLOAT3 CPlayer::Get_Player_Front()
//{
//	return g_front;
//}
//void CPlayer::Uninit()
//{
//}