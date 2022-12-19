#include "global.h"
#include "CCamera.h"

#include "CCore.h"
#include "CObject.h"
#include "CTexture.h"
#include "CScene.h"
#include "CScene_AnimTool.h"
#include "CScene_SceneTool.h"
#include "CScene_Stage.h"
#include "CAnimation.h"

#include "CResMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CSceneMgr.h"


CCamera::CCamera()
	: m_pTargetObj(nullptr)
	, m_fMoveSpeed(0.f)
	, m_pVeilTex(nullptr)
{
}


CCamera::~CCamera()
{}

void CCamera::init()
{
	// render 용 Texture 생성
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	m_pVeilTex = CResMgr::GetInst()->CreateTexture(L"CameraVeil", (UINT)vResolution.x, (UINT)vResolution.y);
}

void CCamera::update()
{
	// CScene_AnimTool 텍스쳐 이동 제한
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	if(L"Animation_Tool" == pCurScene->GetName())
	{
		CTexture* SceneTex = ((CScene_AnimTool*)pCurScene)->GetTexture();	
		UINT TexWidth = SceneTex->Width();
		UINT TexHeight = SceneTex->Height();
	
		if (nullptr != SceneTex)
		{
			Vec2 vResolution = CCore::GetInst()->GetResolution();
			Vec2 vLT = m_vLookAt - vResolution / 2.f;

			// x Axis Left Move Limit
			if (vLT.x > 0)
			{
				if (KEY_HOLD(KEY::A))
					m_vLookAt.x -= m_fMoveSpeed * fDT;
			}

			// x Axis right Move Limit
			if (vLT.x < (TexWidth - vResolution.x))
			{
				if (KEY_HOLD(KEY::D))
					m_vLookAt.x += m_fMoveSpeed * fDT;
			}

			// y Axis top Move Limit
			if (vLT.y > 0)
			{
				if (KEY_HOLD(KEY::W))
					m_vLookAt.y -= m_fMoveSpeed * fDT;
			}

			// y Axis bottom Move Limit
			if (vLT.y < (TexHeight - vResolution.y))
			{
				if (KEY_HOLD(KEY::S))
					m_vLookAt.y += m_fMoveSpeed * fDT;
			}
		}
	}
	else if (L"Scene_Tool" == pCurScene->GetName())
	{
		CTexture* SceneTex = ((CScene_SceneTool*)pCurScene)->GetForeGroundTex();

		if (nullptr != SceneTex)
		{
			// =========
			// 이동 제한 
			// =========
			  
			tAnimFrm tAnim = ((CScene_SceneTool*)pCurScene)->GetForeGroundAnim()->GetFrame(0);

			UINT iWidth = (UINT)tAnim.vSlice.x;
			UINT iHeight = (UINT)tAnim.vSlice.y;

			Vec2 vResolution = CCore::GetInst()->GetResolution();
			Vec2 vLT = m_vLookAt - vResolution / 2.f;

			// x Axis Left Move Limit
			if (vLT.x > 0)
			{
				if (KEY_HOLD(KEY::A))
					m_vLookAt.x -= m_fMoveSpeed * fDT;
			}

			// x Axis right Move Limit
			if (vLT.x < (iWidth - vResolution.x))
			{
				if (KEY_HOLD(KEY::D))
					m_vLookAt.x += m_fMoveSpeed * fDT;
			}

			// y Axis top Move Limit
			if (vLT.y > 0)
			{
				if (KEY_HOLD(KEY::W))
					m_vLookAt.y -= m_fMoveSpeed * fDT;
			}

			// y Axis bottom Move Limit
			if (vLT.y < (iHeight - vResolution.y))
			{
				if (KEY_HOLD(KEY::S))
					m_vLookAt.y += m_fMoveSpeed * fDT;
			}

			//if (KEY_HOLD(KEY::A))
			//	m_vLookAt.x -= m_fMoveSpeed * fDT;
			//if (KEY_HOLD(KEY::D))
			//	m_vLookAt.x += m_fMoveSpeed * fDT;
			//if (KEY_HOLD(KEY::W))
			//	m_vLookAt.y -= m_fMoveSpeed * fDT;
			//if (KEY_HOLD(KEY::S))
			//	m_vLookAt.y += m_fMoveSpeed * fDT;
		}
	}
	else if (L"StartScene" == pCurScene->GetName())
	{
	}
	else 
	{
		// Stage Scene 카메라 설정

		Vec2 vResolution = CCore::GetInst()->GetResolution();

		tAnimFrm tAnim = ((CScene_Stage*)pCurScene)->GetForeGroundAnim()->GetFrame(0);

		UINT iWidth = (UINT)tAnim.vSlice.x;
		UINT iHeight = (UINT)tAnim.vSlice.y;

		if (m_pTargetObj)
		{
			if (m_pTargetObj->IsDead())
			{
				// Dead 상태라면 타겟팅 해제
				m_pTargetObj = nullptr;
			}
			else
			{
				if (L"Stage_01" == pCurScene->GetName() || L"Stage_02" == pCurScene->GetName()
					|| L"Stage_04" == pCurScene->GetName() || L"Stage_06" == pCurScene->GetName())
				{
					// 카메라 위치를 타켓 오브젝트 위치로 설정
					m_vLookAt.x = m_pTargetObj->GetPos().x;
					m_vLookAt.y = vResolution.y / 2.f;
				}
				else if (L"Stage_03" == pCurScene->GetName() || L"Stage_05" == pCurScene->GetName())
				{
					// 카메라 위치를 타켓 오브젝트 위치로 설정
					m_vLookAt.x = vResolution.x / 2.f;
					m_vLookAt.y = m_pTargetObj->GetPos().y;
				}

				// 테스트 용 코드
				if (L"Test1" == pCurScene->GetName())
				{
					// 카메라 위치를 타켓 오브젝트 위치로 설정
					m_vLookAt.x = m_pTargetObj->GetPos().x;
					m_vLookAt.y = vResolution.y / 2.f;
				}
				else if (L"Test2" == pCurScene->GetName())
				{
					// 카메라 위치를 타켓 오브젝트 위치로 설정
					m_vLookAt.x = vResolution.x / 2.f;
					m_vLookAt.y = m_pTargetObj->GetPos().y;
				}


				// 카메라 이동 제한
				if (m_vLookAt.x < vResolution.x / 2.f)
				{
					m_vLookAt.x = vResolution.x / 2.f;
				}

				if (m_vLookAt.y < vResolution.y / 2.f)
				{
					m_vLookAt.y = vResolution.y / 2.f;
				}

				if (m_vLookAt.x > iWidth - vResolution.x / 2.f)
				{
					m_vLookAt.x = iWidth - vResolution.x / 2.f;
				}

				if (m_vLookAt.y > iHeight - vResolution.y / 2.f)
				{
					m_vLookAt.y = iHeight - vResolution.y / 2.f;
				}
			}
		}
	}	

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
	m_vCurLookAt = m_vLookAt;

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2.f;

	// 현재 위치부터 해상도 중심까지의 차이값
	m_vDiff = m_vCurLookAt - vCenter;

	m_vPrevLookAt = m_vCurLookAt;
}
