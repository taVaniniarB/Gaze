#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);

private:
	CUI*	m_pFocusedUI;

public:
	void update();
	// ����Ű ���� ���� �ٷ� ��Ŀ�� ���ִ� �Լ�
	void SetFocusedUI(CUI* _pUI);

private:
	CUI* GetFocusedUI();
	// �θ� UI���� ������ Ÿ���õ� UI ã�Ƽ� ��ȯ�Ѵ�.
	CUI* GetTargetedUI(CUI* _pParentUI);
};

