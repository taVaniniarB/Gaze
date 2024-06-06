#include "pch.h"
#include "CScene.h"
#include "CObject.h"




CScene::CScene()
{
}

// ����: ���� ����̹Ƿ�, ���� �Ҹ��� �� �ڵ����� �����
// ��ü: ���Ϳ��� �����Ҵ� �� ��ü���� "�ּ�"�� �����Ŷ� ���� ���� ���� ���� ���־�� ��
// ��ü����ü�� �־����� ���������ٵ�. �ּҸ� �����ѰŴϱ�, �������� �����߸�...
// ���� �ȿ� ���Ű� ������ �ַ��ַ��ѵ� ������ ���شٰ� ���Ű� ������� ����!
CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			// m_arrObj[i] �׷� ������ j ��ü ����
			delete m_arrObj[i][j];
		}
	}
}


void CScene::update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			if (!m_arrObj[i][j]->IsDead())
			{
				m_arrObj[i][j]->update();
			}
		}
	}
}

void CScene::finalUpdate()
{ // �۾��� ���������ִ� (Ȯ�������ִ�) ������Ʈ
	// �浹ü�� ������Ʈ�� ���󰡰� �Ѵ�
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			// Dead ��ü��
			// ����ü�� ���, ������ �۾� �ʿ��ϱ� ������ final update������ �����ش�
			m_arrObj[i][j]->finalUpdate();
		}
	}
}

void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		// earse �Լ� ���� ���� operator(i, j...) ���� ���� �ʰ�
		// iterator ����

		vector<CObject*>::iterator iter = m_arrObj[i].begin();

		for (; iter != m_arrObj[i].end();)
		{
			if (!(*iter)->IsDead())
			{
				(*iter)->render(_dc);
				++iter;

			}
			else
			{
				iter = m_arrObj[i].erase(iter); //���Ϳ��� ������ ���� �Ŀ� �� ���� ���� �޴� �� ���
			}
		}
	}
}

void CScene::DeleteGroup(GROUP_TYPE _eTarget)
{
	Safe_Delete_Vec<CObject*>(m_arrObj[(UINT)_eTarget]);
}

void CScene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}

void CScene::DeleteAllException(GROUP_TYPE _eLType, GROUP_TYPE _eRType)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		if ((UINT)_eLType != i && (UINT)_eRType != i)
			DeleteGroup((GROUP_TYPE)i);
	}
}