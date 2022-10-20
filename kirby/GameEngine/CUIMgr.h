#pragma once

class CUI;

class CUIMgr :
    public CRoot
{
    SINGLE(CUIMgr)
private:
    CUI*     m_pFocusedUI;


public:
	void update();

	void SetFocusedUI(CUI* _pUI);

private:
	// �θ� UI ������ ������ Ÿ���� �� UI �� ã�Ƽ� ��ȯ �Ѵ�.
	CUI* GetFocusedUI();
	CUI* GetTargetedUI(CUI* _pParentUI);
};

