#include "StdAfx.h"
#include "GameLogic.h"

//////////////////////////////////////////////////////////////////////////

//扑克数据
BYTE CGameLogic::m_cbCardListData[28]=
{
	0x01,0x08,0x09,0x0A,0x0B,0x0C,0x0D,									//方块 A - K
	0x11,0x18,0x19,0x1A,0x1B,0x1C,0x1D,									//梅花 A - K
	0x21,0x28,0x29,0x2A,0x2B,0x2C,0x2D,									//红桃 A - K
	0x31,0x38,0x39,0x3A,0x3B,0x3C,0x3D,									//黑桃 A - K
};

//////////////////////////////////////////////////////////////////////////

//构造函数
CGameLogic::CGameLogic()
{
}

//析构函数
CGameLogic::~CGameLogic()
{
}

//获取类型
BYTE CGameLogic::GetCardGenre(BYTE cbCardData[], BYTE cbCardCount)
{
	BYTE cbCardTemp[MAX_COUNT];
	ZeroMemory(cbCardTemp, sizeof(cbCardTemp));

	CopyMemory(cbCardTemp,cbCardData, cbCardCount * sizeof(BYTE));
	SortCardList(cbCardTemp,cbCardCount);

	//简单牌形
	switch (cbCardCount)
	{
	case 1: //单牌
		{
			return CT_SINGLE;
		}
	case 2:	//对牌
		{
			return (GetCardLogicValue(cbCardData[0])==GetCardLogicValue(cbCardData[1]))?CT_ONE_DOUBLE:CT_SINGLE;
		}
	}

	//五条类型
	if (cbCardCount>=MAX_COUNT)
	{
		//变量定义
		bool cbSameColor=true,bLineCard=true;
		BYTE cbFirstColor=GetCardColor(cbCardTemp[0]);
		BYTE cbFirstValue=GetCardLogicValue(cbCardTemp[0]);

		//牌形分析
		for (BYTE i=1;i<cbCardCount;i++)
		{
			//数据分析
			if (GetCardColor(cbCardTemp[i])!=cbFirstColor) cbSameColor=false;
			if (cbFirstValue!=(GetCardLogicValue(cbCardTemp[i])+i)) bLineCard=false;

			//结束判断
			if ((cbSameColor==false)&&(bLineCard==false)) break;
		}

		//顺子类型
		if ((cbSameColor==false)&&(bLineCard==true)) return CT_SHUN_ZI;

		//同花类型
		if ((cbSameColor==true)&&(bLineCard==false)) return CT_TONG_HUA;

		//同花顺类型
		if ((cbSameColor==true)&&(bLineCard==true)) return CT_TONG_HUA_SHUN;
	}

	//扑克分析
	tagAnalyseResult AnalyseResult;
	AnalysebCardData(cbCardTemp,cbCardCount,AnalyseResult);

	//四条类型
	if (AnalyseResult.cbFourCount==1) return CT_TIE_ZHI;

	//两对类型
	if (AnalyseResult.cbDoubleCount==2) return CT_TWO_DOUBLE;

	//对牌类型
	if ((AnalyseResult.cbDoubleCount==1)&&(AnalyseResult.cbThreeCount==0)) return CT_ONE_DOUBLE;

	//葫芦类型
	if (AnalyseResult.cbThreeCount==1) return (AnalyseResult.cbDoubleCount==1)?CT_HU_LU:CT_THREE_TIAO;

	return CT_SINGLE;
}

//排列扑克
VOID CGameLogic::SortCardList(BYTE cbCardData[], BYTE cbCardCount)
{
	//转换数值
	BYTE cbLogicValue[MAX_COUNT];
	for (BYTE i=0;i<cbCardCount;i++) cbLogicValue[i]=GetCardLogicValue(cbCardData[i]);	

	//排序操作
	bool bSorted=true;
	BYTE cbTempData,bLast=cbCardCount-1;
	do
	{
		bSorted=true;
		for (BYTE i=0;i<bLast;i++)
		{
			if ((cbLogicValue[i]<cbLogicValue[i+1])||
				((cbLogicValue[i]==cbLogicValue[i+1])&&(cbCardData[i]<cbCardData[i+1])))
			{
				//交换位置
				cbTempData=cbCardData[i];
				cbCardData[i]=cbCardData[i+1];
				cbCardData[i+1]=cbTempData;
				cbTempData=cbLogicValue[i];
				cbLogicValue[i]=cbLogicValue[i+1];
				cbLogicValue[i+1]=cbTempData;
				bSorted=false;
			}	
		}
		bLast--;
	} while(bSorted==false);

	return;
}

//混乱扑克
VOID CGameLogic::RandCardList(BYTE cbCardBuffer[], BYTE cbBufferCount)
{
	//混乱准备
	BYTE cbCardData[CountArray(m_cbCardListData)];
	CopyMemory(cbCardData,m_cbCardListData,sizeof(m_cbCardListData));

	//混乱扑克
	BYTE cbRandCount=0,cbPosition=0;
	do
	{
		cbPosition=rand()%(CountArray(cbCardData)-cbRandCount);
		cbCardBuffer[cbRandCount++]=cbCardData[cbPosition];
		cbCardData[cbPosition]=cbCardData[CountArray(cbCardData)-cbRandCount];
	} while (cbRandCount<cbBufferCount);

	return;
}

//逻辑数值
BYTE CGameLogic::GetCardLogicValue(BYTE cbCardData)
{
	//转换数值
	BYTE cbCardValue=GetCardValue(cbCardData);
	BYTE cbLogicValue=(cbCardValue<=2)?(cbCardValue+13):cbCardValue;

	return cbLogicValue;
}

//对比扑克
bool CGameLogic::CompareCard(BYTE cbFirstCardData[], BYTE cbNextCardData[], BYTE cbCardCount)
{
	//获取类型
	BYTE cbNextGenre=GetCardGenre(cbNextCardData,cbCardCount);
	BYTE cbFirstGenre=GetCardGenre(cbFirstCardData,cbCardCount);

	//类型判断
	if (cbFirstGenre!=cbNextGenre) return (cbFirstGenre>cbNextGenre);

	//类型对比
	switch(cbFirstGenre)
	{
	case CT_SINGLE:			//单牌
		{
			SortCardList(cbNextCardData,cbCardCount);
			SortCardList(cbFirstCardData,cbCardCount);

			BYTE cbNextValue=GetCardLogicValue(cbNextCardData[0]);
			BYTE cbFirstValue=GetCardLogicValue(cbFirstCardData[0]);
			BYTE cbNextColor=GetCardColor(cbNextCardData[0]);
			BYTE cbFirstColor=GetCardColor(cbFirstCardData[0]);

			if (cbNextValue != cbFirstValue)
			{
				return cbFirstValue>cbNextValue;
			}

			return cbFirstColor > cbNextColor;
		}
	case CT_HU_LU:			//葫芦
	case CT_TIE_ZHI:		//铁支
	case CT_ONE_DOUBLE:		//对子
	case CT_TWO_DOUBLE:		//两对
	case CT_THREE_TIAO:		//三条
		{
			//分析扑克
			tagAnalyseResult AnalyseResultNext;
			tagAnalyseResult AnalyseResultFirst;
			AnalysebCardData(cbNextCardData,cbCardCount,AnalyseResultNext);
			AnalysebCardData(cbFirstCardData,cbCardCount,AnalyseResultFirst);

			//四条数值
			if (AnalyseResultFirst.cbFourCount>0)
			{
				BYTE cbNextValue=AnalyseResultNext.cbFourLogicVolue[0];
				BYTE cbFirstValue=AnalyseResultFirst.cbFourLogicVolue[0];
				return cbFirstValue>cbNextValue;
			}

			//三条数值
			if (AnalyseResultFirst.cbThreeCount>0)
			{
				BYTE cbNextValue=AnalyseResultNext.cbThreeLogicVolue[0];
				BYTE cbFirstValue=AnalyseResultFirst.cbThreeLogicVolue[0];
				return cbFirstValue>cbNextValue;
			}

			//两对
			if (cbFirstGenre == CT_TWO_DOUBLE)
			{
				ASSERT(AnalyseResultFirst.cbDoubleCount == 2);

				//先比较大对子和小对子的逻辑值
				for (BYTE i=0; i<AnalyseResultFirst.cbDoubleCount; i++)
				{
					SortCardList(AnalyseResultNext.cbDoubleLogicVolue, AnalyseResultNext.cbDoubleCount);
					SortCardList(AnalyseResultFirst.cbDoubleLogicVolue, AnalyseResultFirst.cbDoubleCount);
					BYTE cbNextValue = AnalyseResultNext.cbDoubleLogicVolue[i];
					BYTE cbFirstValue = AnalyseResultFirst.cbDoubleLogicVolue[i];
					if (cbFirstValue != cbNextValue) 
					{
						return cbFirstValue > cbNextValue;
					}
				}

				//对子花色
				if (AnalyseResultFirst.cbDoubleCount > 0)
				{
					SortCardList(AnalyseResultNext.cbDoubleCardData, AnalyseResultNext.cbDoubleCount);
					SortCardList(AnalyseResultFirst.cbDoubleCardData, AnalyseResultFirst.cbDoubleCount);
					BYTE cbNextColor = GetCardColor(AnalyseResultNext.cbDoubleCardData[0]);
					BYTE cbFirstColor = GetCardColor(AnalyseResultFirst.cbDoubleCardData[0]);
					return cbFirstColor>cbNextColor;
				}
			}

			//一对
			if (cbFirstGenre == CT_ONE_DOUBLE)
			{
				ASSERT(AnalyseResultFirst.cbDoubleCount == 1);

				//先比较对子的逻辑值
				for (BYTE i=0; i<AnalyseResultFirst.cbDoubleCount; i++)
				{
					SortCardList(AnalyseResultNext.cbDoubleLogicVolue, AnalyseResultNext.cbDoubleCount);
					SortCardList(AnalyseResultFirst.cbDoubleLogicVolue, AnalyseResultFirst.cbDoubleCount);
					BYTE cbNextValue = AnalyseResultNext.cbDoubleLogicVolue[i];
					BYTE cbFirstValue = AnalyseResultFirst.cbDoubleLogicVolue[i];
					if (cbFirstValue != cbNextValue) 
					{
						return cbFirstValue > cbNextValue;
					}
				}

				//对子花色
				if (AnalyseResultFirst.cbDoubleCount > 0)
				{
					SortCardList(AnalyseResultNext.cbDoubleCardData, AnalyseResultNext.cbDoubleCount);
					SortCardList(AnalyseResultFirst.cbDoubleCardData, AnalyseResultFirst.cbDoubleCount);
					BYTE cbNextColor = GetCardColor(AnalyseResultNext.cbDoubleCardData[0]);
					BYTE cbFirstColor = GetCardColor(AnalyseResultFirst.cbDoubleCardData[0]);
					return cbFirstColor > cbNextColor;
				}
			}

			break;
		}
	case CT_SHUN_ZI:		//顺子
	case CT_TONG_HUA:		//同花
	case CT_TONG_HUA_SHUN:	//同花顺
		{
			//数值判断
			BYTE cbNextValue=GetCardLogicValue(cbNextCardData[0]);
			BYTE cbFirstValue=GetCardLogicValue(cbFirstCardData[0]);
			if (cbFirstValue!=cbNextValue) return (cbFirstValue>cbNextValue);

			//花色判断
			BYTE cbNextColor=GetCardColor(cbNextCardData[0]);
			BYTE cbFirstColor=GetCardColor(cbFirstCardData[0]);

			return (cbFirstColor>cbNextColor);
		}
	}

	//错误断言
	ASSERT(FALSE);

	return false;
}

//分析扑克
VOID CGameLogic::AnalysebCardData(const BYTE cbCardData[], BYTE cbCardCount, tagAnalyseResult & AnalyseResult)
{
	//设置结果
	ZeroMemory(&AnalyseResult,sizeof(AnalyseResult));

	//扑克分析
	for (BYTE i=0;i<cbCardCount;i++)
	{
		//变量定义
		BYTE cbSameCount=1;
		BYTE cbSameCardData[4]={cbCardData[i],0,0,0};
		BYTE cbLogicValue=GetCardLogicValue(cbCardData[i]);

		//获取同牌
		for (INT j=i+1;j<cbCardCount;j++)
		{
			//逻辑对比
			if (GetCardLogicValue(cbCardData[j])!=cbLogicValue) break;

			//设置扑克
			cbSameCardData[cbSameCount++]=cbCardData[j];
		}

		//保存结果
		switch (cbSameCount)
		{
		case 1:		//单张
			{
				AnalyseResult.cbSignedLogicVolue[AnalyseResult.cbSignedCount]=cbLogicValue;
				CopyMemory(&AnalyseResult.cbSignedCardData[(AnalyseResult.cbSignedCount++)*cbSameCount],cbSameCardData,cbSameCount);
				break;
			}
		case 2:		//两张
			{
				AnalyseResult.cbDoubleLogicVolue[AnalyseResult.cbDoubleCount]=cbLogicValue;
				CopyMemory(&AnalyseResult.cbDoubleCardData[(AnalyseResult.cbDoubleCount++)*cbSameCount],cbSameCardData,cbSameCount);
				break;
			}
		case 3:		//三张
			{
				AnalyseResult.cbThreeLogicVolue[AnalyseResult.cbThreeCount]=cbLogicValue;
				CopyMemory(&AnalyseResult.cbThreeCardData[(AnalyseResult.cbThreeCount++)*cbSameCount],cbSameCardData,cbSameCount);
				break;
			}
		case 4:		//四张
			{
				AnalyseResult.cbFourLogicVolue[AnalyseResult.cbFourCount]=cbLogicValue;
				CopyMemory(&AnalyseResult.cbFourCardData[(AnalyseResult.cbFourCount++)*cbSameCount],cbSameCardData,cbSameCount);
				break;
			}
		}

		//设置递增
		i+=cbSameCount-1;
	}

	return;
}

//////////////////////////////////////////////////////////////////////////
