#pragma once
#include "CObject.h"
class CMonster :
    public CObject
{
private:
    Vec2    m_vCenterPos; // �͸����� ĥ�ǵ�, �߾� ��ǥ
    float   m_fSpeed;       // �ʴ� �̵��� �ȼ� ��
    float   m_fMaxDistance; // �͸����� �Ÿ�
    int     m_iDir;     //1(����), -1(����)
    int     m_iHP;

public:
    float GetSpeed() { return m_fSpeed; }
    void SetSpeed(float _f) { m_fSpeed = _f; }
    void SetMoveDist(float _f) { m_fMaxDistance = _f; }
    void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }

public:
    virtual void OnCollisionEnter(CCollider* _pOther);
    
public:
    void update();
    CLONE(CMonster);

public:
    CMonster();
    ~CMonster();
};

