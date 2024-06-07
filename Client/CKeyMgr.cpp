#include "pch.h"
#include "CKeyMgr.h"
#include "CCore.h"

// Ű�� enum�� ���� �Ȱ��� ��Ī�� ���� �迭 �������ν�,
// �ε��� �������� vKey ���� �˰� ��
int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT, //LEFT,
	VK_RIGHT, //RIGHT,
	VK_UP, //UP,
	VK_DOWN, //DOWN,
	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'Z',
	'X',
	'C',
	'V',
	'B',



	VK_MENU, // ALT
	VK_CONTROL, // CTRL
	VK_LSHIFT,
	VK_SPACE,
	VK_RETURN, // ENTER
	VK_ESCAPE, // ESC

	VK_LBUTTON,
	VK_RBUTTON,
};


CKeyMgr::CKeyMgr()
{}

CKeyMgr::~CKeyMgr()
{}

void CKeyMgr::init()
{
	// Ű ����ü ���͸� ä���
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
	//m_vecKey[(int)KEY::LEFT].bPrevPush; // �̷������� ������ ���ȴ�����
	//m_vecKey[(int)KEY::LEFT].eState; // Ű�� ���� üũ �����ϴ�
}

void CKeyMgr::update()
{
	// ������ ��Ŀ�� �˾Ƴ���
	//HWND hMainWnd = CCore::GetInst()->GetMainHwnd();
	HWND hWnd = GetFocus(); // ���� ��Ŀ�� �Ǿ� �ִ� �������� �ڵ� ���� �˷��ִ� �Լ�
	// ���ٸ�, nullptr ��ȯ

	// �츮 ���α׷��� �����찡 ���� ���� �� �ִµ�,
	// ���� �����츸 ���� �Ŷ��, hWnd�� hMainWnd�� ������ �ٸ����� üũ�� ���� ������
	// �׳� ���� ������ ��� ���� �� ���α׷��� �ٸ� ������� ��Ŀ�� �Ǿ� ���� �� Ű �Է��� ó���ϵ��� ������
	if (nullptr != hWnd)
	{
		// Ű���� ���¸� �����Ѵ�
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			// Ű�� ���ȴٸ�
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_vecKey[i].bPrevPush)
					m_vecKey[i].eState = KEY_STATE::HOLD;
				else
				{
					m_vecKey[i].eState = KEY_STATE::TAP;
					m_vecKey[i].bPrevPush = true;
				}
			}
			else
			{
				if (m_vecKey[i].bPrevPush)
					m_vecKey[i].eState = KEY_STATE::AWAY;
				else
				{
					m_vecKey[i].eState = KEY_STATE::NONE;
				}

				m_vecKey[i].bPrevPush = false;
			}
		}

		// mouse ��ġ ���
		POINT ptPos = {};
		
		// GetCursorPos�� ��üȭ�� ������ Ŀ�� ��ǥ ��ȯ(Ŭ���̾�Ʈ â ������ �ƴ�)
		GetCursorPos(&ptPos);

		// Ŭ���̾�Ʈ ������ ���� ��ǥ�� �ڵ����� ������ִ� �Լ�
		ScreenToClient(CCore::GetInst()->GetMainHwnd(), &ptPos);

		m_vCurMousePos = Vec2((float)ptPos.x, (float)ptPos.y);
	}

	//������ ��Ŀ�� ���� ����!
	else
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			m_vecKey[i].bPrevPush = false;

			if (KEY_STATE::TAP == m_vecKey[i].eState || KEY_STATE::HOLD == m_vecKey[i].eState)
				m_vecKey[i].eState = KEY_STATE::AWAY;
			else if (KEY_STATE::AWAY == m_vecKey[i].eState)
				m_vecKey[i].eState = KEY_STATE::NONE;
		}
	}
}