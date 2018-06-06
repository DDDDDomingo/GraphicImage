#pragma once
#include <iostream>
#include <windows.h>

using namespace std;

typedef struct
{
	BYTE b;
	BYTE g;
	BYTE r;
}RGB;

class FrameProcess
{
public:
	FrameProcess();
	~FrameProcess();
	BYTE * Watermark(BYTE *lpbuff, BITMAPINFOHEADER bmih, const char * wmPath, int x, int y);
	BYTE * Grayscale(BYTE *lpbuff, BITMAPINFOHEADER bmih);
	//��ֱ����
	BYTE * VertMirr(BYTE *lpbuff, BITMAPINFOHEADER bmih);
	BYTE * HoriMirr(BYTE *lpbuff, BITMAPINFOHEADER bmih);
	//��˹�˾�
	int* buildGaussKern(int winSize, int sigma);
	//��˹ģ��
	BYTE * GaussBlur(BYTE * lpbuff, BITMAPINFOHEADER bmih, int sigma);
};

