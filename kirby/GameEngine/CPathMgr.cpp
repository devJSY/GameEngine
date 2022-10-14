#include "global.h"
#include "CPathMgr.h"

CPathMgr::CPathMgr()
	: m_szContentPath{}
{}

CPathMgr::~CPathMgr()
{}

void CPathMgr::init()
{
	// ���� ���α׷� ���� ��� ����
	GetCurrentDirectory(256, m_szContentPath);
	
	// ���ڿ� ���� ����
	int _path = (int)wcslen(m_szContentPath);

	// Kirby ���� ��� ���� �߶󳻱�
	for (int i = _path - 1; 0 <= i; --i)
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	// content ��� �߰�
	wcscat_s(m_szContentPath, 255, L"\\Bulid\\Release\\content");
}

wstring CPathMgr::GetRelativePath(const wchar_t* _filepath)
{
	// ��ü ���� ��ΰ� ���ڷ� ������ ���� �����Ʈ�� �߶󳻼� ��� ��� ��Ʈ�� ��ȯ�ϴ� �Լ�

	wstring strFilePath = _filepath;

	// ���� ��ΰ� ���̰� ����
	size_t iAbslen = wcslen(m_szContentPath);
	// ��ü ��� ���̰� ����
	size_t iFullLen = strFilePath.length();

	// iAbslen - iFullLen ��ġ���� iAbslen ��ŭ �߶� ��ġ ����(��� ��� ��Ʈ)
	wstring strRelativePath = strFilePath.substr(iAbslen, iAbslen - iFullLen);

	return strRelativePath;
}
