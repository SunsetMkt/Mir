// BilImages.h: interface for the CBilImages class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BILIMAGES_H__70D1402D_6C09_4CF9_B9A5_2F970298402D__INCLUDED_)
#define AFX_BILIMAGES_H__70D1402D_6C09_4CF9_B9A5_2F970298402D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct BilHeader
{	
	CHAR szTitle[4];
	INT iColorCount;
	INT iImageCount;
};

struct BilImage
{
	SHORT sWidth;
	SHORT sHeight;
	SHORT sOffsetX;
	SHORT sOffsetY;
	PBYTE pBits;
};

//这个机构就是用来保存在内存中的图片的。
struct BMPImage
{
	SHORT sWidth;      //保存在内存中的图片宽度
	SHORT sHeight;     //保存在内存中的图片高度
	PBYTE pBytes;      //保存在内存中的图片数据
	DWORD dwLastTick;  //访问的时间 这个就是用来计算访问的频率的了 算法: (现在时间 - 访问的时间 > 某个规定的时间) 则这个图片从内存中清除, 大家懂吧, 表示这个图片不常访问了
};

//例如 GetTickCount() - dwLastTick > 5*1000
//这个表示如果5秒内这个图片没有被访问过, 那么它将从内存中清除掉
//每当访问过这个图片那么dwLastTick = GetTickCount()这个字段就会被更新, 防止被清除出内存

class CBilImages  
{
public:
	CBilImages(const CString& szFileName); //这样表示创建这个类的时候必须关联一个BIL文件
	virtual ~CBilImages();
    
	//唯一公开的3个接口, 这样别人用这个类的时候就简单多了
	VOID DrawZoom(HDC hDC, INT iIndex, INT iX, INT iY, INT iZoom); //第一个参数DC, 呵呵, 一看就知道是怎么回事了吧, 这是一个跟GDI相关的函数, 它是一个绘图函数
	VOID DrawZoomEx(HDC hDC, INT iIndex, INT iX, INT iY, INT iZoom, BOOL bBottomUp); //下面这个也是
	INT GetImageCount(); //最后一个是返回BIL文件的图片数目的, 简单！

private: //private的意思就是私有的了。。怎么实现外界是看不到的。
	FILE* m_hFile;       //这个是BIL文件的文件句柄
	INT m_iImageCount;   //这个是这个BIL文件的图片数目
	INT m_iColorCount;   //BIL文件所支持的图片位数8或者16
	BMPImage* m_Images;  //这个就是缓存图片了, 在内存中的图片, 这个是个数组大小等于m_Images = new BMPImage[m_iImageCount], 注意这里只是创建了BMPImage结构的内存, BMPImage结构中的pBytes指针, 也就是图片数据指针可能为NULL, 表示图片数据不在内存中
	INT* m_Indexs;       //这个就是BIL文件中每个图片的索引了, 这个时候这个索引就体现出它的巨大作用了, 图片编辑器的时候还没体现出来, 这来就可以用来随机访问了, 由于有索引的存在, 所以可以快速地定位每个图片在文件中的位置并读出来
	DWORD m_dwClearCheckTick;	//这个就是清除缓存计数, 没过一段时间检查内存中的图片是否应该清除出内存
	BITMAPINFO* m_lpBitmapInfo; //这个是位图的结构用来绘图的, 图片编辑器那课已经讲的很清楚了

	VOID ClearOldImages(); //清理图片缓存工具函数
	VOID LoadBMPImage(INT iIndex, BMPImage* lpBMPImage); //这个就是根据图片的索引0 1 2 3 4。。。来获取图片, 这个是从硬盘中获取的, 所以叫LOAD
	PBYTE GetCacheImage(INT iIndex, INT& iWidth, INT& iHeight); //这个根据图片的索引0 1 2 3 4。。。来获取图片, 获取图片的宽度, 高度, 返回的是图片都是数据, 最后2个参数是引用参数可以输出的, 这个函数就不管是否从硬盘或内存中获取图片了, 它只要获取到图片就行了, 具体我们看代码就知道什么意思了
};

#endif // !defined(AFX_BILIMAGES_H__70D1402D_6C09_4CF9_B9A5_2F970298402D__INCLUDED_)
