// BilImages.cpp: implementation of the CBilImages class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MapEditor.h"
#include "BilImages.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBilImages::CBilImages(const CString& szFileName)
{
	m_hFile = NULL;
	m_iImageCount = 0;
	m_Images = NULL;
	m_Indexs = NULL;
	m_dwClearCheckTick = GetTickCount();	
	m_lpBitmapInfo = NULL;					//数据变量的初始化, C++的好习惯。。。
	
	if (szFileName != "")
	{
		m_hFile = fopen(szFileName, "rb");  //打开BIL文件
	}
	
	if (m_hFile)
	{
		BilHeader stBilHeader;   //这段就是分析BIL文件了
		
		fread(&stBilHeader, 1, sizeof(stBilHeader), m_hFile); //读取BIL文件头
		if (strcmp(stBilHeader.szTitle, "bil")) //检查是否是BIL文件
		{
			fclose(m_hFile);
			m_hFile = NULL;
			return;
		}
		m_iColorCount = stBilHeader.iColorCount;  //保存BIL支持的位图位数
		m_iImageCount = stBilHeader.iImageCount;  //保存BIL中的图片数目
		m_Images = new BMPImage[m_iImageCount];   //预先创建好跟图片数目一样的BMPImage结构
		memset(m_Images, 0, m_iImageCount*sizeof(BMPImage)); //清空这个内存, 表示所有图片均没读入内存
		m_Indexs = new INT[m_iImageCount];  //分配索引内存
		if (stBilHeader.iColorCount == 8) //假如是8位BIL文件
		{
			m_lpBitmapInfo = (BITMAPINFO*)new CHAR[sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*256];
			m_lpBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			m_lpBitmapInfo->bmiHeader.biWidth = 0;
			m_lpBitmapInfo->bmiHeader.biHeight = 0;
			m_lpBitmapInfo->bmiHeader.biPlanes = 1;
			m_lpBitmapInfo->bmiHeader.biBitCount = 8;
			m_lpBitmapInfo->bmiHeader.biCompression = BI_RGB;    
			m_lpBitmapInfo->bmiHeader.biSizeImage = 0;          
			m_lpBitmapInfo->bmiHeader.biXPelsPerMeter = 0;
			m_lpBitmapInfo->bmiHeader.biYPelsPerMeter = 0;
			m_lpBitmapInfo->bmiHeader.biClrUsed = 0;
			m_lpBitmapInfo->bmiHeader.biClrImportant = 0; //这里就按照8位的位图来初始化m_lpBitmapInfo了
			
			fread(m_lpBitmapInfo->bmiColors, 1, sizeof(RGBQUAD)*256, m_hFile); //还得读取调色板
		}
		else
		{
			m_lpBitmapInfo = (BITMAPINFO*)new CHAR[sizeof(BITMAPINFOHEADER)];
			m_lpBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			m_lpBitmapInfo->bmiHeader.biWidth = 0;
			m_lpBitmapInfo->bmiHeader.biHeight = 0;
			m_lpBitmapInfo->bmiHeader.biPlanes = 1;
			m_lpBitmapInfo->bmiHeader.biBitCount = 16;
			m_lpBitmapInfo->bmiHeader.biCompression = BI_RGB;    
			m_lpBitmapInfo->bmiHeader.biSizeImage = 0;          
			m_lpBitmapInfo->bmiHeader.biXPelsPerMeter = 0;
			m_lpBitmapInfo->bmiHeader.biYPelsPerMeter = 0;
			m_lpBitmapInfo->bmiHeader.biClrUsed = 0;
			m_lpBitmapInfo->bmiHeader.biClrImportant = 0; //16位的就按照16位来初始化m_lpBitmapInfo
		}
		fread(m_Indexs, 1, m_iImageCount*sizeof(INT), m_hFile); //最好读取索引, 这个BIL文件分析完毕
	}
}

CBilImages::~CBilImages()
{   //这个必须的, C++由我们自己进行内存管理, 所以创建了什么 就得释放什么, 以免内存泄露, 特别是服务器是不允许的, 因为服务器是1年365天地运行, 就算1天泄露一点, 那么最后整个服务器就会跑不动了
	for (INT i = 0; i < m_iImageCount; ++i)
	{
		delete[] m_Images[i].pBytes;
	} //清除我们的BMPImage结构, pBytes可能为NULL, 不过C++ delete NULL是合法的。
	delete[] m_Images; //删除图片结构内存
	delete[] m_Indexs; //删除索引内存
	delete[] (LPSTR)m_lpBitmapInfo; //删除位图结构
	if (m_hFile)//关闭文件
	{
		fclose(m_hFile);
	}
}
//下面我们来看看这个2个GDI函数究竟要画些什么东西吧
//首先我们看它的参数, hDC设备句柄, iIndex图片的索引, iX在DC中的坐标, iY在DC中的坐标, iZoom就是放大缩小的参数了, 演示的时候大家都看到地图编辑器中的放大和缩小按钮吧, 就靠这个实现的了
//看完整个代码DrawZoom实现的功能就是按传入的图片索引、坐标、和缩放大小进行绘制, 不过这个函数不能进行透明绘制, 所以我们就有了下面的函数了EX
VOID CBilImages::DrawZoom(HDC hDC, INT iIndex, INT iX, INT iY, INT iZoom)
{
	INT iWidth, iHeight;  //图片宽、搞
	HBITMAP hOldBitmap, hBitmap; //位图句柄
	HDC hImageDC; //内存DC
	PBYTE pBytes = GetCacheImage(iIndex, iWidth, iHeight); //获取图片数据
	
	if (pBytes)
	{
		m_lpBitmapInfo->bmiHeader.biWidth = iWidth;
		m_lpBitmapInfo->bmiHeader.biHeight = iHeight; //设置绘制位图用的结构, 设置宽和高
		//由DIB数据创建DDB位图
		hBitmap = CreateDIBitmap(hDC, &m_lpBitmapInfo->bmiHeader, CBM_INIT, pBytes, m_lpBitmapInfo, DIB_RGB_COLORS);
		//创建内存DC
		hImageDC = CreateCompatibleDC(hDC);
		//选图片的DDB进内存DC中
		hOldBitmap = (HBITMAP)SelectObject(hImageDC, hBitmap);
		//有了这个DC就可以画了
		//这个由于用到放大和缩小, 所以肯定用到StretchBlt了, 所以得设置拉伸的模式
		SetStretchBltMode(hDC, COLORONCOLOR); //这里设置了, 忘记的可以回顾一下图片编辑器课程的位图部分
		//下面就是绘制了, 具体的每个参数的意思大家都应该知道了, 我们主要关注这2个部分
		//目标的大小, (iWidth*iZoom + 99)/100, (iHeight*iZoom + 99)/100
		//iZoom的取值范围是1-100, 表示缩放的百分比
		//按照一般的数学方法应该是iWidth*iZoom/100, iHeight*iZoom/100
		//加99再除, 表示除法假如有小数点或者叫余数, 我们则加1, 取高的值, 例如5/3 结果为1 余数为2 那么我们就取5/3 = 2
		//为什么要往高的取, 因为这关乎到是否多一个像素和小一个像素的问题, 假如小一个像素就不好看了, 多一个像素则无所谓
		//下面我们来演示一下这个原因, 看到这空隙没, 这个就是用iWidth*iZoom/100, iHeight*iZoom/100算法的后果, 因为C++的整形除总是会往下取的, 这样很多时候就会少了一个像素, 所以我们要往上取, 就要加99了, 这个希望大家可以理解吧, 呵呵, 或者大家可以自己试试
		StretchBlt(hDC, iX, iY, (iWidth*iZoom + 99)/100, (iHeight*iZoom + 99)/100, hImageDC, 0, 0, iWidth, iHeight, SRCCOPY);
		SelectObject(hImageDC, hOldBitmap); //下面就是清理资源了
		DeleteDC(hImageDC);
		DeleteObject(hBitmap);
	}
}

//前面几个参数都跟上面的一样, 可是最后一个参数是什么意思呢? 
//看到么, 图片是向上画的, 不是从格子相下画的, 当bBottonUp为FALSE时, 当我点那个格子的时候应该是按照这样画的,
//可是当TRUE的时候就竖了上去了, 这个是为了绘制OBJ而设置的, 表示这个地面物体时扎根在这个格子里, 不过图片是往上竖起来的
//而且这个函数还带了透明的功能
VOID CBilImages::DrawZoomEx(HDC hDC, INT iIndex, INT iX, INT iY, INT iZoom, BOOL bBottomUp)
{
	INT iWidth, iHeight;
	HBITMAP hOldBitmap, hBitmap;
	HDC hImageDC;
	PBYTE pBytes = GetCacheImage(iIndex, iWidth, iHeight);
	
	if (pBytes)
	{
		m_lpBitmapInfo->bmiHeader.biWidth = iWidth;
		m_lpBitmapInfo->bmiHeader.biHeight = iHeight;
		hBitmap = CreateDIBitmap(hDC, &m_lpBitmapInfo->bmiHeader, CBM_INIT, pBytes, m_lpBitmapInfo, DIB_RGB_COLORS);
		hImageDC = CreateCompatibleDC(hDC);
		hOldBitmap = (HBITMAP)SelectObject(hImageDC, hBitmap); //前面的都跟上面的一样
		//下面的就不一样了用了TransparentBlt, 把黑色的透明色过滤掉
		if (bBottomUp)
		{
			//假如为TRUE, 则要往上竖了iY - (iHeight*iZoom + 99)/100, 计算了往上竖后应该画的坐标
			TransparentBlt(hDC, iX, iY - (iHeight*iZoom + 99)/100, (iWidth*iZoom + 99)/100, (iHeight*iZoom + 99)/100, hImageDC, 0, 0, iWidth, iHeight, 0);
		}
		else
		{   //假如为FALSE就跟上面的一样了, 按照正常情况绘制
			TransparentBlt(hDC, iX, iY, (iWidth*iZoom + 99)/100, (iHeight*iZoom + 99)/100, hImageDC, 0, 0, iWidth, iHeight, 0);
		}
		SelectObject(hImageDC, hOldBitmap); //释放资源
		DeleteDC(hImageDC);
		DeleteObject(hBitmap);
	}
}

INT CBilImages::GetImageCount()
{
	return m_iImageCount;//就这样搞定
}

VOID CBilImages::ClearOldImages()
{
	for (INT i = 0; i < m_iImageCount; ++i)  //检查所有图片结构
	{
		if (m_Images[i].pBytes) //如果pBytes不为NULL表示这个图片已经载入到内存中了
		{
			if ((GetTickCount() - m_Images[i].dwLastTick) > 5 * 60 * 1000) //这个就是刚刚说的算法, 现在这个时间就是5分钟 1000毫秒等于1秒
			{
				delete[] m_Images[i].pBytes; //删除图片的数据
				m_Images[i].pBytes = NULL; //设置为NULL, 表示图片数据已经从内存中清除
			}
		}
	}
}

VOID CBilImages::LoadBMPImage(INT iIndex, BMPImage* lpBMPImage) //从硬盘中获取
{
	BilImage stBilImage;
	PBYTE pBytes;
	
	fseek(m_hFile, m_Indexs[iIndex], SEEK_SET); //利用图片的索引迅速定位所要图片在文件中位置
	fread(&stBilImage, 1, sizeof(BilImage) - 4, m_hFile); //读取图片sizeof(BilImage) - 4我在图片编辑器中讲过的
	lpBMPImage->sWidth = stBilImage.sWidth;  //获取宽度
	lpBMPImage->sHeight = stBilImage.sHeight; //获取高度
	pBytes = new BYTE[((((stBilImage.sWidth * m_iColorCount) + 31) / 32) * 4)*stBilImage.sHeight]; //分配内存
	fread(pBytes, 1, ((((stBilImage.sWidth * m_iColorCount) + 31) / 32) * 4)*stBilImage.sHeight, m_hFile); //读取图片数据, 不记得这个图片大小计算公式的可以回顾一下图片编辑器中的位图那课
	
	lpBMPImage->pBytes = pBytes; //这里把读到的内存指针赋值给BMPImage, 这样整个图片就读取完毕
}

PBYTE CBilImages::GetCacheImage(INT iIndex, INT& iWidth, INT& iHeight) //获取图片, 忽略掉硬盘与内存的细节
{
	if (!m_Images || !m_Indexs || iIndex < 0 || iIndex >= m_iImageCount) //检查BIL文件的合法性, iIndex合法性
		return NULL;
	
	if (GetTickCount() - m_dwClearCheckTick > 10000) //这里顺便做清理, 每次获取图片都会检查清理, 10秒检查一次
	{
		m_dwClearCheckTick = GetTickCount();
		ClearOldImages();
	}
	
	if (m_Images[iIndex].pBytes) //如果这个图片已经读到缓存中, 内存中, 则直接返回, 快速方便
	{
		m_Images[iIndex].dwLastTick = GetTickCount(); //设置访问时间
		iWidth = m_Images[iIndex].sWidth;   //赋值给引用参数返回宽度
		iHeight = m_Images[iIndex].sHeight; //赋值给引用参数返回高度
		return m_Images[iIndex].pBytes; //直接返回图片数据指针
	}
	else
	{   //这里就是表示图片没读到内存中, 需要从硬盘中加载
		LoadBMPImage(iIndex, &m_Images[iIndex]);  //加载图片, 传入图片索引, 和内存图片结构指针
		m_Images[iIndex].dwLastTick = GetTickCount(); //设置访问时间
		iWidth = m_Images[iIndex].sWidth;    //赋值给引用参数返回宽度
		iHeight = m_Images[iIndex].sHeight;  //赋值给引用参数返回高度 
		return m_Images[iIndex].pBytes;  //直接返回图片数据指针
	}
}