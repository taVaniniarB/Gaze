#include "pch.h"
#include "CCamera.h"

#include "CObject.h"
#include "CCore.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

CCamera::CCamera()
	: m_pTargetObj(nullptr)
	, m_fTime(0.5f)
	, m_fSpeed(0.f)
	, m_fAccTime(0.f)
{

}
CCamera::~CCamera()
{

}



void CCamera::update()
{
	if (m_pTargetObj)
	{
		if (m_pTargetObj->IsDead())
		{
			m_pTargetObj = nullptr; // ���� ��ü ������� null�����Ǹ� �� �Ǵϱ� ����
		}
		else
		{
			m_vLookAt = m_pTargetObj->GetPos();
		}
	}

	if (KEY_HOLD(KEY::UP))
		m_vLookAt.y -= 500.f * fDT;
	if (KEY_HOLD(KEY::DOWN))
		m_vLookAt.y += 500.f * fDT;
	if (KEY_HOLD(KEY::RIGHT))
		m_vLookAt.x += 500.f * fDT;
	if (KEY_HOLD(KEY::LEFT))
		m_vLookAt.x -= 500.f * fDT;


	// ȭ�� �߾���ǥ�� ī�޶� LookAt ���� ���
	CalDiff();
}

void CCamera::CalDiff()
{
	m_fAccTime += fDT;

	// �ð� �ʰ� ��, ���� �������� ����
	if (m_fAccTime >= m_fTime)
	{
		m_vCurLookAt = m_vLookAt;
	}
	else
	{
		// �Ѿư� ���� ���� ���
		Vec2 vLookDir = m_vLookAt - m_vPrevLookAt;

		// ������ �߻� ���
		if (!vLookDir.isZero())
		{
		// ��ӵ� �
		// �ӵ�-�ð� �׷����� ����(���ӵ��� ũ��)�� 4�� �����ؼ�
		// �ð��� AccTime���� �Ͽ�, �ӵ� v�� ���Ѵ�.
		// ����, �żӽ� ���Ŀ� ���� �ð� ���� Ŀ�� �ӵ��� �������Ƿ�, ����>���� ���� �ϱ� ���� �ð����� m_fTime - m_fAccTime �̷��� �������
			float vel = 4.f * (m_fTime - m_fAccTime);

			// ���� ��ġ + ( ���� * (�ӷ� * ���ӵ�) * DT )
			m_vCurLookAt = m_vPrevLookAt + vLookDir.Nomalize() * m_fSpeed * vel * fDT;
		}


		

		// ���� LookAt + (����ȭ�� ���⺤��*�ӵ�)
		//m_vCurLookAt = m_vPrevLookAt + vLookDir.Nomalize() * m_fSpeed * fDT;
	}
	
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2;

	m_vDiff = m_vCurLookAt - vCenter;
	m_vPrevLookAt = m_vCurLookAt;

	
}