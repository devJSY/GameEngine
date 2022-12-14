#include "global.h"
#include "CAnimator.h"

#include "CAnimation.h"
#include "CTexture.h"

CAnimator::CAnimator()
	: m_pCurAnim(nullptr)
	, m_bRepeat(false)
	, m_pTex(nullptr)
	, m_pRealRender(false)
	, m_IgnoreRGB{ 255, 0, 255 }
{
}
CAnimator::CAnimator(const CAnimator& _origin)
	: m_bRepeat(_origin.m_bRepeat)
	, m_pTex(_origin.m_pTex)
	, m_pRealRender(_origin.m_pRealRender)
	, m_IgnoreRGB{ _origin.m_IgnoreRGB }
{
	LoadAnimation(_origin.m_pTex->GetRelativePath());
}
CAnimator::~CAnimator()
{
	Safe_Delete_Map(m_mapAnim);
}

void CAnimator::CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT iFrameCount)
{
	CAnimation* pAnim = FindAnimation(_strName);
	assert(nullptr == pAnim);					 // 기존에 애니메이션이 있었다면 에러

	pAnim = new CAnimation;
	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;
	pAnim->Create(_pTex, _vLT, _vSliceSize, _vStep, _fDuration, iFrameCount);
	m_pTex = _pTex;

	m_mapAnim.insert(make_pair(_strName, pAnim));
}

void CAnimator::LoadAnimation(const wstring& _strRelativePath)
{
	CAnimation* pAnim = new CAnimation;
	pAnim->Load(_strRelativePath);		// 해당 경로 파일을 Load하여 애니메이션 생성
	pAnim->m_pAnimator = this;

	// 기존에 애니메이션이 존재하지않았다면 추가
	if (nullptr == FindAnimation(pAnim->GetName()))
	{	
		m_mapAnim.insert(make_pair(pAnim->GetName(), pAnim));
	}
	else
	{
		// 기존 애니메이션 삭제 후 새로 생성한 애니메이션으로 변경
		delete m_mapAnim[pAnim->GetName()];
		m_mapAnim[pAnim->GetName()] = pAnim;
	}
}

CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strName);

	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}

void CAnimator::Play(const wstring& _strName, bool _bRepeat, bool _pRealRender)
{
	m_pCurAnim = FindAnimation(_strName);
	assert(nullptr != m_pCurAnim);	// 애니메이션을 찾지 못했음
	m_bRepeat = _bRepeat;
	m_pCurAnim->SetRenderCoordinate(_pRealRender); // 렌더 좌표여부 설정
}

void CAnimator::Component_update()
{
	if (nullptr != m_pCurAnim)
	{
		// 현재 애니메이션의 프레임 설정
		m_pCurAnim->Component_update();

		// 반복 모드 이면서 마지막 프레임이라면 프레임 초기화
		if (m_bRepeat && m_pCurAnim->IsFinish())
		{
			m_pCurAnim->SetFrame(0);
		}
	}
}

void CAnimator::Component_render(HDC _dc)
{
	if (nullptr != m_pCurAnim)
		m_pCurAnim->Component_render(_dc);
}
