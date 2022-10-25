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

	// ���� �������� ���ӽð��� ���� ��� 
	if (m_vecFrm[m_iCurFrm].fDuration < m_fAccTime)
	{
		++m_iCurFrm;

		// ���� ó�� �������� ���κп� �����ϰų� �Ѿ���
		if (m_vecFrm.size() <= m_iCurFrm)
		{
			m_iCurFrm = -1;
			m_bFinish = true;
			m_fAccTime = 0.f;
			return;
		}

		// ���� �ð��� ���������ӿ��� �ʰ��� �ð���ŭ�� ���� ����
		m_fAccTime = m_fAccTime - m_vecFrm[m_iCurFrm].fDuration;
	}
}

void CAnimation::Component_render(HDC _dc)
{
	if (m_bFinish)
		return;

	CObject* pObj = m_pAnimator->GetOwner();
	Vec2 vPos = pObj->GetPos();
	vPos += m_vecFrm[m_iCurFrm].vOffset; // Object Position �� Offset ��ŭ �߰� �̵� ��ġ

	if (!m_pRealRender)
	{
		// ������ ��ǥ�� ��ȯ
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	}

	TransparentBlt(_dc
		, (int)(vPos.x - m_vecFrm[m_iCurFrm].vSlice.x / 2.f)	// �»�� x ��ġ
		, (int)(vPos.y - m_vecFrm[m_iCurFrm].vSlice.y / 2.f)	// �»�� y ��ġ 
		, (int)(m_vecFrm[m_iCurFrm].vSlice.x)					// �ؽ��� ����
		, (int)(m_vecFrm[m_iCurFrm].vSlice.y)					// �ؽ��� ����
		, m_pTex->GetDC()										// �׷��� DC
		, (int)(m_vecFrm[m_iCurFrm].vLT.x)						// ������ x ��ġ
		, (int)(m_vecFrm[m_iCurFrm].vLT.y)						// ������ y ��ġ	
		, (int)(m_vecFrm[m_iCurFrm].vSlice.x)					// �»�����κ����� ���̰� x
		, (int)(m_vecFrm[m_iCurFrm].vSlice.y)					// �»�����κ����� ���̰� y
		, RGB(255, 0, 255)										// ������ RGB ����
	);
}

void CAnimation::Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	// �ؽ��� ����
	m_pTex = _pTex;

	// �� �����ӿ� �´� ������ ������ vector �� ����
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
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");	// ���� ��Ʈ�� wb ������� ����
	assert(pFile);

	// Animation �� �̸��� �����Ѵ�.(������ ����ȭ)
	fprintf(pFile, "[Animation Name]\n");
	string strName = string(m_strName.begin(), m_strName.end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	// Animation �� ����ϴ� �ؽ���
	fprintf(pFile, "[Texture Name]\n");
	strName = string(m_pTex->GetKey().begin(), m_pTex->GetKey().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	fprintf(pFile, "[Texture Path]\n");
	strName = string(m_pTex->GetRelativePath().begin(), m_pTex->GetRelativePath().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	// ������ ����
	fprintf(pFile, "[Frame Count]\n");
	fprintf(pFile, "%d\n", (int)m_vecFrm.size());

	// ��� ������ ����
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

	fclose(pFile);	// ���� ��Ʈ�� ����
}

void CAnimation::Load(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");	// ���� ��Ʈ�� rb ������� ����
	assert(pFile);

	// Animation �� �̸��� �о�´�.
	string str;
	char szBuff[256] = {};

	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);
	str = szBuff;

	m_strName = wstring(str.begin(), str.end());

	// �����ϴ� �ؽ��� �̸� �� ���
	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);

	str = szBuff;
	wstring strTexKey = wstring(str.begin(), str.end());

	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);

	str = szBuff;
	wstring strResPath = wstring(str.begin(), str.end());

	m_pTex = CResMgr::GetInst()->LoadTexture(strTexKey, strResPath);

	// ������ ����
	FScanf(szBuff, pFile);
	int iFameCount = 0;
	fscanf_s(pFile, "%d", &iFameCount);

	// ��� ������ ����
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

	fclose(pFile); // ���� ��Ʈ�� ����
}
