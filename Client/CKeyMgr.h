#pragma once

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,	
	
	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	A,
	S,
	D,
	F,
	G,
	Z,
	X,
	C,
	V,
	B,

	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,

	LBTN,
	RBTN,

	LAST,
};

enum class KEY_STATE
{
	TAP, // �� ������
	HOLD, // ������ �ִ�
	AWAY, // �� �� ����
	NONE, // �������� �ȴ��Ȱ� ���ݵ� �ȴ���
};

struct tKeyInfo
{
	KEY_STATE	eState;// ���°�
	bool		bPrevPush; // ���� �����ӿ� Ű�� ���ȴ°�?
};

class CKeyMgr
{
	SINGLE(CKeyMgr);

private:
	vector<tKeyInfo> m_vecKey;
	// ���� �ȿ� ��� Ű ���� enum ������� ����
	// Ű���� �ε����� ����
	Vec2			m_vCurMousePos;

public:
	void init();
	void update();

public:
	KEY_STATE GetKeyState(KEY _eKey) { return m_vecKey[(int)_eKey].eState; }
	Vec2 GetMouseCursor() { return m_vCurMousePos; }
};

