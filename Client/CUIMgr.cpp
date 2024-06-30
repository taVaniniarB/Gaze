#include "pch.h"
#include "CUIMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CUI.h"
#include "CKeyMgr.h"

CUIMgr::CUIMgr()
	: m_pFocusedUI(nullptr)
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::update()
{
	bool bLbtnTAP = KEY_TAP(KEY::LBTN);
	bool bLbtnAWAY = KEY_AWAY(KEY::LBTN);

	// 1. FocusedUI Ȯ��
	// Ȥ�ó� ���ο� UI ��Ŀ�� ��ȯ���� �ʾҴ��� Ȯ���ؼ�,
	// ���� ���� �������� FocusedUI�� Ȯ���ؾ� ��
	m_pFocusedUI = GetFocusedUI();

	// ��� UI ��Ȱ��ȭ �����̹Ƿ� �̺�Ʈ ó���� �ʿ䵵 ������ ����
	if (!m_pFocusedUI)
		return;


	// 2. FocusedUI ������ �θ� UI ����, �ڽ� UI ��
	//    ���� Ÿ���õ� UI �����ͼ� �̺�Ʈ ó��
	CUI* pTargetUI = GetTargetedUI(m_pFocusedUI);

	if (nullptr != pTargetUI)
	{
		pTargetUI->MouseOn();

		if (bLbtnTAP)
		{
			pTargetUI->MouseLbtnDown();
			pTargetUI->m_bLbtnDown = true;
		}
		else if (bLbtnAWAY)
		{
			pTargetUI->MousebtnUp();

			if (pTargetUI->m_bLbtnDown)
			{
				pTargetUI->MouseLbtnClicked();
			}

			pTargetUI->m_bLbtnDown = false;
		}
	}

}

// ������ Ư�� Ű�� ������ �� UI�� ��� ��ȯ�ϰ� ���� �� ���
void CUIMgr::SetFocusedUI(CUI* _pUI)
{
	// �̹� �װ� ��Ŀ�� ���� ���, nullptr(��Ŀ�� ������û)�� ���
	if (m_pFocusedUI == _pUI || nullptr == _pUI)
	{
		m_pFocusedUI = _pUI;
		return;
	}

	m_pFocusedUI = _pUI;

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIVector();


	// �ݺ��ڿ� ���ͷ�����
	vector<CObject*>::iterator iter = vecUI.begin();
	for (; iter != vecUI.end(); ++iter)
	{
		// ���� ��ȸ�� ��Ŀ�� �����Ұ� ã�Ƴ���
		if (m_pFocusedUI == *iter)
		{
			break;
		}
	}

	//������ü
	vecUI.erase(iter);
	vecUI.push_back(m_pFocusedUI);
}

// �θ� UI�� �߿��� Focus ���� UI�� �����ϱ�
CUI* CUIMgr::GetFocusedUI()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIVector();

	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	// ���� ��Ŀ�� UI�� �޾Ƶΰ�, ����Ǿ����� Ȯ��
	CUI* pFocusedUI = m_pFocusedUI;


	// ��Ŀ�� �Ѿ�� = �ٸ� UI�� ������

	// �̹� �����ӿ��� ��Ŭ���� �߻����� �ʾ�����
	// ��Ŀ�� ��ȯ���� ���ɼ��� ������ ����
	if (!bLbtnTap)
	{
		return pFocusedUI;
	}

	// ���� ��ư TAP�� �߻��ߴٴ� ����

	// Ÿ�� ���ͷ�����
	vector<CObject*>::iterator targetiter = vecUI.end();
	// �ݺ��ڿ� ���ͷ�����
	vector<CObject*>::iterator iter = vecUI.begin();
	for (; iter != vecUI.end(); ++iter)
	{
		// isMouseOn: ���콺 �÷ȴ��� �ƴ��� ��ȯ
		// UI���� ���� ������ MouseOn ���¸� üũ�ؼ� ���� ����.
		// �Ͽ�ư. UI ���� ���콺�� �ö�� �ִµ��ٰ�, TAP �߻����� �ߴ�?
		if (((CUI*)*iter)->IsMouseOn())
		{
			targetiter = iter;
		}
		
		// �ݺ��ϴٺ���, �ᱹ�� ������ ��(����� �������δ� ���� �տ� ���̴�) �ְ�
		// ��Ŀ���� �켱������ ������
	}

	// �̹��� Focus �� UI�� ���� (��� Ŭ��) > nullptr ��ȯ
	if (vecUI.end() == targetiter)
	{
		return nullptr;
	}

	pFocusedUI = (CUI*)*targetiter;

	//������ü(�ڷ� �ű��) ���� erase �� push back
	vecUI.erase(targetiter);
	vecUI.push_back(pFocusedUI);


	return pFocusedUI;
}

CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	// 1. �θ� UI ���� ��� �ڽ� �˻�
	CUI* pTargetUI = nullptr;

	// �Լ� ȣ���� ������ �����ϴ���, ���� ������ ����
	static list<CUI*> queue;
	static vector<CUI*> vecNoneTarget;

	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);

	// ť�� �� �� ������ ���ڴ�
	while (!queue.empty())
	{
		//��� ������
		CUI* pUI = queue.front();
		queue.pop_front();

		// ť���� ���� UI�� Target���� Ȯ��
		// Ÿ�� UI�� �� �켱���� ���� ����: ���� ���� �ڽ� UI
		// �̹� �˻� UI�� mouse On �Ǿ��� �� > �ϴ� Ÿ������ ����
		// > �� ������ ����, ���콺 on�̸鼭 ���� ���� ���� �ڽ��� Ÿ������ �Ǿ� ���� ���̴�
		if (pUI->IsMouseOn())
		{
			// �̹� UI�� ���콺on �Ǹ�, ���� �ݺ������� Ÿ�� UI�� NonTarget ���
			if (nullptr != pTargetUI)
			{
				vecNoneTarget.push_back(pTargetUI);
			}
			pTargetUI = pUI;
		}
		else //MouseOn�� �ƴ� ��, ������ NoneTarget 
		{
			vecNoneTarget.push_back(pUI);
		}

		// ���� �������� �ڽ� ���� ��������
		const vector<CUI*>& vecChild = pUI->GetChildUI();

		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}

	}

	// ���� ��ư ����, noneTarget���� btnDown üũ�� ��� ����
	// �� Target�� �������� �ʴ°�: Ŭ�� ���� �� ���صǱ� ������, nonTarget�� �и���
	// �� AWAY ������ ���� false�� �ϴ°�? ������ Ÿ���� �ƴϸ� �������ٵ� 
	// >>> UI�� ���� ä ȭ�� ������ �巡���ϴ� ��Ȳ ���
	if (bLbtnAway)
	{
		for (size_t i = 0; i < vecNoneTarget.size(); ++i)
		{
			vecNoneTarget[i]->m_bLbtnDown = false;
		}
	}

	return pTargetUI;
}