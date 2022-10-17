#include "global.h"
#include "CCamera.h"

#include "CCore.h"
#include "CObject.h"
#include "CTexture.h"

#include "CResMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"


CCamera::CCamera()
	: m_pTargetObj(nullptr)
	, m_fTime(0.5f)
	, m_fSpeed(0.f)
	, m_fAccTime(0.5f)
	, m_pVeilTex(nullptr)
{
}


CCamera::~CCamera()
{}

void CCamera::init()
{
	// redner 용 Texture 생성
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	m_pVeilTex = CResMgr::GetInst()->CreateTexture(L"CameraVeil", (UINT)vResolution.x, (UINT)vResolution.y);
}

void CCamera::update()
{
	if (m_pTargetObj)
	{
		if (m_pTargetObj->IsDead())
		{
			// Dead 상태라면 타겟팅 해제
			m_pTargetObj = nullptr;
		}
		else
		{
			// 카메라 위치를 타켓 오브젝트 위치로 설정
			m_vLookAt = m_pTargetObj->GetPos();
		}
	}

	if (KEY_HOLD(KEY::W))
		m_vLookAt.y -= 500.f * fDT;
	if (KEY_HOLD(KEY::S))
		m_vLookAt.y += 500.f * fDT;
	if (KEY_HOLD(KEY::A))
		m_vLookAt.x -= 500.f * fDT;
	if (KEY_HOLD(KEY::D))
		m_vLookAt.x += 500.f * fDT;

	// 현재 카메아 위치값 계산
	CalDiff();
}

void CCamera::render(HDC _dc)
{
	if (m_listCamEffect.empty())
		return;

	tCamEffect& effect = m_listCamEffect.front();

	effect.fCurTime += fDT;

	float fRatio = effect.fCurTime / effect.fDuration;

	if (fRatio < 0.f)
		fRatio = 0.f;
	if (fRatio > 1.f)
		fRatio = 1.f;

	int iAlpha = 0;

	// 이벤트에 따라 알파값 설정
	if (effect.eEffect == CAM_EFFECT::FADE_OUT)
	{
		iAlpha = (int)(255.f * fRatio);
	}
	else if (effect.eEffect == CAM_EFFECT::FADE_IN)
	{
		iAlpha = (int)(255.f * (1.f - fRatio));
	}

	// AlphaBlend 셋팅값 설정
	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER; // 원본과 대상 이미지를 합친다는 의미
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = iAlpha; // 고정 알파값 설정

	AlphaBlend(_dc,
		0, 0
		, (int)m_pVeilTex->Width()
		, (int)m_pVeilTex->Height()
		, m_pVeilTex->GetDC()
		, 0, 0
		, (int)m_pVeilTex->Width()
		, (int)m_pVeilTex->Height()
		, bf);

	if (effect.fCurTime > effect.fDuration)
	{
		effect.eEffect = CAM_EFFECT::NONE;
		m_listCamEffect.pop_front();
	}
}

void CCamera::CalDiff()
{
	//m_fAccTime += fDT;

	//if (m_fTime <= m_fAccTime)
	//{
	//	// 설정한 시간이 지났다면 바로 현재 위치 로 설정
	//	m_vCurLookAt = m_vLookAt;
	//}
	//else
	//{
	//	// 이전 위치 에서 현재위치로의 방향 벡터
	//	Vec2 vDir = m_vLookAt - m_vPrevLookAt;

	//	if (!vDir.IsZero())
	//	{
	//		// 이전 위치에 방향벡터 방향으로 설정한 속도만큼 현재 위치를 결정
	//		m_vCurLookAt = m_vPrevLookAt + vDir.Normalize() * m_fSpeed * fDT;
	//	}
	//}

	m_vCurLookAt = m_vLookAt;

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2.f;

	// 현재 위치부터 해상도 중심까지의 차이값
	m_vDiff = m_vCurLookAt - vCenter;

	m_vPrevLookAt = m_vCurLookAt;
}
