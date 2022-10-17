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
	// redner �� Texture ����
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	m_pVeilTex = CResMgr::GetInst()->CreateTexture(L"CameraVeil", (UINT)vResolution.x, (UINT)vResolution.y);
}

void CCamera::update()
{
	if (m_pTargetObj)
	{
		if (m_pTargetObj->IsDead())
		{
			// Dead ���¶�� Ÿ���� ����
			m_pTargetObj = nullptr;
		}
		else
		{
			// ī�޶� ��ġ�� Ÿ�� ������Ʈ ��ġ�� ����
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

	// ���� ī�޾� ��ġ�� ���
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

	// �̺�Ʈ�� ���� ���İ� ����
	if (effect.eEffect == CAM_EFFECT::FADE_OUT)
	{
		iAlpha = (int)(255.f * fRatio);
	}
	else if (effect.eEffect == CAM_EFFECT::FADE_IN)
	{
		iAlpha = (int)(255.f * (1.f - fRatio));
	}

	// AlphaBlend ���ð� ����
	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER; // ������ ��� �̹����� ��ģ�ٴ� �ǹ�
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = iAlpha; // ���� ���İ� ����

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
	//	// ������ �ð��� �����ٸ� �ٷ� ���� ��ġ �� ����
	//	m_vCurLookAt = m_vLookAt;
	//}
	//else
	//{
	//	// ���� ��ġ ���� ������ġ���� ���� ����
	//	Vec2 vDir = m_vLookAt - m_vPrevLookAt;

	//	if (!vDir.IsZero())
	//	{
	//		// ���� ��ġ�� ���⺤�� �������� ������ �ӵ���ŭ ���� ��ġ�� ����
	//		m_vCurLookAt = m_vPrevLookAt + vDir.Normalize() * m_fSpeed * fDT;
	//	}
	//}

	m_vCurLookAt = m_vLookAt;

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2.f;

	// ���� ��ġ���� �ػ� �߽ɱ����� ���̰�
	m_vDiff = m_vCurLookAt - vCenter;

	m_vPrevLookAt = m_vCurLookAt;
}
