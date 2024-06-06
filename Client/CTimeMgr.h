#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	//������ �� �ð�(��Ÿ Ÿ��)�� ���غ���
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llFrequency;

	double			m_dDT; // ��Ÿ Ÿ��. ������ ������ �ð�
	double			m_dAcc; // 1�� üũ�� ���� DT ����(�� ������ ����ð�)
	UINT			m_iCallCount; // �� �� Ÿ�ӸŴ��� �Լ� ȣ�� Ƚ��(������ ��) üũ
	UINT			m_iFPS; //�� �� ȣ�� Ƚ��

public:
	void init();
	void update();
	void render();

public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }
};

