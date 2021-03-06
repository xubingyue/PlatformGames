#include "StdAfx.h"
#include "Resource.h"
#include "GoldView.h"

//////////////////////////////////////////////////////////////////////////

//静态变量
bool							CGoldView::m_bInit=false;				//初始标志
CPngImageEx						CGoldView::m_ImageGold;					//正常筹码

//////////////////////////////////////////////////////////////////////////

//构造函数
CGoldView::CGoldView()
{
	m_lGold=0L;
	m_lMaxLayer=6;
	memset(m_lGoldCount,0,sizeof(m_lGoldCount));
	m_pGameViewWnd=NULL;
	
	return;
}

//析构函数
CGoldView::~CGoldView()
{
}

//设置筹码
void CGoldView::SetGold(LONGLONG lGold)
{
	if (m_lGold!=lGold)
	{
		m_lGold=lGold;
		RectifyGoldLayer();
	}
	return;
}

//设置层数
void CGoldView::SetMaxGoldLayer(LONGLONG lMaxLayer)
{
	if (m_lMaxLayer!=lMaxLayer)
	{
		m_lMaxLayer=lMaxLayer; 
		RectifyGoldLayer();
	}
	return;
}

//绘画筹码
void CGoldView::DrawGoldView(CDC * pDC, int nXPos, int nYPos, bool bCount,bool bCenter,BYTE bDUser)
{
	if(!bCenter)
	{
		//绘画筹码
		int nYPosDraw=nYPos-GOLD_IMAGE_HEIGHT/2;
		int iDrawCount =0;
		for (LONG i=0;i<CountArray(m_lGoldCount);i++)
		{
			for (LONG j=0;j<m_lGoldCount[i];j++)
			{
				iDrawCount++;
				m_ImageGold.AlphaDrawImage(pDC,nXPos-GOLD_IMAGE_WIDTH/2,nYPosDraw,GOLD_IMAGE_WIDTH,GOLD_IMAGE_HEIGHT,
					(CountArray(m_lGoldCount)-i-1)*GOLD_IMAGE_WIDTH,0,255);
				nYPosDraw-=3;
				if(iDrawCount>=m_lMaxLayer)break;
			}
			if(iDrawCount>=m_lMaxLayer)break;
		}
	}
	else //中心筹码
	{
		//绘画筹码
		int nYPosDraw=nYPos-GOLD_IMAGE_HEIGHT/2;
		int nXPosDraw=nXPos-GOLD_IMAGE_HEIGHT/2;
		int iCount = 0,iDrawCount =0;
		int xTemp=0,yTemp=0;
		for (LONG i=0;i<CountArray(m_lGoldCount);i++)
		{
			for (LONG j=0;j<m_lGoldCount[i];j++)
			{
				iDrawCount++;
				m_ImageGold.AlphaDrawImage(pDC,nXPosDraw+xTemp,nYPosDraw+GOLD_IMAGE_HEIGHT/2+2,GOLD_IMAGE_WIDTH,
					GOLD_IMAGE_HEIGHT,(CountArray(m_lGoldCount)-i-1)*GOLD_IMAGE_WIDTH,0,255);
				nYPosDraw-=3;
				if(iDrawCount>=m_lMaxLayer)
				{
					iDrawCount=0;
					nYPosDraw=nYPos-GOLD_IMAGE_HEIGHT/2;
					iCount++;
					if(iCount==1)
					{
						xTemp=GOLD_IMAGE_WIDTH;
					}
					else if(iCount==2)
					{
						xTemp=-GOLD_IMAGE_WIDTH;
					}
					else if(iCount==3)
					{
						xTemp=GOLD_IMAGE_WIDTH*2;
					}
					else if(iCount==4)
					{
						xTemp=-GOLD_IMAGE_WIDTH*2;
					}
				}	
			}
		}
	}

	//绘画数字
	if((m_lGold>=1L)&&(bCount==true))
	{
		CDFontEx ViewFont;			
		if(bCenter)
		{
			ViewFont.CreateFont(m_pGameViewWnd,TEXT("Arial"),17,400);
			pDC->SetTextColor(RGB(255,255,4));
		}
		else 
		{
			ViewFont.CreateFont(m_pGameViewWnd,TEXT("Arial"),15,400);
			pDC->SetTextColor(RGB(255,255,4));
		}
		//CFont *pOldFont=pDC->SelectObject(&ViewFont);

		int iBkMode = pDC->SetBkMode( TRANSPARENT );

		TCHAR szBuffer[64]=TEXT("");
		GetGlodString(m_lGold,szBuffer);
		int iY = nYPos+GOLD_IMAGE_HEIGHT/((bCenter)?1:2)+1;
		int iX = 0;
		/*int iX = (bDUser!=4)?0:62;*/
		CRect DrawRect(nXPos-50+iX,iY,nXPos+46,iY+12);
		ViewFont.DrawText(pDC,szBuffer,&DrawRect,RGB(255,255,4),DT_CENTER|DT_VCENTER|DT_NOCLIP|DT_SINGLELINE);
		pDC->SetBkMode(iBkMode);	
	}

	return;
}

//调整筹码层
void CGoldView::RectifyGoldLayer()
{
	//变量定义
	LONGLONG lBasicGold[]={1000L,500L,100L,50L,10L,5L,1L},lGold=(LONGLONG)m_lGold;
	memset(m_lGoldCount,0,sizeof(m_lGoldCount));

	//调整筹码层
	for (LONGLONG i=0;i<CountArray(lBasicGold);i++)
	{
		if (lGold>=lBasicGold[i])
		{
			m_lGoldCount[i]=lGold/lBasicGold[i];
			lGold-=m_lGoldCount[i]*lBasicGold[i];
			if (m_lGoldCount[i]>m_lMaxLayer)
			{
				m_lGoldCount[i]=m_lMaxLayer;
			}
		}
	}

	return;
}

//整性变字符
LPCTSTR CGoldView::GetGlodString(LONGLONG lGold, TCHAR szString[])
{
	LONGLONG lTemp=(LONGLONG)lGold; 
	if(lGold<0L) return szString;

	//处理小数点
	DWORD dwCharBit=0L;
	//lGold+=0.001;
	//if(lGold-lTemp>0)
	//{
	//	lTemp = (LONGLONG)((lGold-lTemp)*100);

	//	bool bZero=(lTemp<10)?true:false;

	//	//转换字符
	//	do
	//	{
	//		szString[dwCharBit++]=(TCHAR)(lTemp%10+TEXT('0'));
	//		lTemp/=10;
	//	} while (lTemp>0L);

	//	//加0位
	//	if(bZero)szString[dwCharBit++]=TEXT('0');

	//	szString[dwCharBit++]=TEXT('.');
	//}

	//转换字符
	lTemp = (LONGLONG)lGold; 
	DWORD dwNumBit=0L;
	do
	{
		dwNumBit++;
		szString[dwCharBit++]=(TCHAR)(lTemp%10+TEXT('0'));
		if (dwNumBit%3==0) szString[dwCharBit++]=TEXT(',');
		lTemp/=10;
	} while (lTemp>0L);

	//调整字符
	if (szString[dwCharBit-1]==TEXT(',')) szString[dwCharBit-1]=0;
	szString[dwCharBit]=0;

	//尾头交换
	_tcsrev(szString);

	return szString;
}

//加载资源
bool CGoldView::LoadResource(CWnd* pWnd)
{
	if (m_bInit==false)
	{
		m_bInit=true;
		m_ImageGold.LoadImage(pWnd,GetModuleHandle(NULL),TEXT("PNG_SCORE"));
	}
	if(m_ImageNumber.IsNull())
		m_ImageNumber.LoadFromResource(pWnd,AfxGetInstanceHandle(),IDB_NUMBER);

	m_pGameViewWnd=pWnd;

	return true;
}
//////////////////////////////////////////////////////////////////////////
