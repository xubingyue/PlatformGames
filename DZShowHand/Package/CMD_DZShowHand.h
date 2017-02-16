#ifndef CMD_DZSHOWHAND_HEAD_FILE
#define CMD_DZSHOWHAND_HEAD_FILE

//////////////////////////////////////////////////////////////////////////
//公共宏定义

#define KIND_ID							3									//游戏 I D
#define GAME_PLAYER						8									//游戏人数
#define GAME_NAME						TEXT("德州扑克")					//游戏名字
#define GAME_GENRE						(GAME_GENRE_GOLD|GAME_GENRE_MATCH)	//游戏类型

//版本信息
#define VERSION_SERVER					PROCESS_VERSION(7,0,1)				//程序版本
#define VERSION_CLIENT					PROCESS_VERSION(7,0,1)				//程序版本

//结束原因
#define GER_NO_PLAYER					0x10								//没有玩家

//数目定义
#define FULL_COUNT					    52									//全牌数目
#define MAX_COUNT						2									//最大数目
#define MAX_CENTERCOUNT					5									//最大数目

//数值掩码
#define	CARD_MASK_COLOR				0xF0									//花色掩码
#define	CARD_MASK_VALUE				0x0F									//数值掩码

#define  SMALL_CARD_WIDTH			25
#define  SMALL_CARD_HEIGHT			33

//X 排列方式
enum enXCollocateMode 
{
	enXLeft,						//左对齐
	enXCenter,						//中对齐
	enXRight,						//右对齐
};

//Y 排列方式
enum enYCollocateMode 
{ 
	enYTop,							//上对齐
	enYCenter,						//中对齐
	enYBottom,						//下对齐
};

//扑克结构
struct tagCardItem
{
	bool							bEffect;							//特效标志
	bool							bMy;								//自己标志
	bool							bShoot;								//弹起标志
	BYTE							cbCardData;							//扑克数据
};



//属性定义
#define MAX_CARD_COUNT				5									//扑克数目
#define SPACE_CARD_DATA				255									//间距扑克


//间距定义
#define DEF_X_DISTANCE				19									//默认间距
#define DEF_Y_DISTANCE				17									//默认间距
#define DEF_SHOOT_DISTANCE			20									//默认间距


//////////////////////////////////////////////////////////////////////////
//服务器命令结构
#define SUB_S_GAME_START				100									//游戏开始
#define SUB_S_ADD_SCORE					101									//加注结果
#define SUB_S_GIVE_UP					102									//放弃跟注	
#define SUB_S_SEND_CARD					103									//发牌消息
#define SUB_S_GAME_END					104									//游戏结束
#define SUB_S_SIT_DOWN					105									//用户坐下
#define SUB_S_OPEN_CARD					106									//用户开牌
#define SUB_S_SP_USER					107									//特殊用户

//游戏状态
struct CMD_S_StatusFree
{
	LONGLONG							lCellMinScore;						//最小下注
	LONGLONG							lCellMaxScore;						//最大下注
};

//游戏状态
struct CMD_S_StatusPlay
{
	//加注信息
	LONGLONG							lCellScore;							//单元下注
	LONGLONG							lTurnMaxScore;						//最大下注
	LONGLONG							lTurnLessScore;						//最小下注
	LONGLONG							lCellMaxScore;						//最大下注
	LONGLONG							lAddLessScore;						//加最小注
	LONGLONG							lTableScore[GAME_PLAYER];			//下注数目
	LONGLONG							lTotalScore[GAME_PLAYER];			//累计下注
	LONGLONG							lCenterScore;						//中心筹码

	//状态信息
	WORD								wDUser;								//D玩家
	WORD								wMinChipInUser;						//小盲注用户
	WORD				 				wCurrentUser;						//当前玩家
	BYTE								cbPlayStatus[GAME_PLAYER];			//游戏状态
	BYTE							    cbBalanceCount;						//平衡次数

	//扑克信息
	BYTE								cbCenterCardData[MAX_CENTERCOUNT];	//扑克数目
	BYTE								cbHandCardData[MAX_COUNT];			//桌面扑克
};

//发送扑克
struct CMD_S_GameStart
{
	WORD				 				wCurrentUser;						//当前玩家
	WORD								wDUser;								//D玩家
	WORD								wMinChipInUser;						//小盲注用户
	WORD								wMaxChipInUser;						//大盲注玩家	
	LONGLONG							lCellScore;							//单元下注
	LONGLONG							lTurnMaxScore;						//最大下注
	LONGLONG							lTurnLessScore;						//最小下注
	LONGLONG							lAddLessScore;						//加最小注
	BYTE								cbCardData[GAME_PLAYER][MAX_COUNT];	//用户扑克
};

//发送扑克
struct CMD_S_SpUser
{
	BYTE								cbAllData[GAME_PLAYER][MAX_COUNT];	//用户扑克
	BYTE								cbCenterCardData[MAX_CENTERCOUNT];	//中心扑克
};

//用户下注
struct CMD_S_AddScore
{
	WORD								wCurrentUser;						//当前用户
	WORD								wAddScoreUser;						//加注用户
	LONGLONG							lAddScoreCount;						//加注数目
	LONGLONG							lTurnLessScore;						//最少加注
	LONGLONG							lTurnMaxScore;						//最大下注
	LONGLONG							lAddLessScore;						//加最小注
	BYTE								cbShowHand[GAME_PLAYER];			//梭哈用户
};

//用户放弃
struct CMD_S_GiveUp
{
	WORD								wGiveUpUser;						//放弃用户
	LONGLONG							lLost;								//输掉金币	
};

//发牌数据包
struct CMD_S_SendCard
{
	BYTE								cbPublic;							//是否公牌
	WORD								wCurrentUser;						//当前用户
	BYTE								cbSendCardCount;					//发牌数目
	BYTE								cbCenterCardData[MAX_CENTERCOUNT];	//中心扑克	
};

//游戏结束
struct CMD_S_GameEnd
{
	BYTE								cbTotalEnd;							//强退标志
	LONGLONG							lGameTax[GAME_PLAYER];				//游戏税收
	LONGLONG							lGameScore[GAME_PLAYER];			//游戏得分
	BYTE								cbCardData[GAME_PLAYER][MAX_COUNT];	//用户扑克
	BYTE								cbLastCenterCardData[GAME_PLAYER][MAX_CENTERCOUNT];//最后扑克
	BYTE								cbDelayOverGame;
};

//游戏结束
struct CMD_S_OpenCard
{
	WORD								wWinUser;							//用户开牌
};


//////////////////////////////////////////////////////////////////////////
//客户端命令结构
#define SUB_C_ADD_SCORE					1									//用户加注
#define SUB_C_GIVE_UP					2									//放弃消息
#define SUB_C_OPEN_CARD					3									//开牌消息

//用户加注
struct CMD_C_AddScore
{
	LONGLONG							lScore;								//加注数目
};

//////////////////////////////////////////////////////////////////////////

#endif
