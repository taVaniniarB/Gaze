#pragma once
#include "CUI.h"
class CPanelUI :
    public CUI
{
private:
    Vec2    m_vDragStart;
public:
    virtual void update();
    virtual void render(HDC _dc);
    virtual void MouseOn(); // ���콺 ���ٴ�
    virtual void MouseLbtnDown(); // ���� ��ư ������ ��
    virtual void MousebtnUp(); // ���콺 ������ ��

    CLONE(CPanelUI);

public:
    CPanelUI();
    ~CPanelUI();
};

