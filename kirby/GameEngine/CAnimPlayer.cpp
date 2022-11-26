#include "global.h"
#include "CAnimPlayer.h"

#include "CAnimator.h"
#include "CCamera.h"

#include "CTimeMgr.h"

CAnimPlayer::CAnimPlayer()
{
	CreateComponents(Component_TYPE::Animator);
}

CAnimPlayer::~CAnimPlayer()
{
}

void CAnimPlayer::start()
{

}

void CAnimPlayer::SetAnimation(const wstring& _strRelativePath, const wstring& _strName, bool _bRepeat)
{
	CAnimator* pAnimator = (CAnimator*)GetComponents(Component_TYPE::Animator);

	pAnimator->LoadAnimation(_strRelativePath);
	pAnimator->Play(_strName, _bRepeat, true);
}
