#include "global.h"
#include "CTexture.h"

#include "CCore.h"

CTexture::CTexture()
	: m_dc(0)
	, m_hBit(0)
	, m_bitInfo{}

{
}

CTexture::~CTexture()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);
}

void CTexture::Load(const wstring& _strRelativePath)
{
	// 인자 경로의 파일을 읽어와서 m_hBit 비트맵 초기화
	m_hBit = (HBITMAP)LoadImage(nullptr, _strRelativePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(m_hBit);

	// 이중 버퍼링용 DC생성
	m_dc = CreateCompatibleDC(CCore::GetInst()->GetMainDC());
	HBITMAP hPreveBlt = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPreveBlt);

	// m_hBlt의 정보를 m_bitInfo 에 저장
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}

void CTexture::Create(UINT _iWidth, UINT _iHeight)
{
	// Alpha Blend 

	HDC mainDC = CCore::GetInst()->GetMainDC();
	//Vec2 vResolution = CCore::GetInst()->GetResolution();

	// 이중 버퍼링용 Bitmap, DC 생성
	m_hBit = CreateCompatibleBitmap(mainDC, (int)_iWidth, (int)_iHeight);
	m_dc = CreateCompatibleDC(mainDC);

	// 생성한 DC의 비트맵을 생성한 비트맵으로 설정
	HBITMAP HOldBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(HOldBit); // 디폴트 비트맵 삭제

	// m_hBlt의 정보를 m_bitInfo 에 저장
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}
