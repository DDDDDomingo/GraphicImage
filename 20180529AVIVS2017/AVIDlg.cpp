// AVIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AVI.h"
#include "AVIDlg.h"
#include <vfw.h> // ����VFWͷ�ļ�

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
int CAVIDlg::startxDest = 766 * 0.5 - 720*0.5*0.5;
int CAVIDlg::startyDest = (695 - 80)*0.5 - 480*0.5*0.5;
double CAVIDlg::scale = -0.5;
int CAVIDlg::flag = 0;
int CAVIDlg::sleeptime = 100;
// -1Ϊ������
int CAVIDlg::imageOpe = -1;
int CAVIDlg::isChanged = 0;
//ˮӡ����
int CAVIDlg::WMx = 0;
int CAVIDlg::WMy = 0;
// ��˹ģ��
// -1Ϊ������
int CAVIDlg::sigma = 10;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAVIDlg dialog

CAVIDlg::CAVIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAVIDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAVIDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAVIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CURRENT_FRAME, m_current_frame);
	DDX_Control(pDX, IDC_TOTAL_FRAME, m_total_frame);
	DDX_Control(pDX, IDC_NOW_TIME, m_now_time);

	//{{AFX_DATA_MAP(CAVIDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAVIDlg, CDialog)
	//{{AFX_MSG_MAP(CAVIDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN_BTN, OnOpenBtn)
	ON_BN_CLICKED(IDC_PRO_BTN, OnProBtn)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDABORT, &CAVIDlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT1, &CAVIDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON3, &CAVIDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CAVIDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &CAVIDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDOK, &CAVIDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON6, &CAVIDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CAVIDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDCANCEL, &CAVIDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CAVIDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON8, &CAVIDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CAVIDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CAVIDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CAVIDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CAVIDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CAVIDlg::OnBnClickedButton13)
	ON_EN_CHANGE(IDC_EDIT_X, &CAVIDlg::OnEnChangeEditX)
	ON_EN_CHANGE(IDC_EDIT_YGET, &CAVIDlg::OnEnChangeEditYget)
	ON_EN_CHANGE(IDC_EDIT_SIGMA, &CAVIDlg::OnEnChangeEditSigma)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAVIDlg message handlers

BOOL CAVIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.
	m_Menu.LoadMenu(IDR_MENU1);
	SetMenu(&m_Menu);


	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	strAviFilePath = "";
	bImgPro = false;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAVIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAVIDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cxIcon+ 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAVIDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAVIDlg::OnOpenBtn() 
{
	// TODO: Add your control notification handler code here
	PAVIFILE pavif;	 // AVI�ļ�ָ��
	AVIFILEINFO pfinfo; // AVI�ļ���Ϣ

	if(bImgPro)return;

	// �ļ��򿪶Ի���
	CFileDialog dlg(true,"*.avi",NULL,NULL,"*.avi|*.avi||");
	if (dlg.DoModal()==IDOK)
	{
		strAviFilePath = dlg.GetPathName();
	}else
	{
		return;
	}
	
	// ����Ƶ�ļ�,��ȡ��Ƶ������Ϣ
	AVIFileInit(); // ��ʼ��AVI��
	AVIFileOpen(&pavif,strAviFilePath,OF_READ,NULL); // ��ֻ���ķ�ʽ��AVI�ļ�
	AVIFileInfo(pavif,&pfinfo,sizeof(AVIFILEINFO)); // ��ȡAVI�ļ���Ϣ

	// ��ȡavi�ļ��ĳ�����Ϣ
	lImgWidth  = pfinfo.dwWidth; // ��
	lImgHeight = pfinfo.dwHeight; // ��
	lImgLength = pfinfo.dwLength;


	AVIFileRelease(pavif); // �ͷ�avi�ļ�
	AVIFileExit();	// �ͷ�avi��	
}

// ��Ƶ�źŴ����߳�
UINT CAVIDlg::lpImgProThreadProc(LPVOID lpParam)
{
	CAVIDlg *pDlgWnd = (CAVIDlg*)lpParam; // ������ָ��

	PAVIFILE pfile;	 // AVI�ļ�ָ��
	AVIFILEINFO pfi; // AVI�ļ���Ϣ
	PAVISTREAM pavi; // AVI��
	AVISTREAMINFO psi; // AVI����Ϣ
	PGETFRAME pgf; // ���֡��ָ��
	BITMAPINFOHEADER bmih; // λͼ��Ϣͷ
	BYTE *lpbuff; // ��Ƶ����ָ��
	long lNumFrames; // ��֡��
	long lFirstFrame; // ��ʼ֡

	//����֡���������
	FrameProcess fp;

	// ��ʼ��AVI��
	AVIFileInit(); 

	// ��ֻ���ķ�ʽ��AVI�ļ�
	int res = AVIFileOpen(&pfile, pDlgWnd->strAviFilePath, OF_READ,NULL);
	int n = GetLastError();
	if (res!=AVIERR_OK)
	{
		//an error occures
		if (pfile!=NULL)
			AVIFileRelease(pfile);
		return -1;
	}
	 
	// ��ȡAVI�ļ���Ϣ
	AVIFileInfo(pfile,&pfi,sizeof(AVIFILEINFO)); 
	
	// �����Ƶ��
	res = AVIFileGetStream(pfile,&pavi,streamtypeVIDEO,0);   
	if (res!=AVIERR_OK)
	{
		if (pavi!=NULL)
			AVIStreamRelease(pavi);
		AVIFileExit();
		return -1;
	}
	
	// ���AVI����Ϣ
	AVIStreamInfo(pavi,&psi,sizeof(AVISTREAMINFO)); 
	
	// ��ʼ֡���
	lFirstFrame=AVIStreamStart(pavi); 
	if (lFirstFrame==-1)
	{
		//Error getteing the frame inside the stream
		if (pavi!=NULL)
			AVIStreamRelease(pavi);
		AVIFileExit();
		return -1;
	}
	
	// AVI���ĳ���,��֡��
	lNumFrames = AVIStreamLength(pavi);
	if (lNumFrames==-1)
	{
		//Error getteing the number of frames inside the stream
		if (pavi!=NULL)
			AVIStreamRelease(pavi);
		AVIFileExit();
		return -1;
	}
	// ����λͼ����
	memset(&bmih,0,sizeof(BITMAPINFOHEADER));
	bmih.biBitCount=24;
	bmih.biSize = sizeof(BITMAPINFOHEADER);
	bmih.biWidth = pfi.dwWidth;
	bmih.biHeight = pfi.dwHeight;
	bmih.biCompression =BI_RGB;
	bmih.biPlanes =1;
	bmih.biXPelsPerMeter = 3780;
	bmih.biYPelsPerMeter = 3780;
	
	BITMAPFILEHEADER  bmfh;
	bmfh.bfSize  =  sizeof(bmfh);
    bmfh.bfOffBits  =  sizeof(bmfh)  +  sizeof(bmih);
	bmfh.bfType  =  (int)'M'*  256  +  'B';
	//bmfh.bfType=0x424D;
    bmfh.bfReserved1  =  0;
	bmfh.bfReserved2  =  0;


	CClientDC dc(pDlgWnd);


	RECT Rect1;
	Rect1.left = 10;
	Rect1.top = 10;
	Rect1.right = 740;
	Rect1.bottom = 565;

	//����һ����ɫ��ˢ
	CBrush Brush(RGB(240, 240, 240));

	dc.FillRect(&Rect1,&Brush);
	//��ȡδѹ������Ƶ֡,����ѹ����Ƶ֡
	pgf=AVIStreamGetFrameOpen(pavi,&bmih); 
	
	if(pgf==NULL)
	{
		AfxMessageBox("��ȡ��ѹ������Ƶ֡ʧ��!");
		return -1;
	}
	
	int index=0;
	
	//��֡��
	CString totalFra;
	totalFra.Format(_T("%d"), lNumFrames);
	pDlgWnd->m_total_frame.SetWindowTextA(totalFra);

	CString currentFra;

	for(int i = lFirstFrame ; i < lNumFrames ; i++) // ѭ������ÿһ֡
	{
		if (isChanged == 1) {
			dc.FillRect(&Rect1, &Brush);
			isChanged = 0;
		}
		//dc.FillRect(&Rect1, &Brush);
		index = i-lFirstFrame;

		// ���ָ��֡���ڴ��ַ
		lpbuff=(BYTE *)AVIStreamGetFrame(pgf,index) + sizeof(BITMAPINFOHEADER);

		//--------------------------�����㷨--------------------------//
		//__Begin
		// ��ҶȻ�(������չ)
		switch (imageOpe)
		{
		case -1:
			break;
		case 0:
			// TODO ����Լ���ˮӡͼƬ
			lpbuff = fp.Watermark(lpbuff, bmih, "ˮӡ·��", WMx, WMy);
			break;
		case 1:
			lpbuff = fp.Grayscale(lpbuff, bmih);
			break;
		case 2:
			lpbuff = fp.VertMirr(lpbuff, bmih);
			break;
		case 3:
			lpbuff = fp.HoriMirr(lpbuff, bmih);
			break;
		case 4:
			lpbuff = fp.GaussBlur(lpbuff, bmih, sigma);
			break;
		}
		//__End		
		//--------------------------�����㷨--------------------------//

		//***********************************************************************
		// �ò��������ڶԻ����Ͻ�����ʾ
		// StretchDIBits()ֻ����ʾRGB��ʽ������,��ʾǰ�����Ƶ����תΪ��Ӧ�ĸ�ʽ
		//***********************************************************************
		::SetStretchBltMode(dc.m_hDC, COLORONCOLOR); 
		if (flag == 0) {
			// ���Ų���ʾ��ǰ֡��RGBͼ
			StretchDIBits(dc.m_hDC, startxDest, startyDest, bmih.biWidth*scale, bmih.biHeight*scale, 0, 0,
				bmih.biWidth, bmih.biHeight, /*����ʾͼ������*/lpbuff, (BITMAPINFO *)&bmih, DIB_RGB_COLORS, SRCCOPY);
		}
		else {
			StretchDIBits(dc.m_hDC, 15, 50, bmih.biWidth*0.5, bmih.biHeight*0.5, 0, 0,
				bmih.biWidth, bmih.biHeight, /*����ʾͼ������*/lpbuff, (BITMAPINFO *)&bmih, DIB_RGB_COLORS, SRCCOPY);
			StretchDIBits(dc.m_hDC, 378, 50, bmih.biWidth*0.5, bmih.biHeight*0.5, 0, 0,
				bmih.biWidth, bmih.biHeight, /*����ʾͼ������*/lpbuff, (BITMAPINFO *)&bmih, DIB_RGB_COLORS, SRCCOPY);
			StretchDIBits(dc.m_hDC, 15, 300, bmih.biWidth*0.5, bmih.biHeight*0.5, 0, 0,
				bmih.biWidth, bmih.biHeight, /*����ʾͼ������*/lpbuff, (BITMAPINFO *)&bmih, DIB_RGB_COLORS, SRCCOPY);
			StretchDIBits(dc.m_hDC, 378, 300, bmih.biWidth*0.5, bmih.biHeight*0.5, 0, 0,
				bmih.biWidth, bmih.biHeight, /*����ʾͼ������*/lpbuff, (BITMAPINFO *)&bmih, DIB_RGB_COLORS, SRCCOPY);
		}
		currentFra.Format(_T("%d"), index+1);
		pDlgWnd->m_current_frame.SetWindowTextA(currentFra);
		//��ȡ��ǰʱ��
		pDlgWnd->m_now_time.SetWindowTextA(pDlgWnd->getNowTime());

        //****************************************************************************
		// ��ʱ:����ÿ֡�����ʱ����(��λΪms,�������޸�)
		//****************************************************************************
		Sleep(sleeptime);
	}

	AVIStreamGetFrameClose(pgf);
	AVIFileRelease(pfile);
	AVIFileExit();	

	AfxMessageBox("��Ƶ���ݴ������!");
	pDlgWnd->bImgPro = false;

	//��λ
	flag = 0;

	return 0;
}

CString CAVIDlg::getNowTime()
{
	time_t rawtime;
	time(&rawtime);
	char pblgtime[20];
	strftime(pblgtime, 20, "%Y-%m-%d %X", localtime(&rawtime));
	return pblgtime;
}

void CAVIDlg::OnProBtn() 
{
	// TODO: Add your control notification handler code here
	// ����ͼ�����߳�
	if(!bImgPro)
	{
		// �ļ���Ϊ�������ѵ����ļ�
		if(strAviFilePath == "")
		{
			AfxMessageBox("���ȵ���AVI��Ƶ�ļ�!");
			return;
		}

		if (scale < 0) {
			AfxMessageBox("���������ű���!");
			return;
		}

		// �����߳�
		ImgProThreadProc = AfxBeginThread(lpImgProThreadProc, this);
		ImgProThreadProc->m_bAutoDelete = true;
		bImgPro = true;
	}else
	{
		AfxMessageBox("���ڽ�����Ƶ���ݴ���...");
	}
	
	return;	
}

void CAVIDlg::OnBnClickedButton2()
{
	CString str;
	GetDlgItemText(IDC_EDIT1,str);

	if (str.IsEmpty()) {
		AfxMessageBox("���������ű���!");
		return;
	}

	scale = atof(str);

	
	if (scale > 1.0 || scale < 0) {
		AfxMessageBox("���������0С��1.0������!������ΪĬ�ϱ���0.5!");
		scale = 0.5;
		return;
	}

	startxDest = 373 - 360 * scale;
	startyDest = 615 * 0.5 - 240 * scale;

	isChanged = 1;
}



void CAVIDlg::OnEnChangeEdit1()
{

}


void CAVIDlg::OnBnClickedButton3()
{
	//������ʾ
	flag = 1;
	isChanged = 1;
}

void CAVIDlg::OnBnClickedButton4()
{
	// 100ms
	sleeptime = 100;
}

void CAVIDlg::OnBnClickedButton5()
{
	// 500ms
	sleeptime = 500;
}

void CAVIDlg::OnBnClickedButton6()
{
	// 1s
	sleeptime = 1000;
}


void CAVIDlg::OnBnClickedButton7()
{
	// 2s
	sleeptime = 2000;
}


void CAVIDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}


void CAVIDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();
}


void CAVIDlg::OnBnClickedButton8()
{
	CString str;
	GetDlgItemText(IDC_EDIT_X, str);
	WMx = atof(str);
	GetDlgItemText(IDC_EDIT_YGET, str);
	WMy = atof(str);
	// ˮӡ����
	imageOpe = 0;
}


void CAVIDlg::OnBnClickedButton9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// �ҶȻ�����
	imageOpe = 1;
}


void CAVIDlg::OnBnClickedButton10()
{
	// ��ֱ����
	imageOpe = 2;
}


void CAVIDlg::OnBnClickedButton11()
{
	// ˮƽ����
	imageOpe = 3;
}


void CAVIDlg::OnBnClickedButton12()
{	
	CString str;
	GetDlgItemText(IDC_EDIT_SIGMA, str);
	sigma = atof(str);
	// ��˹ģ��
	imageOpe = 4;
}

void CAVIDlg::OnBnClickedButton13()
{
	// ��������
	imageOpe = -1;
}


void CAVIDlg::OnEnChangeEditX()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}



void CAVIDlg::OnEnChangeEditYget()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CAVIDlg::OnEnChangeEditCget()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CAVIDlg::OnEnChangeEditSigma()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
