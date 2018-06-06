#include "stdafx.h"
#include "FrameProcess.h"


FrameProcess::FrameProcess()
{
}


FrameProcess::~FrameProcess()
{
}

BYTE * FrameProcess::Watermark(BYTE * lpbuff, BITMAPINFOHEADER bmih, const char * wmPath, int WMx, int WMy)
{
	//保证为3的倍数 使图像对齐
	WMx = WMx / 3 * 3;
	WMy = WMy / 3 * 3;

	FILE * fp;
	BITMAPFILEHEADER bitHead;
	BITMAPINFOHEADER infoHead;
	if (fopen_s(&fp, wmPath, "rb") != 0)      //图片路径可修改
	{
		cout << "这个文件不存在!" << endl;
		exit(0);
	}
	fread(&bitHead, 1, sizeof(BITMAPFILEHEADER), fp);

	if (fseek(fp, sizeof(BITMAPFILEHEADER), 0))
	{
		cout << "跳转失败" << endl;
	}
	fread(&infoHead, sizeof(BITMAPINFOHEADER), 1, fp);
	
	int height = infoHead.biHeight;
	int width = infoHead.biWidth;


	int yuantuSize = sizeof(lpbuff) / sizeof(lpbuff[0]);
	//一行的长度
	int changeWidth = (width*infoHead.biBitCount + 31) / 32 * 4;
	//原图一行的长度
	int trueWidth = (bmih.biWidth*bmih.biBitCount + 31) / 32 * 4;
	//对水印起始坐标进行判断
	if (WMx > trueWidth) {
		WMx = trueWidth - changeWidth;
	}
	if (WMy > bmih.biHeight) {
		WMy = bmih.biHeight - infoHead.biHeight;
	}
	//获取水印数据
	BYTE    *wmData = (BYTE *)malloc(height*changeWidth);
	memset(wmData, 0, height*changeWidth);

	fread(wmData, 1, height*changeWidth, fp);

	//int wmSize = sizeof(wmData) / sizeof(wmData[0]);

	int indexY = WMx +trueWidth* WMy;
	int indexWM = 0;

	//列
	for (int j = 0; j < height; j++) {
		//行
		for (int i = 0; i < changeWidth; i++) {
			if (wmData[indexWM] != 255) {
				lpbuff[indexY] = wmData[indexWM];
			}
			indexY++;
			indexWM++;
		}
		indexY = indexY + (trueWidth - changeWidth);
	}
	//释放空间
	delete []wmData;
	return lpbuff;
}

BYTE * FrameProcess::Grayscale(BYTE * lpbuff, BITMAPINFOHEADER bmih)
{
	//分量法、最大值法、平均值法、加权平均法
	//采用平均值法
	//f(i,j)=(R(i,j)+G(i,j)+B(i,j)) /3
	//加权平均法
	//f(i,j)=0.30R(i,j)+0.59G(i,j)+0.11B(i,j)
	int heightLP = bmih.biHeight;
	int widthLP = bmih.biWidth;
	//一行的像素
	int trueWidth = (bmih.biWidth*bmih.biBitCount + 31) / 32 * 4;
	//起点
	int indexY = 0;
	//列
	for (int j = 0; j < heightLP; j++) {
		//行
		for (int i = 0; i < trueWidth/3; i++) {
			//蓝色
			//lpbuff[indexY]
			//绿色
			//lpbuff[indexY + 1]
			//红色
			//lpbuff[indexY + 2]
			//平均值
			//avg = (BYTE)(lpbuff[indexY] + lpbuff[indexY + 1] + lpbuff[indexY + 2]);
			//加权平均
			lpbuff[indexY] = lpbuff[indexY + 1] = lpbuff[indexY + 2] = (BYTE)(0.11*lpbuff[indexY] + 0.59*lpbuff[indexY + 1] + 0.3*lpbuff[indexY + 2]);
			indexY+=3;
		}
	}

	return lpbuff;
}

BYTE * FrameProcess::VertMirr(BYTE * lpbuff, BITMAPINFOHEADER bmih)
{
	BYTE temp;
	int heightLP = bmih.biHeight;
	int widthLP = bmih.biWidth;
	//一行的像素
	int trueWidth = (bmih.biWidth*bmih.biBitCount + 31) / 32 * 4;
	//起点
	int indexY = 0;
	//列
	for (int j = 0; j < heightLP/2; j++) {
		int changeLine = (heightLP - j)*trueWidth /3 *3;
		//行
		for (int i = 0; i < trueWidth; i++) {
			temp = lpbuff[indexY];
			lpbuff[indexY] = lpbuff[changeLine + i];
			lpbuff[changeLine + i] = temp;
			indexY++;
		}
	}
	return lpbuff;
}

BYTE * FrameProcess::HoriMirr(BYTE * lpbuff, BITMAPINFOHEADER bmih)
{
	BYTE temp;
	int heightLP = bmih.biHeight;
	int widthLP = bmih.biWidth;
	//一行的像素
	int trueWidth = (bmih.biWidth*bmih.biBitCount + 31) / 32 * 4;
	//列
	for (int j = 0; j < heightLP; j++) {
		int changeLine = j* trueWidth;
		//行
		for (int i = 0; i < trueWidth/2+1; i++) {
			temp = lpbuff[i+changeLine];
			lpbuff[i + changeLine] = lpbuff[changeLine + trueWidth -i];
			lpbuff[changeLine + trueWidth - i] = temp;
		}
	}
	return lpbuff;
}

int * FrameProcess::buildGaussKern(int winSize, int sigma)
{
	int wincenter, x;
	float   sum = 0.0f;
	wincenter = winSize / 2;
	float *kern = (float*)malloc(winSize * sizeof(float));
	int *ikern = (int*)malloc(winSize * sizeof(int));
	float SQRT_2PI = 2.506628274631f;
	float sigmaMul2PI = 1.0f / (sigma * SQRT_2PI);
	float divSigmaPow2 = 1.0f / (2.0f * sigma * sigma);
	for (x = 0; x < wincenter + 1; x++)
	{
		kern[wincenter - x] = kern[wincenter + x] = exp(-(x * x)* divSigmaPow2) * sigmaMul2PI;
		sum += kern[wincenter - x] + ((x != 0) ? kern[wincenter + x] : 0.0);
	}
	sum = 1.0f / sum;
	for (x = 0; x < winSize; x++)
	{
		kern[x] *= sum;
		ikern[x] = kern[x] * 256.0f;
	}
	free(kern);
	return ikern;
}

BYTE * FrameProcess::GaussBlur(BYTE * lpbuff, BITMAPINFOHEADER bmih, int sigma)
{	
	int heightLP = bmih.biHeight;
	int widthLP = bmih.biWidth;
	//一行的像素
	int trueWidth = (bmih.biWidth*bmih.biBitCount + 31) / 32 * 4;

	int  winsize = (1 + (((int)ceil(3 * sigma)) * 2));
	int *gaussKern = buildGaussKern(winsize, sigma);
	winsize *= 3;
	int  halfsize = winsize / 2;

	BYTE *tmpBuffer = (BYTE*)malloc(trueWidth * heightLP * sizeof(BYTE));

	for (int h = 0; h < heightLP; h++)
	{
		int  rowWidth = h * trueWidth;

		for (int w = 0; w < trueWidth; w += 3)
		{
			int rowR = 0;
			int rowG = 0;
			int rowB = 0;
			int * gaussKernPtr = gaussKern;
			int whalfsize = w + trueWidth - halfsize;
			unsigned int  curPos = rowWidth + w;
			for (unsigned int k = 1; k < winsize; k += 3)
			{
				int  pos = rowWidth + ((k + whalfsize) % trueWidth);
				int fkern = *gaussKernPtr++;
				rowR += (lpbuff[pos] * fkern);
				rowG += (lpbuff[pos + 1] * fkern);
				rowB += (lpbuff[pos + 2] * fkern);
			}

			tmpBuffer[curPos] = ((BYTE)(rowR >> 8));
			tmpBuffer[curPos + 1] = ((BYTE)(rowG >> 8));
			tmpBuffer[curPos + 2] = ((BYTE)(rowB >> 8));

		}
	}
	winsize /= 3;
	halfsize = winsize / 2;
	for (int w = 0; w < trueWidth; w++)
	{
		for (int h = 0; h < heightLP; h++)
		{
			int col_all = 0;
			int hhalfsize = h + heightLP - halfsize;
			for (int k = 0; k < winsize; k++)
			{
				col_all += tmpBuffer[((k + hhalfsize) % heightLP)* trueWidth + w] * gaussKern[k];
			}
			lpbuff[h * trueWidth + w] = (BYTE)(col_all >> 8);
		}
	}
	free(tmpBuffer);
	free(gaussKern);
	return lpbuff;
}


