#pragma once

#include "Stdafx.h"
#include "ScoreView.h"
#include "GoldControl.h"
#include "GoldView.h"
#include "CardControl.h"
#include "SmallCardControl.h"
#include "Prompt.h"

//////////////////////////////////////////////////////////////////////////

#define FRAME_CAPTION					30								//框架头高

//////////////////////////////////////////////////////////////////////////

//消息定义
#define IDM_START					WM_USER+100							//开始消息
#define IDM_EXIT					WM_USER+101							//离开消息
#define IDM_GIVEUP					WM_USER+102							//放弃消息
#define IDM_ADD_SCORE				WM_USER+103							//加注消息	
#define IDM_PASS_CARD				WM_USER+104							//让牌消息	
#define IDM_FOLLOW					WM_USER+105							//跟注消息
#define IDM_SHOWHAND				WM_USER+106							//梭哈消息
#define IDM_START_TIMES				WM_USER+107							//时间消息
#define IDM_AUTO_START				WM_USER+108							//开始消息
#define IDM_SIT_DOWN				WM_USER+109							//坐下消息
#define IDM_GAME_OVER				WM_USER+111							//结束消息
#define IDM_SEND_FINISH				WM_USER+112							//发牌结束
#define IDM_OPEN_CARD				WM_USER+113							//开牌消息
#define WM_SET_CAPTION				WM_USER+229							//窗口消息
#define IDM_LBUTTONDOWN_VIEW		WM_USER+220							//左键视图

//时间定时器
#define IDI_GAME_OVER					30								//动画定时器
#define IDI_NO_SCORE					31								//结束定时器
#define IDI_CLOSE_GAME                  32                              //退出倒计时 

//////////////////////////////////////////////////////////////////////////
//结构定义

//筹码状态
struct tagJettonStatus
{
	//属性信息
	WORD							wMoveCount;							//移动次数
	WORD							wMoveIndex;							//移动索引

	//筹码信息
	CPoint							ptFrom;								//出发位置
	CPoint							ptDest;								//目的位置
	CPoint							ptCourse;							//过程位置
	LONGLONG						lGold;								//筹码数目

	//移动形式
	INT								iMoveType;							//移动形式
};

//扑克状态
struct tagCardStatus
{
	//属性信息
	WORD							wMoveCount;							//移动次数
	WORD							wMoveIndex;							//移动索引

	//筹码信息
	CPoint							ptFrom;								//出发位置
	CPoint							ptDest;								//目的位置
	CPoint							ptCourse;							//过程位置
	BYTE							bCard;								//扑克数据

	//移动形式
	INT								iMoveType;							//移动形式
};
//////////////////////////////////////////////////////////////////////////

//动画参数
#define TO_USERCARD						1								//用户扑克
#define TO_GIVEUP_CARD					2								//回收扑克
#define TO_CENTER_CARD					3								//中心扑克

typedef CWHArray<tagCardStatus,tagCardStatus&> CCardStatusArray;
//////////////////////////////////////////////////////////////////////////

//游戏视图
class CGameClientView : public CGameFrameViewGDI
{
	//状态变量
protected:
	bool							m_bReset;							//复位标志
	WORD							m_wMeChairID;						//椅子位置
	WORD							m_wDUser;							//D标示
	WORD							m_wMyIsLookOn;						//旁观用户
	WORD							m_wUserGender[GAME_PLAYER];			//用户姓别
	WORD							m_wUserPost[GAME_PLAYER];			//用户位置
	WORD							m_wCardType[GAME_PLAYER];			//用户牌型

	//数据变量
protected:
	BYTE							m_bShowUser;						//显示标志
	LONGLONG						m_lTableScore[GAME_PLAYER];			//桌面下注
	LONGLONG						m_lTotalScore[GAME_PLAYER];			//总下注
	LONGLONG						m_lCenterScore;						//中心筹码
	LONGLONG						m_lTurnLessScore;					//最小下注
	LONGLONG						m_lTurnMaxScore;					//最大下注

	//界面变量
protected:
	CBitImageEx						m_ImageViewCenter;					//背景位图
	CBitImageEx						m_ImageViewFill;
	CBitImageEx						m_ImageHuman;						//人物图像
	CBitImageEx						m_ImageTitleInfo;					//下注信息
	CBitImageEx						m_ImageUserFrame;					//用户框架

	CPngImageEx						m_ImageCardMask;					//扑克掩图
	CPngImageEx						m_ImageD;							//D位图
	CPngImageEx						m_ImageArrowhead;					//时间箭头
	CPngImageEx						m_ImageCard;						//扑克位图
	CPngImageEx						m_ImageSmallCard;					//小牌位图
	CPngImageEx						m_ImageCradType;					//结束牌型
	
protected:
	CString							m_StringCaption;					//标题
	CDFontEx						m_FontCaption;						//标题字体

	//控件变量
protected:
	CSkinButton						m_btMin;							//最小化按钮
	CSkinButton						m_btClose;							//关闭按钮
	CSkinButton						m_btBank;							//银行按钮
	CPngImage						m_ImageGameFrame[8];				//游戏框架

	//动画变量
public:
	//移动类型
	enum ANTE_ANIME_ENUM
	{
		AA_BASEFROM_TO_BASEDEST=0,										// 底注筹码下注
		AA_BASEDEST_TO_CENTER,											// 加注筹码移至中间
		AA_CENTER_TO_BASEFROM,											// 中加筹码移至底注
	};
	CGoldView						m_MoveGoldView[GAME_PLAYER];		//筹码控件
	bool							m_bJettonAction;					//动画标志
	bool							m_bCardAction;						//动画标志
	tagJettonStatus					m_JettonStatus[GAME_PLAYER];		//筹码信息
	CCardStatusArray				m_CardStatus[GAME_PLAYER+1];		//扑克信息
	BYTE							m_bCenterCount;						//中心次数

	//位置变量
protected:
	CPoint							m_ptHuman[GAME_PLAYER];				//人物位置
	CPoint							m_ptWomen[GAME_PLAYER];				//人物位置
	CPoint							m_ptSmallCard[GAME_PLAYER];			//小牌位置
	CPoint							m_ptCard[GAME_PLAYER];				//扑克位置
	CPoint							m_ptJetton[GAME_PLAYER];			//筹码位置
	CPoint							m_ptCenterCard;						//中心扑克位置
	CPoint							m_ptCenterJetton;					//中心筹码位置
	CPoint							m_ptD[GAME_PLAYER];					//D位置
	CPoint							m_SendEndingPos[GAME_PLAYER];		//发牌结束位置
	CPoint							m_ptSitDown[GAME_PLAYER];			//坐下按钮位置
	CPoint                          m_ptViewCenter;                     //视图中心 

	//按钮控件
public:
	CSkinButton						m_btStart;							//开始按钮
	CSkinButton						m_btExit;							//离开按钮
	CSkinButton						m_btPassCard;						//放弃按纽
	CSkinButton						m_btShowHand;						//梭哈按钮
	CSkinButton						m_btGiveUp;							//放弃按钮	
	CSkinButton						m_btAdd;							//加注按钮	
	CSkinButton						m_btFollow;							//跟注按钮	
	CSkinButton						m_btAutoStart;						//自动开始
	CSkinButton						m_btOpenCard;						//开牌按钮
	CSkinButton						m_btSitDown[GAME_PLAYER];			//坐下按钮

	//动画变量
protected:
	bool							m_bGameEnd;							//游戏结束
	CPoint							m_SendCardPos;						//发牌位置

	//控件变量
public:
	CPrompt							m_Prompt;							//提示结束
	CScoreView						m_ScoreView;						//成绩窗口
	CGoldControl					m_GoldControl;						//加注视图
	CGoldView						m_GoldView[GAME_PLAYER];			//筹码控件
	CGoldView						m_CenterGoldView;					//中心筹码
	CCardControl					m_CardControl[GAME_PLAYER];			//扑克视图
	CCardControl					m_CenterCardControl;				//中心视图
	CSmallCardControl				m_SmallCardControl[GAME_PLAYER];	//小扑克视图

	//字体变量
public:
	CFont                           m_ViewFont;                         //视图字体 
	CDFontEx                        m_ViewFontEx;                       //视图字体

	//函数定义
public:
	//构造函数
	CGameClientView();
	//析构函数
	virtual ~CGameClientView();

	//继承函数
private:
	//重置界面
	virtual VOID ResetGameView();
	//调整控件
	virtual VOID RectifyControl(INT nWidth, INT nHeight);
	//绘画界面
	virtual VOID DrawGameView(CDC * pDC, INT nWidth, INT nHeight);
	//绘画框架
	virtual VOID DrawGameFrame(CDC *pDC, int nWidth, int nHeight);
	//是否特殊绘制
	virtual bool RealizeWIN7() { return true;; }

	//功能函数
public:
	//显示用户
	void SetShowUserView(BYTE bShow);
	//设置位置
	void SetMePost(WORD wMeChairID){m_wMeChairID = wMeChairID;}
	//旁观状态
	void SetMyLookOn(WORD wIsLookOnId);
	//旁观状态
	WORD GetMyLookOnId(){return m_wMyIsLookOn;}
	//设置标示
	void SetDFlag(WORD wDUser);
	//设置下注
	void SetUserTableScore(WORD wChairID, LONGLONG lTableScore);
	//中心筹码
	void SetCenterScore(LONGLONG lCenterScore);
	//设置总筹码
	void SetTotalScore(WORD wChairID, LONGLONG lTotalScore);
	//筹码信息
	void SetTitleInfo(LONGLONG lTurnLessScore, LONGLONG lTurnMaxScore);
	//设置结束
	void SetGameEndStart();
	//设置结束
	void SetGameEndEnd();
	//设置结束
	void SetCenterCount(){m_bCenterCount=0;}
	//移动筹码
	void DrawMoveAnte( WORD wViewChairID, int iMoveType, LONGLONG lTableScore );
	//移动扑克
	void DrawMoveCard( WORD wViewChairID, int iMoveType, BYTE bCard );
	//移动筹码
	bool MoveJetton();
	//移动筹码
	bool MoveCard();
	// 添加小数点
	CString AddDecimal( LONGLONG lScore ,  bool bComma = true, bool bPlus = false );
	//整性变字符
	LPCTSTR GetGlodString(LONGLONG lGold, TCHAR szString[]);
	//物理位置
	void SetUserPost(WORD wPhysicsPost,WORD wViewPost);
	//动画标志
	bool IsMoveing(){return (m_bJettonAction || m_bCardAction);}
	//设置时间
	void SetOverTimer(){SetTimer(IDI_GAME_OVER,50,NULL);}
	//复位标志
	void SetResetTag(bool bReset=false){m_bReset = bReset;}
	//复位标志
	void SetUserGender(WORD wViewChairID,WORD wGender){m_wUserGender[wViewChairID] = wGender;}
	//结束提示框
	void SetNoScoreDlg(){SetTimer(IDI_NO_SCORE,50,NULL);}
	//结束牌型
	void ShowOverCardType(WORD wViewChairID, BYTE cbCardType);
	//更新视图
	void RefreshGameView();

	//消息映射
protected:
	//建立函数
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//时间消息
	afx_msg void OnTimer(UINT nIDEvent);
	//命令消息
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//标题
	afx_msg LRESULT OnSetCaption(WPARAM wParam, LPARAM lParam);
	//按钮
	afx_msg void OnLButtonDown(UINT nFlags, CPoint Point);
	//最小按钮	
	afx_msg void OnButtonMin();
	//关闭按钮	
	afx_msg void OnButtonClose();

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
