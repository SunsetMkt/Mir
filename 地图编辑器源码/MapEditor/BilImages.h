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

//����������������������ڴ��е�ͼƬ�ġ�
struct BMPImage
{
	SHORT sWidth;      //�������ڴ��е�ͼƬ���
	SHORT sHeight;     //�������ڴ��е�ͼƬ�߶�
	PBYTE pBytes;      //�������ڴ��е�ͼƬ����
	DWORD dwLastTick;  //���ʵ�ʱ�� �����������������ʵ�Ƶ�ʵ��� �㷨: (����ʱ�� - ���ʵ�ʱ�� > ĳ���涨��ʱ��) �����ͼƬ���ڴ������, ��Ҷ���, ��ʾ���ͼƬ����������
};

//���� GetTickCount() - dwLastTick > 5*1000
//�����ʾ���5�������ͼƬû�б����ʹ�, ��ô�������ڴ��������
//ÿ�����ʹ����ͼƬ��ôdwLastTick = GetTickCount()����ֶξͻᱻ����, ��ֹ��������ڴ�

class CBilImages  
{
public:
	CBilImages(const CString& szFileName); //������ʾ����������ʱ��������һ��BIL�ļ�
	virtual ~CBilImages();
    
	//Ψһ������3���ӿ�, ����������������ʱ��ͼ򵥶���
	VOID DrawZoom(HDC hDC, INT iIndex, INT iX, INT iY, INT iZoom); //��һ������DC, �Ǻ�, һ����֪������ô�����˰�, ����һ����GDI��صĺ���, ����һ����ͼ����
	VOID DrawZoomEx(HDC hDC, INT iIndex, INT iX, INT iY, INT iZoom, BOOL bBottomUp); //�������Ҳ��
	INT GetImageCount(); //���һ���Ƿ���BIL�ļ���ͼƬ��Ŀ��, �򵥣�

private: //private����˼����˽�е��ˡ�����ôʵ������ǿ������ġ�
	FILE* m_hFile;       //�����BIL�ļ����ļ����
	INT m_iImageCount;   //��������BIL�ļ���ͼƬ��Ŀ
	INT m_iColorCount;   //BIL�ļ���֧�ֵ�ͼƬλ��8����16
	BMPImage* m_Images;  //������ǻ���ͼƬ��, ���ڴ��е�ͼƬ, ����Ǹ������С����m_Images = new BMPImage[m_iImageCount], ע������ֻ�Ǵ�����BMPImage�ṹ���ڴ�, BMPImage�ṹ�е�pBytesָ��, Ҳ����ͼƬ����ָ�����ΪNULL, ��ʾͼƬ���ݲ����ڴ���
	INT* m_Indexs;       //�������BIL�ļ���ÿ��ͼƬ��������, ���ʱ��������������ֳ����ľ޴�������, ͼƬ�༭����ʱ��û���ֳ���, �����Ϳ����������������, �����������Ĵ���, ���Կ��Կ��ٵض�λÿ��ͼƬ���ļ��е�λ�ò�������
	DWORD m_dwClearCheckTick;	//�����������������, û��һ��ʱ�����ڴ��е�ͼƬ�Ƿ�Ӧ��������ڴ�
	BITMAPINFO* m_lpBitmapInfo; //�����λͼ�Ľṹ������ͼ��, ͼƬ�༭���ǿ��Ѿ����ĺ������

	VOID ClearOldImages(); //����ͼƬ���湤�ߺ���
	VOID LoadBMPImage(INT iIndex, BMPImage* lpBMPImage); //������Ǹ���ͼƬ������0 1 2 3 4����������ȡͼƬ, ����Ǵ�Ӳ���л�ȡ��, ���Խ�LOAD
	PBYTE GetCacheImage(INT iIndex, INT& iWidth, INT& iHeight); //�������ͼƬ������0 1 2 3 4����������ȡͼƬ, ��ȡͼƬ�Ŀ��, �߶�, ���ص���ͼƬ��������, ���2�����������ò������������, ��������Ͳ����Ƿ��Ӳ�̻��ڴ��л�ȡͼƬ��, ��ֻҪ��ȡ��ͼƬ������, �������ǿ������֪��ʲô��˼��
};

#endif // !defined(AFX_BILIMAGES_H__70D1402D_6C09_4CF9_B9A5_2F970298402D__INCLUDED_)
