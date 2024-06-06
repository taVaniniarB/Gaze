#include "pch.h"
#include "CMonster.h"
#include "CTimeMgr.h"
#include "CCollider.h"

CMonster::CMonster()
	: m_vCenterPos(Vec2(0.f, 0.f))
	, m_fSpeed(100.f)
	, m_fMaxDistance(50.f)
	, m_iDir(1)
	, m_iHP(5)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));
}

CMonster::~CMonster()
{
}



void CMonster::update()
{
	Vec2 vCurPos = GetPos();

	//���� ���⿡ ���߾� �ð� �� seppd ��ŭ �̵�
	vCurPos.x += fDT * m_fSpeed * m_iDir; //iDir�� -1�̰ų� 1�̶�, �װ� ���ϸ� ���� Ȥ�� ���!

	// ��ȸ �Ÿ� ���ط��� �Ѿ���� Ȯ��
	// DT�� ���ϴ� ����̶�, �ر� ��ĥ �� ������ ����
	
	// ���:�ʰ��� ����:�����̵���
	float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDistance;
	
	// ���� ��� = dt ��꿡 ���� �ִ� �Ÿ� �ʰ��ߴ�
	if (0.f < fDist)
	{
		// ���� ��ȯ
		m_iDir *= -1;
		vCurPos.x += fDist * m_iDir;
	}

	SetPos(vCurPos);
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	// �浹�� ������Ʈ�� ��ü�� �˾Ƴ��� (�浹ü�� owner ��ȯ�ϴ� GetObj)
	CObject* pOtherObj = _pOther->GetObj();
	// obj ���� �˾Ƴ��� ���: ������Ʈ�� ���̵� �±׸� �ο�

	if (pOtherObj->GetName() == L"Player_Missile")
	{
		--m_iHP;

		if(m_iHP <= 0)
			DeleteObject(this);
	}

	int a = 0;
}