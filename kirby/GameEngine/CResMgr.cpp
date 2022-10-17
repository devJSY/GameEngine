#include "global.h"
#include "CResMgr.h"

#include "CRes.h"
#include "CTexture.h"

#include "CPathMgr.h"

CResMgr::CResMgr()
{}

CResMgr::~CResMgr()
{
	Safe_Delete_Map(m_mapTex);
}

CTexture* CResMgr::LoadTexture(const wstring& _strkey, const wstring& _RelativePath)
{
	CTexture* pTex = FindTexture(_strkey);

	// ������ �ؽ��İ� �־��� ��� ����
	if (nullptr != pTex)
	{
		return pTex;
	}

	// ������ �ؽ��İ� �����ٸ� ���� �����Ͽ� ����
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _RelativePath;

	pTex = new CTexture;
	pTex->Load(strFilePath);
	pTex->SetKey(_strkey);
	pTex->SetRelativePath(_RelativePath);

	m_mapTex.insert(make_pair(_strkey, pTex));

	return pTex;
}

CTexture* CResMgr::FindTexture(const wstring& _strkey)
{
	map<wstring, CRes*>::iterator iter = m_mapTex.find(_strkey);

	if (iter == m_mapTex.end())
	{
		return nullptr;
	}

	return (CTexture*)iter->second;
}

CTexture* CResMgr::CreateTexture(const wstring& _strkey, UINT _iWidth, UINT _iHeight)
{
	CTexture* pTex = FindTexture(_strkey);
	// ������ �־��ٸ� ���� ó��
	assert(nullptr == pTex);

	pTex = new CTexture;
	pTex->Create(_iWidth, _iHeight);
	pTex->SetKey(_strkey);

	m_mapTex.insert(make_pair(_strkey, pTex));

	return pTex;
}
