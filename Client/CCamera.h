#pragma once

class CObject;

class CCamera
{
	SINGLE(CCamera);
private:
	Vec2		m_vLookAt; // ī�޶� ��ġ ��ǥ (��ǥ ��ǥ)
	Vec2		m_vCurLookAt; // ������ġ�� ������ġ ���� ��ġ (���� ī�޶� ��ġ)
	Vec2		m_vPrevLookAt; // ī�޶��� ���� ������ ��ġ
	// �ް��� ī�޶� �̵� �߻� ��, ƽ �ϰ� �̵����� �ʰ� õõ�� �̵��ϴ� ȿ��
	
	CObject*	m_pTargetObj; // ī�޶� Ÿ�� ������Ʈ (�Ѿư� ������Ʈ)
	Vec2		m_vDiff; // �ػ� �߽� ��ġ�� ī�޶� LookAt �� ���̰�

	float		m_fTime;
	float		m_fSpeed; // Ÿ�� ���󰡴� �ӵ�
	float		m_fAccTime;

public:
	// �̵� ��ǥ ��ǥ, (�� ��) �̵��Ÿ�(speed), �����ð��� �����Ѵ�
	void SetLookAt(Vec2 _vLook)
	{
		m_vLookAt = _vLook;

		// ���-���� ��ǥ '����'�� ���ϱ�
		float fMoveDist = (m_vLookAt - m_vPrevLookAt).Length();
		
		
		m_fSpeed = fMoveDist / m_fTime;
		m_fAccTime = 0.f;
	}
	void SetTarget(CObject* _pTarget) { m_pTargetObj = _pTarget; }
	Vec2 GetLookAt() { return m_vCurLookAt; }
	Vec2 GetRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff; }
	// ��������ǥ > ��¥��ǥ ��ȯ
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }

public:
	void update();

private:
	void CalDiff();

};

