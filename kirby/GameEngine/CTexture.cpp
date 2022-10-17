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
	// ���� ����� ������ �о�ͼ� m_hBit ��Ʈ�� �ʱ�ȭ
	m_hBit = (HBITMAP)LoadImage(nullptr, _strRelativePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(m_hBit);

	// ���� ���۸��� DC����
	m_dc = CreateCompatibleDC(CCore::GetInst()->GetMainDC());
	HBITMAP hPreveBlt = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPreveBlt);

	// m_hBlt�� ������ m_bitInfo �� ����
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}

void CTexture::Create(UINT _iWidth, UINT _iHeight)
{
	// Alpha Blend 

	HDC mainDC = CCore::GetInst()->GetMainDC();
	//Vec2 vResolution = CCore::GetInst()->GetResolution();

	// ���� ���۸��� Bitmap, DC ����
	m_hBit = CreateCompatibleBitmap(mainDC, (int)_iWidth, (int)_iHeight);
	m_dc = CreateCompatibleDC(mainDC);

	// ������ DC�� ��Ʈ���� ������ ��Ʈ������ ����
	HBITMAP HOldBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(HOldBit); // ����Ʈ ��Ʈ�� ����

	// m_hBlt�� ������ m_bitInfo �� ����
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}
