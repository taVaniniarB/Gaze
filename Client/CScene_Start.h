#pragma once
#include "CScene.h"
class CScene_Start :
    public CScene
{
public:
    // �����Լ����� ��������� �����ش� (Ű���� ��� �������̵� �� �����Լ��� ��!)
    virtual void Enter();
    virtual void Exit();
    virtual void update();

public:
    CScene_Start();
    ~CScene_Start();
};

