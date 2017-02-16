
#pragma once
#include "TableFrameSink.h"

//�Զ�������
struct tagCustomGeneral
{
	//��ׯ��Ϣ
	LONGLONG						lApplyBankerCondition;			//��������
	LONGLONG						lBankerTime;					//��ׯ����
	LONGLONG						lBankerTimeAdd;					//ׯ��������
	LONGLONG						lBankerScoreMAX;				//������ׯ�����
	LONGLONG						lBankerTimeExtra;				//������ׯ����
	BOOL							nEnableSysBanker;				//ϵͳ��ׯ

	//ʱ��
	LONGLONG						cbFreeTime;						//����ʱ��
	LONGLONG						cbBetTime;						//��עʱ��
	LONGLONG						cbEndTime;						//����ʱ��
	LONGLONG						cbGuessTime;					//�´�Сʱ��

	//��ע����
	LONGLONG						lAreaLimitScore;				//��������
	LONGLONG						lUserLimitScore;				//��������
	LONGLONG						lEndGameMul;					//��ǰ���ưٷֱ�

	//��Ϣ
	TCHAR							szMessageItem1[64];				//��Ϣ1
	TCHAR							szMessageItem2[64];				//��Ϣ2
	TCHAR							szMessageItem3[64];				//��Ϣ3

	//���
	LONGLONG						StorageStart;					//��ʼ���
	LONGLONG						StorageDeduct;					//���˥��
	LONGLONG						StorageMax1;					//���ⶥ1
	LONGLONG						StorageMul1;					//���ⶥ�����Ӯ�ָ���
	LONGLONG						StorageMax2;					//���ⶥ2
	LONGLONG						StorageMul2;					//���ⶥ�����Ӯ�ָ���

	//���캯��
	tagCustomGeneral()
	{
		DefaultCustomRule();
	}

	void DefaultCustomRule()
	{
		lApplyBankerCondition = 10000;
		lBankerTime = 10;
		lBankerTimeAdd = 10;
		lBankerScoreMAX = 10000000;
		lBankerTimeExtra = 10;
		nEnableSysBanker = TRUE;

		cbFreeTime = 5;
		cbBetTime = 10;
		cbEndTime = 20;
		cbGuessTime=15;

		lAreaLimitScore = 100000000;
		lUserLimitScore = 10000000;
		lEndGameMul = 10;

		CopyMemory(szMessageItem1,TEXT("�����Ǹ�������ɫ����"),sizeof(TEXT("�����Ǹ�������ɫ����")));
		CopyMemory(szMessageItem2,TEXT("������ӭ"),sizeof(TEXT("������ӭ")));
		CopyMemory(szMessageItem3,TEXT("��Ҿ�����Ϸ��"),sizeof(TEXT("��Ҿ�����Ϸ��")));

		StorageStart = 0;
		StorageDeduct = 0;
		StorageMax1 = 10000000;
		StorageMul1 = 50;
		StorageMax2 = 1000000000;
		StorageMul2 = 80;
	}
};


struct tagCustomConfig
{
	tagCustomGeneral				CustomGeneral;					//ͨ�ù���
	tagCustomAndroid				CustomAndroid;					//������

	//���캯��
	tagCustomConfig()
	{
		DefaultCustomRule();
	}

	void DefaultCustomRule()
	{
		CustomGeneral.DefaultCustomRule();
		CustomAndroid.DefaultCustomRule();
	}
};

////////////////////////////////////////////////////////////////////////////////////////////
class CDlgCustomGeneral : public CDialog
{
	//���ýṹ
public:
	tagCustomGeneral					m_CustomGeneral;						//�Զ�����

	//��������
public:
	//���캯��
	CDlgCustomGeneral();
	//��������
	virtual ~CDlgCustomGeneral();

	//���غ���
protected:
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//��ʼ������
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
////////////////////////////////////////////////////////////////////////////////////////////
class CDlgCustomAndroid : public CDialog
{
	//���ýṹ
public:
	tagCustomAndroid					m_CustomAndroid;						//�Զ�����

	//��������
public:
	//���캯��
	CDlgCustomAndroid();
	//��������
	virtual ~CDlgCustomAndroid();

	//���غ���
protected:
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//��ʼ������
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};
////////////////////////////////////////////////////////////////////////////////////////////
class CDlgCustomRule : public CDialog
{
	//�ؼ�����
protected:
	CDlgCustomGeneral				m_DlgCustomGeneral;					//ͨ������
	CDlgCustomAndroid				m_DlgCustomAndroid;					//��������

	//���ñ���
protected:
	WORD							m_wCustomSize;						//���ô�С
	LPBYTE							m_pcbCustomRule;					//���û���

	//���ýṹ
protected:
	tagCustomConfig					m_CustomConfig;						//�Զ�����
	WORD							m_wGeneralErrorCount;				//ͨ�ò������ô������
	WORD							m_wAndroidErrorCount;				//�����������ô������
	CString							m_strErrorMessage;					//������ʾ��Ϣ
	//��������
public:
	//���캯��
	CDlgCustomRule();
	//��������
	virtual ~CDlgCustomRule();

	//���غ���
protected:
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//��ʼ������
	virtual BOOL OnInitDialog();
	//ȷ������
	virtual VOID OnOK();
	//ȡ����Ϣ
	virtual VOID OnCancel();
	//��������
	BOOL UpdateConfigData(BOOL bSaveAndValidate);

	//���ܺ���
public:
	//��������
	bool SetCustomRule(LPBYTE pcbCustomRule, WORD wCustomSize);
	//��������
	bool SaveCustomRule(LPBYTE pcbCustomRule, WORD wCustomSize);
	//Ĭ������
	bool DefaultCustomRule(LPBYTE pcbCustomRule, WORD wCustomSize);
	//����У��(�ؼ�������)
	bool CheckData();
	//ͨ��У��
	void FormatDataCheck(LONGLONG lCheckData,LONGLONG lMindata,LONGLONG lMaxdata,LPCTSTR strDataName,bool IsGeneralData);
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR,LRESULT *pResult);
	//���������������ʱ ɾ������������ѡ��
	void DeleteAndroid();
	//����У��
	bool CheckCustomRule();
	DECLARE_MESSAGE_MAP()
};
////////////////////////////////////////////////////////////////////////////////////////////