#include "pch.h"
#include "CPathMgr.h"

#include "CCore.h"

CPathMgr::CPathMgr()
	: m_szContentPath{}
{
}

CPathMgr::~CPathMgr()
{}

// �н��Ŵ����� �ʱ�ȭ�� �� content ������ ã�Ƴ� ���̴�!
void CPathMgr::init()
{
	// ���� ����, �� ���� �ּ�
	GetCurrentDirectory(255, m_szContentPath);
	// ���� ��� : ���� �������� ��ġ ��ΰ� ������ ä����

	// ����������
	// + bin \ content �ϸ�, ��� ��Ȳ������ ������ ������ ������ �� �ְڴ�

	int iLen = (int)wcslen(m_szContentPath);

	for (int i = iLen - 1; 0 <= i; --i)
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");

	//SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szContentPath);
}