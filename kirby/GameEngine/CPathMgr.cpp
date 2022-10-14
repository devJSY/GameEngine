#include "global.h"
#include "CPathMgr.h"

CPathMgr::CPathMgr()
	: m_szContentPath{}
{}

CPathMgr::~CPathMgr()
{}

void CPathMgr::init()
{
	// 현재 프로그램 실행 경로 저장
	GetCurrentDirectory(256, m_szContentPath);
	
	// 문자열 길이 저장
	int _path = (int)wcslen(m_szContentPath);

	// Kirby 파일 경로 까지 잘라내기
	for (int i = _path - 1; 0 <= i; --i)
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	// content 경로 추가
	wcscat_s(m_szContentPath, 255, L"\\Bulid\\Release\\content");
}

wstring CPathMgr::GetRelativePath(const wchar_t* _filepath)
{
	// 전체 파일 경로가 인자로 들어오면 절대 경로파트를 잘라내서 상대 경로 파트를 반환하는 함수

	wstring strFilePath = _filepath;

	// 절대 경로값 길이값 저장
	size_t iAbslen = wcslen(m_szContentPath);
	// 전체 경로 길이값 저장
	size_t iFullLen = strFilePath.length();

	// iAbslen - iFullLen 위치부터 iAbslen 만큼 잘라낸 위치 저장(상대 경로 파트)
	wstring strRelativePath = strFilePath.substr(iAbslen, iAbslen - iFullLen);

	return strRelativePath;
}
