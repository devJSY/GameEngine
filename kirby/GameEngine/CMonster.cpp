#include "global.h"
#include "CMonster.h"

#include "CCore.h"
#include "CCollider.h"
#include "CTexture.h"
#include "AI.h"

#include "CResMgr.h"

CMonster::CMonster()
	: m_tInfo{}
{
	// ================
	// Collider Create
	// ================ 
	CreateComponents(Component_TYPE::Collider);

	// ================
	// Rigidbody Create
	// ================ 
	CreateComponents(Component_TYPE::RigidBody);


	// ================
	// Gravity Create
	// ================ 
	CreateComponents(Component_TYPE::Gravity);
}

CMonster::~CMonster()
{	
	if (nullptr != m_pAI)
		delete m_pAI;
}

void CMonster::update()
{
	if (nullptr != m_pAI)
		m_pAI->update();
}

void CMonster::render(HDC _dc)
{
	//int iWidth = m_pTex->Width();
	//int iHeight = m_pTex->Height();

	//Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	//TransparentBlt(_dc
	//	, int(vPos.x - (float)(iWidth / 2))
	//	, int(vPos.y - (float)(iHeight / 2))
	//	, iWidth, iHeight
	//	, m_pTex->GetDC()
	//	, 0, 0, iWidth, iHeight
	//	, RGB(255, 0, 255));

	Component_render(_dc);
}


void CMonster::start()
{
	CCollider* pCollider = ((CCollider*)GetComponents(Component_TYPE::Collider));
	pCollider->SetScale(GetScale());
}