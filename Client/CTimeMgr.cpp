#include "pch.h"
#include "CTimeMgr.h"

#include "CCore.h"


CTimeMgr::CTimeMgr()
	: m_llCurCount{}
	, m_llPrevCount{} //���Ͽ�...?
	, m_llFrequency{}
	, m_dDT(0.)
	, m_iCallCount(0)
	, m_dAcc(0.)
{
}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	// GetTickCount�� ����ѵ� �и������� ����(1�ʿ� õ��)
	// �������̶� ���� ���� �� �ð��� ��� ����!!
	// ���� ī��Ʈ (���α׷� ����~�������)
	QueryPerformanceCounter(&m_llPrevCount);

	// �� �� ī��Ʈ�� �󸶳� �߻��ߴ°�
	QueryPerformanceFrequency(&m_llFrequency);
}


void CTimeMgr::update()
{
	// update�� �� ������ ���� ȣ���.
	// ����, update ȣ�� ���� �� �ð��� ���� �� �ð��� ���̰�
	// 1������ �� �ð��� �ȴ�

	QueryPerformanceCounter(&m_llCurCount);

	//QuadPart �κ��� LARGE_INTEGER �ڷ����� ���� long long �κ� ������
	// �������� �������� 0 �����״ϱ�, float ��ȯ
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)(m_llFrequency.QuadPart);

	

	// fps = 1. / m_dDT;
	// �̷��� �Ź� dt�� ���� fps�� ����ϸ� dt�� ���� fps�� �ʹ� ���߳��������� ����
	// Ÿ�� �Ŵ����� ȣ�� Ƚ���� ����
	// ���� 1�ʿ� �ɸ� ������ ���� ����

	// ���� ������ �ð� ��� ���� ���� ī��Ʈ ���� ���� ī��Ʈ ������ ����
	m_llPrevCount = m_llCurCount;

	// ����� �� DT�� ��Ŀ���� ����
	// DT�� ������ 1/60�ʷ� �����Ѵ�
	// ����� �ڵ忡���� �۵��ϵ��� �Ѵ�
#ifdef _DEBUG
	if (m_dDT > (1. / 60.))
		m_dDT = (1. / 60.);
#endif
}


void CTimeMgr::render()
{
	++m_iCallCount;
	m_dAcc += m_dDT; // DT ���� > ���α׷� ���� �ð�(�� ����)

	if (m_dAcc >= 1.)
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS: %d, DT: %f", m_iFPS, m_dDT);
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}
}