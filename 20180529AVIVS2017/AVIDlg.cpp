// AVIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AVI.h"
#include "AVIDlg.h"
#include <vfw.h> // 包含VFW头文件

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
int CAVIDlg::startxDest = 766 * 0.5 - 720*0.5*0.5;
int CAVIDlg::startyDest = (695 - 80)*0.5 - 480*0.5*0.5;
double CAVIDlg::scale = -0.5;
int CAVIDlg::flag = 0;
int CAVIDlg::sleeptime = 100;
// -1为不处理
int CAVIDlg::imageOpe = -1;
int CAVIDlg::isChanged = 0;
//水印处理
int CAVIDlg::WMx = 0;
int CAVIDlg::WMy = 0;
// 高斯模糊
// -1为不处理
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
	PAVIFILE pavif;	 // AVI文件指针
	AVIFILEINFO pfinfo; // AVI文件信息

	if(bImgPro)return;

	// 文件打开对话框
	CFileDialog dlg(true,"*.avi",NULL,NULL,"*.avi|*.avi||");
	if (dlg.DoModal()==IDOK)
	{
		strAviFilePath = dlg.GetPathName();
	}else
	{
		return;
	}
	
	// 打开视频文件,读取视频数据信息
	AVIFileInit(); // 初始化AVI库
	AVIFileOpen(&pavif,strAviFilePath,OF_READ,NULL); // 以只读的方式打开AVI文件
	AVIFileInfo(pavif,&pfinfo,sizeof(AVIFILEINFO)); // 获取AVI文件信息

	// 读取avi文件的长宽信息
	lImgWidth  = pfinfo.dwWidth; // 宽
	lImgHeight = pfinfo.dwHeight; // 高
	lImgLength = pfinfo.dwLength;


	AVIFileRelease(pavif); // 释放avi文件
	AVIFileExit();	// 释放avi库	
}

// 视频信号处理线程
UINT CAVIDlg::lpImgProThreadProc(LPVOID lpParam)
{
	CAVIDlg *pDlgWnd = (CAVIDlg*)lpParam; // 主窗口指针

	PAVIFILE pfile;	 // AVI文件指针
	AVIFILEINFO pfi; // AVI文件信息
	PAVISTREAM pavi; // AVI流
	AVISTREAMINFO psi; // AVI流信息
	PGETFRAME pgf; // 获得帧的指针
	BITMAPINFOHEADER bmih; // 位图信息头
	BYTE *lpbuff; // 视频数据指针
	long lNumFrames; // 总帧数
	long lFirstFrame; // 起始帧

	//创建帧操作类对象
	FrameProcess fp;

	// 初始化AVI库
	AVIFileInit(); 

	// 以只读的方式打开AVI文件
	int res = AVIFileOpen(&pfile, pDlgWnd->strAviFilePath, OF_READ,NULL);
	int n = GetLastError();
	if (res!=AVIERR_OK)
	{
		//an error occures
		if (pfile!=NULL)
			AVIFileRelease(pfile);
		return -1;
	}
	 
	// 获取AVI文件信息
	AVIFileInfo(pfile,&pfi,sizeof(AVIFILEINFO)); 
	
	// 获得视频流
	res = AVIFileGetStream(pfile,&pavi,streamtypeVIDEO,0);   
	if (res!=AVIERR_OK)
	{
		if (pavi!=NULL)
			AVIStreamRelease(pavi);
		AVIFileExit();
		return -1;
	}
	
	// 获得AVI流信息
	AVIStreamInfo(pavi,&psi,sizeof(AVISTREAMINFO)); 
	
	// 起始帧序号
	lFirstFrame=AVIStreamStart(pavi); 
	if (lFirstFrame==-1)
	{
		//Error getteing the frame inside the stream
		if (pavi!=NULL)
			AVIStreamRelease(pavi);
		AVIFileExit();
		return -1;
	}
	
	// AVI流的长度,即帧数
	lNumFrames = AVIStreamLength(pavi);
	if (lNumFrames==-1)
	{
		//Error getteing the number of frames inside the stream
		if (pavi!=NULL)
			AVIStreamRelease(pavi);
		AVIFileExit();
		return -1;
	}
	// 构造位图参数
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

	//定义一个黑色画刷
	CBrush Brush(RGB(240, 240, 240));

	dc.FillRect(&Rect1,&Brush);
	//获取未压缩的视频帧,即解压缩视频帧
	pgf=AVIStreamGetFrameOpen(pavi,&bmih); 
	
	if(pgf==NULL)
	{
		AfxMessageBox("获取解压缩的视频帧失败!");
		return -1;
	}
	
	int index=0;
	
	//总帧数
	CString totalFra;
	totalFra.Format(_T("%d"), lNumFrames);
	pDlgWnd->m_total_frame.SetWindowTextA(totalFra);

	CString currentFra;

	for(int i = lFirstFrame ; i < lNumFrames ; i++) // 循环处理每一帧
	{
		if (isChanged == 1) {
			dc.FillRect(&Rect1, &Brush);
			isChanged = 0;
		}
		//dc.FillRect(&Rect1, &Brush);
		index = i-lFirstFrame;

		// 获得指定帧的内存地址
		lpbuff=(BYTE *)AVIStreamGetFrame(pgf,index) + sizeof(BITMAPINFOHEADER);

		//--------------------------处理算法--------------------------//
		//__Begin
		// 如灰度化(功能扩展)
		switch (imageOpe)
		{
		case -1:
			break;
		case 0:
			// TODO 添加自己的水印图片
			lpbuff = fp.Watermark(lpbuff, bmih, "水印路径", WMx, WMy);
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
		//--------------------------处理算法--------------------------//

		//***********************************************************************
		// 该部分用于在对话框上进行显示
		// StretchDIBits()只能显示RGB格式的数据,显示前需把视频数据转为相应的格式
		//***********************************************************************
		::SetStretchBltMode(dc.m_hDC, COLORONCOLOR); 
		if (flag == 0) {
			// 缩放并显示当前帧的RGB图
			StretchDIBits(dc.m_hDC, startxDest, startyDest, bmih.biWidth*scale, bmih.biHeight*scale, 0, 0,
				bmih.biWidth, bmih.biHeight, /*待显示图像数据*/lpbuff, (BITMAPINFO *)&bmih, DIB_RGB_COLORS, SRCCOPY);
		}
		else {
			StretchDIBits(dc.m_hDC, 15, 50, bmih.biWidth*0.5, bmih.biHeight*0.5, 0, 0,
				bmih.biWidth, bmih.biHeight, /*待显示图像数据*/lpbuff, (BITMAPINFO *)&bmih, DIB_RGB_COLORS, SRCCOPY);
			StretchDIBits(dc.m_hDC, 378, 50, bmih.biWidth*0.5, bmih.biHeight*0.5, 0, 0,
				bmih.biWidth, bmih.biHeight, /*待显示图像数据*/lpbuff, (BITMAPINFO *)&bmih, DIB_RGB_COLORS, SRCCOPY);
			StretchDIBits(dc.m_hDC, 15, 300, bmih.biWidth*0.5, bmih.biHeight*0.5, 0, 0,
				bmih.biWidth, bmih.biHeight, /*待显示图像数据*/lpbuff, (BITMAPINFO *)&bmih, DIB_RGB_COLORS, SRCCOPY);
			StretchDIBits(dc.m_hDC, 378, 300, bmih.biWidth*0.5, bmih.biHeight*0.5, 0, 0,
				bmih.biWidth, bmih.biHeight, /*待显示图像数据*/lpbuff, (BITMAPINFO *)&bmih, DIB_RGB_COLORS, SRCCOPY);
		}
		currentFra.Format(_T("%d"), index+1);
		pDlgWnd->m_current_frame.SetWindowTextA(currentFra);
		//获取当前时间
		pDlgWnd->m_now_time.SetWindowTextA(pDlgWnd->getNowTime());

        //****************************************************************************
		// 延时:控制每帧处理的时间间隔(单位为ms,可自行修改)
		//****************************************************************************
		Sleep(sleeptime);
	}

	AVIStreamGetFrameClose(pgf);
	AVIFileRelease(pfile);
	AVIFileExit();	

	AfxMessageBox("视频数据处理结束!");
	pDlgWnd->bImgPro = false;

	//归位
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
	// 启动图像处理线程
	if(!bImgPro)
	{
		// 文件名为空则提醒导入文件
		if(strAviFilePath == "")
		{
			AfxMessageBox("请先导入AVI视频文件!");
			return;
		}

		if (scale < 0) {
			AfxMessageBox("请输入缩放倍数!");
			return;
		}

		// 启动线程
		ImgProThreadProc = AfxBeginThread(lpImgProThreadProc, this);
		ImgProThreadProc->m_bAutoDelete = true;
		bImgPro = true;
	}else
	{
		AfxMessageBox("正在进行视频数据处理...");
	}
	
	return;	
}

void CAVIDlg::OnBnClickedButton2()
{
	CString str;
	GetDlgItemText(IDC_EDIT1,str);

	if (str.IsEmpty()) {
		AfxMessageBox("请输入缩放倍数!");
		return;
	}

	scale = atof(str);

	
	if (scale > 1.0 || scale < 0) {
		AfxMessageBox("请输入大于0小于1.0的数字!已重置为默认倍数0.5!");
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
	//田字显示
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
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}


void CAVIDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}


void CAVIDlg::OnBnClickedButton8()
{
	CString str;
	GetDlgItemText(IDC_EDIT_X, str);
	WMx = atof(str);
	GetDlgItemText(IDC_EDIT_YGET, str);
	WMy = atof(str);
	// 水印处理
	imageOpe = 0;
}


void CAVIDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	// 灰度化处理
	imageOpe = 1;
}


void CAVIDlg::OnBnClickedButton10()
{
	// 垂直镜像
	imageOpe = 2;
}


void CAVIDlg::OnBnClickedButton11()
{
	// 水平镜像
	imageOpe = 3;
}


void CAVIDlg::OnBnClickedButton12()
{	
	CString str;
	GetDlgItemText(IDC_EDIT_SIGMA, str);
	sigma = atof(str);
	// 高斯模糊
	imageOpe = 4;
}

void CAVIDlg::OnBnClickedButton13()
{
	// 不做处理
	imageOpe = -1;
}


void CAVIDlg::OnEnChangeEditX()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}



void CAVIDlg::OnEnChangeEditYget()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CAVIDlg::OnEnChangeEditCget()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CAVIDlg::OnEnChangeEditSigma()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
