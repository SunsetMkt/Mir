// �ִ� ��ư�� ��

#include "stdafx.h"
#define MAX_TXT_BUTTON_COUNT	5

/////////////////////////////////////////////////////////////////////////
//	CTextButton : ������
/////////////////////////////////////////////////////////////////////////
CTextButton::CTextButton()
{
	m_pTxtBtn.ClearAllNodes();
	m_nTxtHeight = 0;
	m_nMaxLine = 0;
	m_bIsReady = FALSE;
	m_IsUseSubTxt = FALSE;
}

/////////////////////////////////////////////////////////////////////////
//	~CTextButton : �Ҹ���
/////////////////////////////////////////////////////////////////////////
CTextButton::~CTextButton()
{
	ReleaseButtons();
}

/////////////////////////////////////////////////////////////////////////
//	AddButton : Text ��ư�� �߰��Ѵ�.
/////////////////////////////////////////////////////////////////////////
// pszTxt: ȭ�鿡 ǥ�õ� Text
// xRect: ��ư���� �νĵ� Rect ����
// nLinePos: �������� Line Count
// pszParam: Ŭ�� �Ǿ����� ���� Parameter��
/////////////////////////////////////////////////////////////////////////
BOOL	CTextButton::AddButton(CHAR *pszTxt,RECT xRect,INT nLinePos,CHAR *pszParam,COLORREF nColor,COLORREF cColor)
{
	if(m_bIsReady)
	{
		SIZE tSize;
		CMTxtBtn* tCMTxtBtn;
		tCMTxtBtn = new  CMTxtBtn;
		tSize = g_xMainWnd.GetStrLength(NULL,NULL,pszTxt);
		m_nTxtHeight  = tSize.cy;
		strcpy(tCMTxtBtn->Txt,pszTxt);
		tCMTxtBtn->xRect = xRect;
		tCMTxtBtn->nLinePos = nLinePos;
		strcpy(tCMTxtBtn->Param,pszParam);
		tCMTxtBtn->bIsClicked = FALSE;
		tCMTxtBtn->nColor = nColor;
		tCMTxtBtn->cColor = cColor;
		m_pTxtBtn.AddNode(tCMTxtBtn);
		return TRUE;
	}
	else 
		return FALSE;
}

BOOL	CTextButton::AddButton(CHAR *pszTxt,CHAR *pszTxt2,RECT xRect,INT nLinePos,CHAR *pszParam,COLORREF nColor,COLORREF cColor)
{
	if(m_bIsReady)
	{
		SIZE tSize;
		CMTxtBtn* tCMTxtBtn;
		tCMTxtBtn = new  CMTxtBtn;
		tSize = g_xMainWnd.GetStrLength(NULL,NULL,pszTxt);
		m_nTxtHeight  = tSize.cy;

		strcpy(tCMTxtBtn->Txt,pszTxt);
		strcpy(tCMTxtBtn->sTxt,pszTxt2);

		tCMTxtBtn->xRect = xRect;
		tCMTxtBtn->nLinePos = nLinePos;

		strcpy(tCMTxtBtn->Param,pszParam);
		tCMTxtBtn->bIsClicked = FALSE;
		tCMTxtBtn->nColor = nColor;
		tCMTxtBtn->cColor = cColor;

		m_pTxtBtn.AddNode(tCMTxtBtn);
		m_IsUseSubTxt = TRUE;
		return TRUE;
	}
	else 
		return FALSE;
}

/////////////////////////////////////////////////////////////////////////
//	ClickCheck : Button Click �� ���� Click Checking �� �Ѵ�.
/////////////////////////////////////////////////////////////////////////
// xPos: ���� ���콺 ��ǥ�� �޾� �ð�
// xWndPos: ���� Text�� ���̱� ���� �ϴ� ���� ��ǥ�� �޾� �ð�
// CurrentTopLine: ���� Window �� ������ ���� ����
/////////////////////////////////////////////////////////////////////////
CMTxtBtn*	CTextButton::ClickCheck(POINT xWndPos,POINT	xPos,INT CurrentTopLine)
{
	if(m_bIsReady)
	{
		m_pTxtBtn.MoveCurrentToTop();
		for(int i = 0; i<m_pTxtBtn.ListLength();i++)
		{
			if((m_pTxtBtn.GetCurrentData()->nLinePos >= CurrentTopLine) && (m_pTxtBtn.GetCurrentData()->nLinePos <= CurrentTopLine+m_nMaxLine))
			{
				if(IsCurrsorOnThisButton(m_pTxtBtn.GetCurrentData(),xWndPos,xPos,CurrentTopLine))
				{
					m_pTxtBtn.GetCurrentData()->bIsClicked = !m_pTxtBtn.GetCurrentData()->bIsClicked;
					return m_pTxtBtn.GetCurrentData();
				}
			}
			m_pTxtBtn.MoveNextNode();
		}
	}
	return NULL;
}

/////////////////////////////////////////////////////////////////////////
//	ReleaseButtons : �̹� ���� �ִ� ��� ��ư���� ������.
/////////////////////////////////////////////////////////////////////////
BOOL CTextButton::ReleaseButtons(VOID)
{
	if(m_bIsReady)
	{
		m_pTxtBtn.ClearAllNodes();
//		m_bIsReady = FALSE;
		m_nTxtHeight = 0;
		return TRUE;
	}
	else
		return FALSE;
}

/////////////////////////////////////////////////////////////////////////
//	InitTxtBtn : �� Ŭ������ ��� �Ҽ� �ֵ��� �غ� �Ѵ�.
/////////////////////////////////////////////////////////////////////////
// nTextHeight: ���� Text�� Height  
// WndRect: �������� ũ��  
// nMaxLine: ������ �ִ� �ִ� ���μ�
/////////////////////////////////////////////////////////////////////////
BOOL CTextButton::InitTxtBtn(INT nMaxLine,POINT StartPos,INT nLineGap)
{
	m_bIsReady = TRUE;
	m_nMaxLine = nMaxLine;
	m_xStartPos = StartPos;
	m_nLineGap = nLineGap;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////
//	GetButton : �ش� Button�� �����͸� ��´�.
/////////////////////////////////////////////////////////////////////////
// nIndex : Index
/////////////////////////////////////////////////////////////////////////
CMTxtBtn* CTextButton::GetButton(INT nIndex)
{
	if(nIndex<0 || nIndex>m_pTxtBtn.GetCounter()) return NULL;
	m_pTxtBtn.MoveCurrentToTop();
	m_pTxtBtn.MoveNode(nIndex);
	return m_pTxtBtn.GetCurrentData();
}

/////////////////////////////////////////////////////////////////////////
//	GetButtonCount : Button�� ���� ��´�.
/////////////////////////////////////////////////////////////////////////
INT CTextButton::GetButtonCount(VOID)
{
	return m_pTxtBtn.GetCounter();
}

VOID CTextButton::ClickFreeAllBtn(VOID)
{
	m_pTxtBtn.MoveCurrentToTop();
	for(int i = 0 ; i < m_pTxtBtn.GetCounter() ; i++)
	{
		m_pTxtBtn.GetCurrentData()->bIsClicked = FALSE;
		m_pTxtBtn.MoveNextNode();
	}
}

/////////////////////////////////////////////////////////////////////////
//	ClickCheck : Button Click �� ���� Click Checking �� �Ѵ�.
/////////////////////////////////////////////////////////////////////////
// xPos: ���� ���콺 ��ǥ�� �޾� �ð�
// xWndPos: ���� Text�� ���̱� ���� �ϴ� ���� ��ǥ�� �޾� �ð�
// CurrentTopLine: ���� Window �� ������ ���� ����
/////////////////////////////////////////////////////////////////////////


CMTxtBtn* CTextButton::ButtonDownCheck(POINT xWndPos,POINT xPos,INT CurrentTopLine)
{
///	CMTxtBtn*	xResult=NULL;
/*	int			nTempX,nTempY;
	int			StdPosX,StdPosY;	// �����̴� �����쳻���� ���� ���� ��� �Ѵ�.*/
	
	if(m_bIsReady)
	{
		m_pTxtBtn.MoveCurrentToTop();
		for(int i = 0; i<m_pTxtBtn.ListLength();i++)
		{
			if((m_pTxtBtn.GetCurrentData()->nLinePos >= CurrentTopLine) && (m_pTxtBtn.GetCurrentData()->nLinePos <= CurrentTopLine+m_nMaxLine))
			{
				if(IsCurrsorOnThisButton(m_pTxtBtn.GetCurrentData(),xWndPos,xPos,CurrentTopLine))
				{
					m_pTxtBtn.GetCurrentData()->bIsClicked = TRUE; 
					return m_pTxtBtn.GetCurrentData();
				}
				m_pTxtBtn.GetCurrentData()->bIsClicked = FALSE;
			}
			m_pTxtBtn.MoveNextNode();
		}
	}
	return NULL;
}


CMTxtBtn* CTextButton::ButtonUpCheck(POINT xWndPos,POINT xPos,INT CurrentTopLine)
{	
	if(m_bIsReady)
	{
		m_pTxtBtn.MoveCurrentToTop();
		for(int i = 0; i<m_pTxtBtn.ListLength();i++)
		{
			if((m_pTxtBtn.GetCurrentData()->nLinePos >= CurrentTopLine) && (m_pTxtBtn.GetCurrentData()->nLinePos <= CurrentTopLine+m_nMaxLine))
			{
				if(IsCurrsorOnThisButton(m_pTxtBtn.GetCurrentData(),xWndPos,xPos,CurrentTopLine))
				{
					m_pTxtBtn.GetCurrentData()->bIsClicked = FALSE;   
					return m_pTxtBtn.GetCurrentData();
				}
			}
			m_pTxtBtn.MoveNextNode();
		}
	}
	return NULL;
}



BOOL CTextButton::IsCurrsorOnThisButton(CMTxtBtn* pBtn,POINT xWndPos,POINT xPos,INT CurrentTopLine)
{
	int			nTempX,nTempY;
	int			StdPosX,StdPosY;																			// �����̴� �����쳻���� ���� ���� ��� �Ѵ�.
	
	StdPosY = xWndPos.y + (pBtn->nLinePos - CurrentTopLine)*(m_nTxtHeight+m_nLineGap)+m_xStartPos.y;		// ���� ��ġ������ Top�� ���Ѵ�.
	StdPosX = xWndPos.x + pBtn->xRect.left+m_xStartPos.x;													// ���� ��ġ������ Left�� ���Ѵ�.
	nTempX = StdPosX	+ pBtn->xRect.right;
	nTempY = StdPosY	+ pBtn->xRect.bottom;
			
	if((xPos.x>StdPosX)&&(xPos.x<nTempX))
	{
		if((xPos.y>StdPosY)&&(xPos.y<nTempY))
		{
			return TRUE;
		}
	}
	return FALSE;
}