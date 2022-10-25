#include "global.h"

#include "CAnimation.h"
#include "CAnimator.h"
#include "CObject.h"
#include "CTexture.h"

#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CResMgr.h"

CAnimation::CAnimation()
	: m_pAnimator(nullptr)
	, m_pTex(nullptr)
	, m_iCurFrm(0)
	, m_fAccTime(0.f)
	, m_bFinish(false)
	, m_pRealRender(false)
{
}
CAnimation::~CAnimation()
{
}

void CAnimation::Component_update()
{
	if (m_bFinish)
		return;

	m_fAccTime += fDT;

	// 현재 프레임의 지속시간이 지난 경우 
	if (m_vecFrm[m_iCurFrm].fDuration < m_fAccTime)
	{
		++m_iCurFrm;

		// 예외 처리 프레임의 끝부분에 도달하거나 넘어선경우
		if (m_vecFrm.size() <= m_iCurFrm)
		{
			m_iCurFrm = -1;
			m_bFinish = true;
			m_fAccTime = 0.f;
			return;
		}

		// 현재 시간을 이전프레임에서 초과된 시간만큼을 빼서 설정
		m_fAccTime = m_fAccTime - m_vecFrm[m_iCurFrm].fDuration;
	}
}

void CAnimation::Component_render(HDC _dc)
{
	if (m_bFinish)
		return;

	CObject* pObj = m_pAnimator->GetOwner();
	Vec2 vPos = pObj->GetPos();
	vPos += m_vecFrm[m_iCurFrm].vOffset; // Object Position 에 Offset 만큼 추가 이동 위치

	if (!m_pRealRender)
	{
		// 렌더링 좌표로 변환
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	}

	TransparentBlt(_dc
		, (int)(vPos.x - m_vecFrm[m_iCurFrm].vSlice.x / 2.f)	// 좌상단 x 위치
		, (int)(vPos.y - m_vecFrm[m_iCurFrm].vSlice.y / 2.f)	// 좌상단 y 위치 
		, (int)(m_vecFrm[m_iCurFrm].vSlice.x)					// 텍스쳐 가로
		, (int)(m_vecFrm[m_iCurFrm].vSlice.y)					// 텍스쳐 세로
		, m_pTex->GetDC()										// 그려질 DC
		, (int)(m_vecFrm[m_iCurFrm].vLT.x)						// 복사할 x 위치
		, (int)(m_vecFrm[m_iCurFrm].vLT.y)						// 복사할 y 위치	
		, (int)(m_vecFrm[m_iCurFrm].vSlice.x)					// 좌상단으로부터의 길이값 x
		, (int)(m_vecFrm[m_iCurFrm].vSlice.y)					// 좌상단으로부터의 길이값 y
		, RGB(255, 0, 255)										// 무시할 RGB 색상
	);
}

void CAnimation::Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	// 텍스쳐 셋팅
	m_pTex = _pTex;

	// 각 프레임에 맞는 데이터 설정후 vector 에 저장
	tAnimFrm frm = {};

	for (UINT i = 0; i < _iFrameCount; ++i)
	{
		frm.fDuration = _fDuration;
		frm.vSlice = _vSliceSize;
		frm.vLT = _vLT + (_vStep * (float)i);
		
		m_vecFrm.push_back(frm);
	}
}

void CAnimation::Save(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");	// 파일 스트림 wb 방식으로 열기
	assert(pFile);

	// Animation 의 이름을 저장한다.(데이터 직렬화)
	fprintf(pFile, "[Animation Name]\n");
	string strName = string(m_strName.begin(), m_strName.end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	// Animation 이 사용하는 텍스쳐
	fprintf(pFile, "[Texture Name]\n");
	strName = string(m_pTex->GetKey().begin(), m_pTex->GetKey().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	fprintf(pFile, "[Texture Path]\n");
	strName = string(m_pTex->GetRelativePath().begin(), m_pTex->GetRelativePath().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	// 프레임 개수
	fprintf(pFile, "[Frame Count]\n");
	fprintf(pFile, "%d\n", (int)m_vecFrm.size());

	// 모든 프레임 정보
	for (size_t i = 0; i < m_vecFrm.size(); ++i)
	{
		fprintf(pFile, "[Frame Index]\n");
		fprintf(pFile, "%d\n", (int)i);

		fprintf(pFile, "[Left Top]\n");
		fprintf(pFile, "%d %d\n", (int)m_vecFrm[i].vLT.x, (int)m_vecFrm[i].vLT.y);

		fprintf(pFile, "[Slice Size]\n");
		fprintf(pFile, "%d %d\n", (int)m_vecFrm[i].vSlice.x, (int)m_vecFrm[i].vSlice.y);

		fprintf(pFile, "[Offset]\n");
		fprintf(pFile, "%d %d\n", (int)m_vecFrm[i].vOffset.x, (int)m_vecFrm[i].vOffset.y);

		fprintf(pFile, "[Duration]\n");
		fprintf(pFile, "%f\n", m_vecFrm[i].fDuration);

		fprintf(pFile, "\n\n");
	}

	fclose(pFile);	// 파일 스트림 종료
}

void CAnimation::Load(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");	// 파일 스트림 rb 방식으로 오픈
	assert(pFile);

	// Animation 의 이름을 읽어온다.
	string str;
	char szBuff[256] = {};

	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);
	str = szBuff;

	m_strName = wstring(str.begin(), str.end());

	// 참조하는 텍스쳐 이름 및 경로
	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);

	str = szBuff;
	wstring strTexKey = wstring(str.begin(), str.end());

	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);

	str = szBuff;
	wstring strResPath = wstring(str.begin(), str.end());

	m_pTex = CResMgr::GetInst()->LoadTexture(strTexKey, strResPath);

	// 프레임 개수
	FScanf(szBuff, pFile);
	int iFameCount = 0;
	fscanf_s(pFile, "%d", &iFameCount);

	// 모든 프레임 정보
	tAnimFrm frm = {};
	for (int i = 0; i < iFameCount; ++i)
	{
		POINT pt = {};

		while (true)
		{
			FScanf(szBuff, pFile);

			if (!strcmp("[Frame Index]", szBuff))
			{
				fscanf_s(pFile, "%d", &pt.x);
			}
			else if (!strcmp("[Left Top]", szBuff))
			{
				fscanf_s(pFile, "%d", &pt.x);
				fscanf_s(pFile, "%d", &pt.y);

				frm.vLT = pt;
			}
			else if (!strcmp("[Slice Size]", szBuff))
			{
				fscanf_s(pFile, "%d", &pt.x);
				fscanf_s(pFile, "%d", &pt.y);

				frm.vSlice = pt;
			}
			else if (!strcmp("[Offset]", szBuff))
			{
				fscanf_s(pFile, "%d", &pt.x);
				fscanf_s(pFile, "%d", &pt.y);

				frm.vOffset = pt;
			}
			else if (!strcmp("[Duration]", szBuff))
			{
				fscanf_s(pFile, "%f", &frm.fDuration);
				break;
			}
		}

		m_vecFrm.push_back(frm);
	}

	fclose(pFile); // 파일 스트림 종료
}
