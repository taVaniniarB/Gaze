#include "pch.h"
#include "CScene.h"
#include "CObject.h"
#include "CTile.h"
#include "CResMgr.h"
#include "CPathMgr.h"




CScene::CScene()
	: m_iTileX(0)
	, m_iTileY(0)
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

void CScene::CreateTile(UINT _iXCount, UINT _iYCount)
{
	DeleteGroup(GROUP_TYPE::TILE);

	m_iTileX = _iXCount;
	m_iTileY = _iYCount;


	CTexture* pTileTex = CResMgr::GetInst()->LoadTexture(L"Tile", L"texture\\tile\\tile.bmp");

	// Ÿ�� ����
	for (UINT i = 0; i < _iYCount; ++i)
	{
		for (UINT j = 0; j < _iXCount; ++j)
		{
			CTile* pTile = new CTile();

			pTile->SetTexture(pTileTex);
			pTile->SetPos(Vec2((float)(TILE_SIZE * j), (float)(i * TILE_SIZE)));
			AddObject(pTile, GROUP_TYPE::TILE);
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

// ����� ����ϴ� ����
// �������� Ư�� â ��� �ҷ�������,
// �� enter()���� �����η� ���� �ҷ����� ����� ���� ���� ��
void CScene::LoadTile(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	// Ŀ�� ������Ʈ
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	assert(pFile);

	// Ÿ�� ���μ��� ���� �ҷ�����
	UINT xCount = 0;
	UINT yCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);

	// �ҷ��� ������ �°� EmptyTile�� �����α�
	CreateTile(xCount, yCount);

	// ������� ���� ������ �ʿ��� ���� �ҷ����� ��
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Load(pFile);
	}

	// �� ���Ͽ� ���� ���� ����� �ݱ�
	fclose(pFile);

}