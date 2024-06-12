#include "pch.h"
#include "CScene_Tool.h"
#include "CKeyMgr.h"

#include "CSceneMgr.h"
#include "CCore.h"
#include "CCamera.h"

#include "CTile.h"
#include "CResMgr.h"
#include "CSceneMgr.h"
#include "CUI.h"

#include "resource.h"


CScene_Tool::CScene_Tool()
{
}

CScene_Tool::~CScene_Tool()
{
}


void CScene_Tool::Enter()
{
	// Ÿ�� ����
	CreateTile(5, 5);
	
	// UI ����
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	CUI* pUI = new CUI;
	pUI->SetScale(Vec2(100.f, 30.f));
	pUI->SetPos(Vec2(vResolution.x - pUI->GetScale().x, 0.f));
	
	AddObject(pUI, GROUP_TYPE::UI);

	// ī�޶� LookAt ����
	// 	   //���� UI �������� �ػ� �޾ƿ��� �κ� �־, �ϴ� �ּ� ó��
	//Vec2 vResolution = CCore::GetInst()->GetResolution();
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);

}

void CScene_Tool::Exit()
{
}




void CScene_Tool::update()
{
	CScene::update();

	SetTileIdx();
}


void CScene_Tool::SetTileIdx()
{
	if (KEY_TAP(KEY::LBTN))
	{
		// ���콺 ��ġ�� ������ǥ�� ��ȯ
		Vec2 vMousePos = MOUSE_POS;;
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

		int iTileX = (int)GetTileX();
		int iTileY = (int)GetTileY();

		// ������ǥ ����Ͽ� int
		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		// Ÿ�� ���� �� Ŭ�� ����ó��
		if (vMousePos.x < 0.f || iCol >= iTileX
			|| vMousePos.y < 0.f || iRow >= iTileY)
		{
			return;
		}


		UINT iIdx = iRow * iTileX + iCol;

		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		// CObject �������̱� ������, CTile Ÿ������ ĳ����
		// �ڿ������� ������ �����Ͽ� ��ȣ ���ֱ�
		((CTile*)vecTile[iIdx])->AddImgIdx();
	}
	// ���콺 ��ǥ�� ����Ų Ÿ���� � Ÿ������ �˾Ƴ���
	// ���콺 ��ǥ.x, y�� ���� Ÿ�� ������� ������ �� ��° ��, ������ �� �� �ִ�
	// �̷��� ���� ��, ����, Ÿ�� ���� �� �Է��� �ִ� ��, �� ���� ������ ������Ʈ�� Ÿ�� �׷� ���͸� ��ȸ
	// ���� �ε����� ���� �ݺ��� �� ���� �ٷ� ���� ����
	
}





// Tool Scene�� ��� X, ���� ���ϰ� ��ġ�� �̷��� �صа���
// =======================
// Tile Count Window Proc
// =======================
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			// dialog ���� ������ �������� ���ִ� �Լ�
			// �ڵ�, ID(ID ������ ���ҽ� ��� �������ֱ�), �ʿ����, ����ó��)
			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

			// Ÿ�� ���� ���� �ؾ��� ��: ���� Ÿ�� �����
			// Ÿ�� �׷� ������Ʈ���� ��� ������
			// ����� ����Լ��� �ƴϹǷ� SceneMgr�������� scene �޾ƿ;� ��
			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
			// ������ Tool Scene������ �� UI ����̹Ƿ�, �޴��ٴ� ToolScene������ Ȱ��ȭ�Ѵ�
			// �׸��� �ٿ�ĳ������ ���� �� ������ üũ�����ν� �ڵ� �󿡼��� �޴��ٴ� �� ������ ����� ������� ��������� ǥ���Ѵ�

			// ToolScene Ȯ��
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			pToolScene->CreateTile(iXCount, iYCount);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}