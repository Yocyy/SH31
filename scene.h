#pragma once

#include <list>
#include <typeinfo>
#include "main.h"

#include "game_object.h"

#include "polygon.h"
#include "Field.h"
#include "camera.h"
#include "fieldNormal.h"

class CScene
{
protected:
	std::list<CGameObject*>	m_GameObject;

public:
	CScene(){}
	virtual ~CScene(){}


	virtual void Init()
	{
		AddGameObject<CCamera>();
		//AddGameObject<CField>();
		AddGameObject<CFieldNormal>();
		AddGameObject<CPolygon>();
		//AddGameObject<CPlayer>();
	}

	virtual void Uninit()
	{
		for (CGameObject* object : m_GameObject)
		{
			object->Uninit();
			delete object;
		}

		m_GameObject.clear();
	}


	virtual void Update()
	{
		for( CGameObject* object : m_GameObject )
			object->Update();
	}


	virtual void Draw()
	{
		for (CGameObject* object : m_GameObject)
			object->Draw();
	}


	template <typename T>
	T* AddGameObject()
	{
		T* gameObject = new T();
		gameObject->Init();
		m_GameObject.push_back( gameObject );

		return gameObject;
	}

	template <typename T>
	T* GetGameObject()
	{
		for (CGameObject* object : m_GameObject)

		{
			if (typeid(*object) == typeid(T))
			{
				return (T*)object;
			}
		}
		return nullptr;
	}
};