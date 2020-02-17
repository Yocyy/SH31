#pragma once

#include "game_object.h"

class CScene;
class CShader;
class COBJModel;

class C3DObject : public CGameObject
{
private:
	CShader* m_Shader;
	COBJModel* m_Model;
	float Move_Speed = 0.1f;
	float Rot_Speed = 0.1f;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void DrawShadow();
};