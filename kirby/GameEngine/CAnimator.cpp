#include "global.h"
#include "CAnimator.h"

#include "CAnimation.h"
#include "CTexture.h"

CAnimator::CAnimator()
	: m_pCurAnim(nullptr)
	, m_bRepeat(false)
	, m_pTex(nullptr)
	, m_pRealRender(false)
{
}
CAnimator::CAnimator(const CAnimator& _origin)
	: m_bRepeat(_origin.m_bRepeat)
	, m_pTex(_origin.m_pTex)
	, m_pRealRender(_origin.m_pRealRender)
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
	assert(nullptr == pAnim);					 // ������ �ִϸ��̼��� �־��ٸ� ����

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
	pAnim->Load(_strRelativePath);		// �ش� ��� ������ Load�Ͽ� �ִϸ��̼� ����

	// ������ �ִϸ��̼��� ���������ʾҴٸ� �߰�
	if (nullptr == FindAnimation(pAnim->GetName()))
	{
		pAnim->m_pAnimator = this;
		m_mapAnim.insert(make_pair(pAnim->GetName(), pAnim));
	}
	else
	{
		delete pAnim;
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
	assert(nullptr != m_pCurAnim);	// �ִϸ��̼��� ã�� ������
	m_bRepeat = _bRepeat;
	m_pCurAnim->SetRenderCoordinate(_pRealRender); // ���� ��ǥ���� ����
}

void CAnimator::Component_update()
{
	if (nullptr != m_pCurAnim)
	{
		// ���� �ִϸ��̼��� ������ ����
		m_pCurAnim->Component_update();

		// �ݺ� ��� �̸鼭 ������ �������̶�� ������ �ʱ�ȭ
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
