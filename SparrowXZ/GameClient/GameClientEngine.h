#pragma once

#include "Stdafx.h"
#include "GameLogic.h"
#include "GameClientView.h"
#include "DirectSound.h"

//////////////////////////////////////////////////////////////////////////

//游戏对话框
class CGameClientEngine : public CGameFrameEngine
{
	//游戏变量
protected:
	bool							m_bCheatMode;						//防作弊标识

	//用户变量
protected:
	WORD							m_wBankerUser;						//庄家用户
	WORD							m_wCurrentUser;						//当前用户
	BYTE							m_cbUserAction;						//玩家动作
	LONG							m_lSiceCount;						//骰子点数
	TCHAR							m_szAccounts[GAME_PLAYER][32];		//用户名字

	//缺门信息
protected:
	bool							m_bCallCard[GAME_PLAYER];			//用户状态
	BYTE							m_cbCallCard[GAME_PLAYER];			//用户缺门

	//托管变量
protected:
	bool							m_bStustee;							//托管标志
	WORD							m_wTimeOutCount;					//超时次数

	//堆立变量
protected:
	WORD							m_wHeapHand;						//堆立头部
	WORD							m_wHeapTail;						//堆立尾部
	BYTE							m_cbHeapCardInfo[4][2];				//堆牌信息

	//扑克变量
protected:
	BYTE							m_cbLeftCardCount;					//剩余数目
	BYTE							m_cbCardIndex[MAX_INDEX];			//手中扑克

	//组合扑克
protected:
	BYTE							m_cbWeaveCount[GAME_PLAYER];		//组合数目
	tagWeaveItem					m_WeaveItemArray[GAME_PLAYER][4];	//组合扑克

	//出牌信息
protected:
	WORD							m_wOutCardUser;						//出牌用户
	BYTE							m_cbOutCardData;					//出牌扑克
	BYTE							m_cbDiscardCount[GAME_PLAYER];		//丢弃数目
	BYTE							m_cbDiscardCard[GAME_PLAYER][55];	//丢弃记录

	//控件变量
public:
	CGameLogic						m_GameLogic;						//游戏逻辑
	CHistoryScore					m_HistoryScore;						//历史积分
	CGameClientView					m_GameClientView;					//游戏视图
	CDirectSound					m_DirectSound;						//出牌和发牌声音
	
	//函数定义
public:
	//构造函数
	CGameClientEngine();
	//析构函数
	virtual ~CGameClientEngine();

	//常规继承
private:
	//初始函数
	virtual bool OnInitGameEngine();
	//重置框架
	virtual bool OnResetGameEngine();
	//时钟删除
	virtual bool OnEventGameClockKill(WORD wChairID);
	//时间消息
	virtual bool OnEventGameClockInfo(WORD wChairID, UINT nElapse, WORD wClockID);
	//旁观状态
	virtual bool OnEventLookonMode(VOID * pData, WORD wDataSize);
	//网络消息
	virtual bool OnEventGameMessage(WORD wSubCmdID, VOID * pBuffer, WORD wDataSize);
	//游戏场景
	virtual bool OnEventSceneMessage(BYTE cbGameStatus, bool bLookonOther, VOID * pBuffer, WORD wDataSize);

	//消息处理
protected:
	//游戏开始
	bool OnSubGameStart(const void * pBuffer, WORD wDataSize);
	//用户选缺
	bool OnSubCallCard(const void * pBuffer, WORD wDataSize);
	//庄家信息
	bool OnSubBankerInfo(const void * pBuffer, WORD wDataSize);
	//用户出牌
	bool OnSubOutCard(const void * pBuffer, WORD wDataSize);
	//发牌消息
	bool OnSubSendCard(const void * pBuffer, WORD wDataSize);
	//操作提示
	bool OnSubOperateNotify(const void * pBuffer, WORD wDataSize);
	//操作结果
	bool OnSubOperateResult(const void * pBuffer, WORD wDataSize);
	//游戏结束
	bool OnSubGameEnd(const void * pBuffer, WORD wDataSize);
	//用户托管
	bool OnSubTrustee(const void * pBuffer,WORD wDataSize);
	//用户吃胡
	bool OnSubUserChiHu( const void *pBuffer,WORD wDataSize );
	//用户杠牌
	bool OnSubGangScore( const void *pBuffer, WORD wDataSize );

	//辅助函数
protected:
	//播放声音
	void PlayCardSound(WORD wChairID,BYTE cbCardData);
	//播放声音
	void PlayActionSound(WORD wChairID,BYTE cbAction);
	//出牌判断
	bool VerdictOutCard(BYTE cbCardData);
	//扣除扑克
	void DeductionTableCard(bool bHeadCard);
	//显示控制
	bool ShowOperateControl(BYTE cbUserAction, BYTE cbActionCard);

	//消息映射
protected:
	//开始消息
	LRESULT OnStart(WPARAM wParam, LPARAM lParam);
	//定缺消息
	LRESULT OnCallCard(WPARAM wParam, LPARAM lParam);
	//出牌操作
	LRESULT OnOutCard(WPARAM wParam, LPARAM lParam);
	//扑克操作
	LRESULT OnCardOperate(WPARAM wParam, LPARAM lParam);
	//拖管控制
	LRESULT OnStusteeControl(WPARAM wParam, LPARAM lParam);
	//第二次摇色子消息
	LRESULT OnSiceTwo(WPARAM wParam, LPARAM lParam);
	//摇色子结束消息
	LRESULT OnSiceFinish(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
