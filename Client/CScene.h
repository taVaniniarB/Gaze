#pragma once

// ������ �ӵ� �ø��� ���� ��� ���� ��� ���漱��
// ������� �ߴٸ�, object ������ ������ scene�ʵ� �Ź� Ȯ�εż� ������
// ��ü�����δ� �𸣰�, �̷� �ְ� �ִ�~ ������ �˰ԵǴ°���
// Ÿ�Կ� ���� ��ü�� ������ ���� ������ �����ͷιۿ� ����� �� ��
class CObject;

class CScene
{
private:
	// �θ� Ÿ�� �����ͷ� �ڽ�Ÿ�� �� ���� �� ������, �̰� �ϳ��� ��ΰ���
	// ������Ʈ�� ���� ������ ���͸� �׷� ������ŭ ������
	// ������Ʈ �ּ� �޴� ������ �迭!
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END];
	wstring				m_strName; // Scene �̸�

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	virtual void update();
	virtual void finalUpdate();
	virtual void render(HDC _dc);

	// �� ���� �� �ʱ� �۾��� �ϴ� �Լ�. �θ𿡼� ���� ����.
	// �ڽĵ��� �ڱ⸸�� ����� �����ϸ� �Ǵϱ� �θ� �ʿ��� �����Լ�ȭ ���Ѽ�
	// ���� ��ü��(������)�� start�� ȣ��ǵ��� �ѰŴϱ�
	// �ڱ� �������� �����ؾ� �Ѵ�, ��� �� �˸��� �뵵�ϱ�
	// ���������Լ��� �Ǿ�� ��
	// > Scene�� ���� ��ü ������ �Ұ���������.
	// > �������� �����ϰ� �ִ� Ŭ������, 
	// ���� ��üȭ�� �� �ִ� Ŭ������ �ƴ϶�
	// � �Լ����� �����Ǿ�� �ϴ��� �˷��ִ�, �߻� Ŭ����ȭ
	virtual void Enter() = 0;
	// ������ ���� �� ȣ��
	virtual void Exit() = 0;

public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType)
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}

	// ���� ���� �ȵǰ� ���� �׷� �� ��ü�� �ֵ��� �� (����) + �������� const
	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType]; }
	void DeleteGroup(GROUP_TYPE _eTarget); // �׷� ���� �� �ش� �׷��� ��� ���� ����
	void DeleteAll();
	void DeleteAllException(GROUP_TYPE _eLType, GROUP_TYPE _eRType);
	const vector<CObject*>* GetObjectArr() { return m_arrObj; }

public:
	CScene();
	virtual ~CScene();
};