#include "pch.h"
#include "CUIMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CUI.h"
#include "CKeyMgr.h"

CUIMgr::CUIMgr()
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::update()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	// ��� �ֻ��� �θ� UI���� ��� ���� (�ڽ� UI�� �� �Ʒ� ���������� �޷� ���� ���̰�)
	const vector<CObject*>& vecUI = pCurScene->GetGroupObject(GROUP_TYPE::UI);



	// �̹� �����ӿ� �� ���ȴ��� Ȯ��
	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	// �� �������� Ȯ��
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	// �� �� false�� ���� �־ �� �� true�� ���� ���� > else if ���

	for (size_t i = 0; i < vecUI.size(); ++i)
	{
		// obejct�� �ƴ� ui���� �ִ� �Լ� ��� ���� �ٿ�ĳ����
		CUI* pUI = (CUI*)vecUI[i];

		pUI = GetTargetedUI(pUI);

		// Ÿ�� UI�� null�� �ƴϴ� = ���콺 �ø� UI �����Ѵ�
		// = �� UI�� MouseOn ȣ��
		if (nullptr != pUI)
		{
			pUI->MouseOn();

			// �ǵǾ���
			if (bLbtnTap)
			{
				pUI->MouseLbtnDown();
				pUI->m_bLbtnDown = true; // �������� ����
			}
			else if (bLbtnAway)
			{
				pUI->MousebtnUp();

				if (pUI->m_bLbtnDown)
				{
					pUI->MouseLbtnClicked();
				}

				pUI->m_bLbtnDown = false;
			}
			//Ŭ���̶�?
			// LbtnDown ���� LbtnUp �߻�
		}
	}
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
		else //�׷��� ���� ��
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

	// ���� ��ư ����, ���ȴ� üũ�� �ٽ� ����
	if (bLbtnAway)
	{
		for (size_t i = 0; i < vecNoneTarget.size(); ++i)
		{
			vecNoneTarget[i]->m_bLbtnDown = false;
		}
	}

	return pTargetUI;
}
