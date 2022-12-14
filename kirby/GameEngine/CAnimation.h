#pragma once
#include "CRoot.h"

class CAnimator;
class CTexture;

struct tAnimFrm
{
    Vec2 vLT;
    Vec2 vSlice;
    Vec2 vOffset;
    float fDuration;
};

class CAnimation :
	public CRoot
{
private:
	wstring				m_strName;
	CAnimator*			m_pAnimator;
	CTexture*			m_pTex;			// Animation 이 사용하는 텍스쳐
	vector<tAnimFrm>	m_vecFrm;		// 모든 프레임 정보
	int					m_iCurFrm;		// 현재 프레임
	float				m_fAccTime;		// 시간 누적

	bool				m_bFinish;		// 재생 끝에 도달여부
	bool				m_pRealRender;  // 실제 좌표, 렌더링 좌표 여부 1 이면 실제 좌표
	

public:
	const wstring GetName() { return m_strName; }
	bool IsFinish() { return m_bFinish; }
	void SetFrame(int _iFrameIdx)
	{
		m_bFinish = false;
		m_iCurFrm = _iFrameIdx;
		m_fAccTime = 0.f;
	}

	tAnimFrm& GetFrame(int _iIdx) { return m_vecFrm[_iIdx]; }
	UINT GetMaxFrame() { return (UINT)m_vecFrm.size(); }

private:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	void SetRenderCoordinate(bool _pRealRender) { m_pRealRender = _pRealRender; }

public:
	void Save(const wstring& _strRelativePath);
	void Load(const wstring& _strRelativePath);

public:
	void Component_update();
	void Component_render(HDC _dc);
	void Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);

private:
	void SetTexture(CTexture* _pTex) { m_pTex = _pTex; }
	void AddFrameVec(Vec2 _vLT, Vec2 _vSlice, float fDuration);

public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
	friend class CScene_AnimTool;
};

