#pragma once

#include "StringMessage.h"

//////////////////////////////////////////////////////////////////////////////////

class CGameFrameWindow : public CFrameWnd, public IGameFrameWnd, public IUserEventSink
{
	//����ӿ�
protected:
	IClientKernel *					m_pIClientKernel;					//�ں˽ӿ�
	IGameFrameView *				m_pIGameFrameView;					//��ͼ�ӿ�
	IGameFrameService *				m_pIGameFrameService;				//��ܷ���

	//���ܿؼ�
public:
	CStringMessage					m_StringMessage;					//��Ϣ����
	CGameFrameControl				m_GameFrameControl;					//���ƿ��

	//��Ϸ�ؼ�
public:
	CSkinButton						m_btClose;							//�رհ�ť
	CSkinButton						m_btMin;							//��С��ť
	CSkinButton						m_btSound;							//������ť
	CSkinButton						m_btOption;							//���ð�ť

	//�����Դ
protected:
	//CPngImage						m_PngFrameTop;						//��ܱ���
	CDFontEx						m_DFontEx;							// ����
	CBitImage						m_ImageTop;

private:
	CSize							m_CurWindowSize;

	//��������
public:
	//���캯��
	CGameFrameWindow();
	//��������
	~CGameFrameWindow();

	//�����ӿ�
public:
	//�ͷŶ���
	virtual VOID Release() { delete this; }
	//�ӿڲ�ѯ
	virtual VOID * QueryInterface(REFGUID Guid, DWORD dwQueryVer);

	//���غ���
protected:
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	//�����
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	//�������
protected:
	//�����ؼ�
	VOID RectifyControl(INT nWidth, INT nHeight);
	//�����С
	void ReSetDlgSize(int cx,int cy);

	//���ڿ���
public:
	//��Ϸ����
	virtual bool ShowGameRule();
	//��󴰿�
	virtual bool MaxSizeWindow();
	//��ԭ����
	virtual bool RestoreWindow();

	//���ƽӿ�
public:
	//��������
	virtual bool AllowGameSound(bool bAllowSound);
	//�Թۿ���
	virtual bool AllowGameLookon(DWORD dwUserID, bool bAllowLookon);
	//���ƽӿ�
	virtual bool OnGameOptionChange();

	//�û��¼�
public:
	//�û�����
	virtual VOID OnEventUserEnter(IClientUserItem * pIClientUserItem, bool bLookonUser);
	//�û��뿪
	virtual VOID OnEventUserLeave(IClientUserItem * pIClientUserItem, bool bLookonUser);
	//�û�����
	virtual VOID OnEventUserScore(IClientUserItem * pIClientUserItem, bool bLookonUser);
	//�û�״̬
	virtual VOID OnEventUserStatus(IClientUserItem * pIClientUserItem, bool bLookonUser);
	//�û�ͷ��
	virtual VOID OnEventCustomFace(IClientUserItem * pIClientUserItem, bool bLookonUser);
	//�û�����
	virtual VOID OnEventUserAttrib(IClientUserItem * pIClientUserItem, bool bLookonUser);


	//��Ϣ����
protected:
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//λ����Ϣ
	VOID OnSize(UINT nType, INT cx, INT cy);
	//������Ϣ
	INT OnCreate(LPCREATESTRUCT lpCreateStruct);
	//�����Ϣ
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//�����Ϣ
	VOID OnLButtonDblClk(UINT nFlags, CPoint Point);
	//�ı���Ϣ
	VOID OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	//�������
	afx_msg LRESULT OnNcHitTest(CPoint point);

	//�Զ���Ϣ
protected:
	//������Ϣ
	LRESULT	OnSetTextMesage(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};

///////////////////////////////////////////////////////////////////////////////////