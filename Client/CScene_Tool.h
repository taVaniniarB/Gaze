#pragma once

#include "CScene.h"
class CScene_Tool:
	public CScene
{
private:
public:
	virtual void Enter();
	virtual void Exit();
	virtual void update();
	//virtual void finalUpdate();
	//virtual void render();

	// �۾� ���¿� ���� �б�ó�� or Enum �����ص���

public:
	// ���콺 Ŭ�� �� Ÿ�� �ε��� 1 ����
	void SetTileIdx();


public:
	CScene_Tool();
	~CScene_Tool();
};

