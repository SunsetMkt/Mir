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
	m_lpBitmapInfo = NULL;					//���ݱ����ĳ�ʼ��, C++�ĺ�ϰ�ߡ�����
	
	if (szFileName != "")
	{
		m_hFile = fopen(szFileName, "rb");  //��BIL�ļ�
	}
	
	if (m_hFile)
	{
		BilHeader stBilHeader;   //��ξ��Ƿ���BIL�ļ���
		
		fread(&stBilHeader, 1, sizeof(stBilHeader), m_hFile); //��ȡBIL�ļ�ͷ
		if (strcmp(stBilHeader.szTitle, "bil")) //����Ƿ���BIL�ļ�
		{
			fclose(m_hFile);
			m_hFile = NULL;
			return;
		}
		m_iColorCount = stBilHeader.iColorCount;  //����BIL֧�ֵ�λͼλ��
		m_iImageCount = stBilHeader.iImageCount;  //����BIL�е�ͼƬ��Ŀ
		m_Images = new BMPImage[m_iImageCount];   //Ԥ�ȴ����ø�ͼƬ��Ŀһ����BMPImage�ṹ
		memset(m_Images, 0, m_iImageCount*sizeof(BMPImage)); //�������ڴ�, ��ʾ����ͼƬ��û�����ڴ�
		m_Indexs = new INT[m_iImageCount];  //���������ڴ�
		if (stBilHeader.iColorCount == 8) //������8λBIL�ļ�
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
			m_lpBitmapInfo->bmiHeader.biClrImportant = 0; //����Ͱ���8λ��λͼ����ʼ��m_lpBitmapInfo��
			
			fread(m_lpBitmapInfo->bmiColors, 1, sizeof(RGBQUAD)*256, m_hFile); //���ö�ȡ��ɫ��
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
			m_lpBitmapInfo->bmiHeader.biClrImportant = 0; //16λ�ľͰ���16λ����ʼ��m_lpBitmapInfo
		}
		fread(m_Indexs, 1, m_iImageCount*sizeof(INT), m_hFile); //��ö�ȡ����, ���BIL�ļ��������
	}
}

CBilImages::~CBilImages()
{   //��������, C++�������Լ������ڴ����, ���Դ�����ʲô �͵��ͷ�ʲô, �����ڴ�й¶, �ر��Ƿ������ǲ������, ��Ϊ��������1��365�������, ����1��й¶һ��, ��ô��������������ͻ��ܲ�����
	for (INT i = 0; i < m_iImageCount; ++i)
	{
		delete[] m_Images[i].pBytes;
	} //������ǵ�BMPImage�ṹ, pBytes����ΪNULL, ����C++ delete NULL�ǺϷ��ġ�
	delete[] m_Images; //ɾ��ͼƬ�ṹ�ڴ�
	delete[] m_Indexs; //ɾ�������ڴ�
	delete[] (LPSTR)m_lpBitmapInfo; //ɾ��λͼ�ṹ
	if (m_hFile)//�ر��ļ�
	{
		fclose(m_hFile);
	}
}
//�����������������2��GDI��������Ҫ��Щʲô������
//�������ǿ����Ĳ���, hDC�豸���, iIndexͼƬ������, iX��DC�е�����, iY��DC�е�����, iZoom���ǷŴ���С�Ĳ�����, ��ʾ��ʱ���Ҷ�������ͼ�༭���еķŴ����С��ť��, �Ϳ����ʵ�ֵ���
//������������DrawZoomʵ�ֵĹ��ܾ��ǰ������ͼƬ���������ꡢ�����Ŵ�С���л���, ��������������ܽ���͸������, �������Ǿ���������ĺ�����EX
VOID CBilImages::DrawZoom(HDC hDC, INT iIndex, INT iX, INT iY, INT iZoom)
{
	INT iWidth, iHeight;  //ͼƬ����
	HBITMAP hOldBitmap, hBitmap; //λͼ���
	HDC hImageDC; //�ڴ�DC
	PBYTE pBytes = GetCacheImage(iIndex, iWidth, iHeight); //��ȡͼƬ����
	
	if (pBytes)
	{
		m_lpBitmapInfo->bmiHeader.biWidth = iWidth;
		m_lpBitmapInfo->bmiHeader.biHeight = iHeight; //���û���λͼ�õĽṹ, ���ÿ�͸�
		//��DIB���ݴ���DDBλͼ
		hBitmap = CreateDIBitmap(hDC, &m_lpBitmapInfo->bmiHeader, CBM_INIT, pBytes, m_lpBitmapInfo, DIB_RGB_COLORS);
		//�����ڴ�DC
		hImageDC = CreateCompatibleDC(hDC);
		//ѡͼƬ��DDB���ڴ�DC��
		hOldBitmap = (HBITMAP)SelectObject(hImageDC, hBitmap);
		//�������DC�Ϳ��Ի���
		//��������õ��Ŵ����С, ���Կ϶��õ�StretchBlt��, ���Ե����������ģʽ
		SetStretchBltMode(hDC, COLORONCOLOR); //����������, ���ǵĿ��Իع�һ��ͼƬ�༭���γ̵�λͼ����
		//������ǻ�����, �����ÿ����������˼��Ҷ�Ӧ��֪����, ������Ҫ��ע��2������
		//Ŀ��Ĵ�С, (iWidth*iZoom + 99)/100, (iHeight*iZoom + 99)/100
		//iZoom��ȡֵ��Χ��1-100, ��ʾ���ŵİٷֱ�
		//����һ�����ѧ����Ӧ����iWidth*iZoom/100, iHeight*iZoom/100
		//��99�ٳ�, ��ʾ����������С������߽�����, �������1, ȡ�ߵ�ֵ, ����5/3 ���Ϊ1 ����Ϊ2 ��ô���Ǿ�ȡ5/3 = 2
		//ΪʲôҪ���ߵ�ȡ, ��Ϊ��غ����Ƿ��һ�����غ�Сһ�����ص�����, ����Сһ�����ؾͲ��ÿ���, ��һ������������ν
		//������������ʾһ�����ԭ��, �������϶û, ���������iWidth*iZoom/100, iHeight*iZoom/100�㷨�ĺ��, ��ΪC++�����γ����ǻ�����ȡ��, �����ܶ�ʱ��ͻ�����һ������, ��������Ҫ����ȡ, ��Ҫ��99��, ���ϣ����ҿ�������, �Ǻ�, ���ߴ�ҿ����Լ�����
		StretchBlt(hDC, iX, iY, (iWidth*iZoom + 99)/100, (iHeight*iZoom + 99)/100, hImageDC, 0, 0, iWidth, iHeight, SRCCOPY);
		SelectObject(hImageDC, hOldBitmap); //�������������Դ��
		DeleteDC(hImageDC);
		DeleteObject(hBitmap);
	}
}

//ǰ�漸���������������һ��, �������һ��������ʲô��˼��? 
//����ô, ͼƬ�����ϻ���, ���ǴӸ������»���, ��bBottonUpΪFALSEʱ, ���ҵ��Ǹ����ӵ�ʱ��Ӧ���ǰ�����������,
//���ǵ�TRUE��ʱ���������ȥ��, �����Ϊ�˻���OBJ�����õ�, ��ʾ�����������ʱ���������������, ����ͼƬ��������������
//�����������������͸���Ĺ���
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
		hOldBitmap = (HBITMAP)SelectObject(hImageDC, hBitmap); //ǰ��Ķ��������һ��
		//����ľͲ�һ��������TransparentBlt, �Ѻ�ɫ��͸��ɫ���˵�
		if (bBottomUp)
		{
			//����ΪTRUE, ��Ҫ��������iY - (iHeight*iZoom + 99)/100, ��������������Ӧ�û�������
			TransparentBlt(hDC, iX, iY - (iHeight*iZoom + 99)/100, (iWidth*iZoom + 99)/100, (iHeight*iZoom + 99)/100, hImageDC, 0, 0, iWidth, iHeight, 0);
		}
		else
		{   //����ΪFALSE�͸������һ����, ���������������
			TransparentBlt(hDC, iX, iY, (iWidth*iZoom + 99)/100, (iHeight*iZoom + 99)/100, hImageDC, 0, 0, iWidth, iHeight, 0);
		}
		SelectObject(hImageDC, hOldBitmap); //�ͷ���Դ
		DeleteDC(hImageDC);
		DeleteObject(hBitmap);
	}
}

INT CBilImages::GetImageCount()
{
	return m_iImageCount;//�������㶨
}

VOID CBilImages::ClearOldImages()
{
	for (INT i = 0; i < m_iImageCount; ++i)  //�������ͼƬ�ṹ
	{
		if (m_Images[i].pBytes) //���pBytes��ΪNULL��ʾ���ͼƬ�Ѿ����뵽�ڴ�����
		{
			if ((GetTickCount() - m_Images[i].dwLastTick) > 5 * 60 * 1000) //������Ǹո�˵���㷨, �������ʱ�����5���� 1000�������1��
			{
				delete[] m_Images[i].pBytes; //ɾ��ͼƬ������
				m_Images[i].pBytes = NULL; //����ΪNULL, ��ʾͼƬ�����Ѿ����ڴ������
			}
		}
	}
}

VOID CBilImages::LoadBMPImage(INT iIndex, BMPImage* lpBMPImage) //��Ӳ���л�ȡ
{
	BilImage stBilImage;
	PBYTE pBytes;
	
	fseek(m_hFile, m_Indexs[iIndex], SEEK_SET); //����ͼƬ������Ѹ�ٶ�λ��ҪͼƬ���ļ���λ��
	fread(&stBilImage, 1, sizeof(BilImage) - 4, m_hFile); //��ȡͼƬsizeof(BilImage) - 4����ͼƬ�༭���н�����
	lpBMPImage->sWidth = stBilImage.sWidth;  //��ȡ���
	lpBMPImage->sHeight = stBilImage.sHeight; //��ȡ�߶�
	pBytes = new BYTE[((((stBilImage.sWidth * m_iColorCount) + 31) / 32) * 4)*stBilImage.sHeight]; //�����ڴ�
	fread(pBytes, 1, ((((stBilImage.sWidth * m_iColorCount) + 31) / 32) * 4)*stBilImage.sHeight, m_hFile); //��ȡͼƬ����, ���ǵ����ͼƬ��С���㹫ʽ�Ŀ��Իع�һ��ͼƬ�༭���е�λͼ�ǿ�
	
	lpBMPImage->pBytes = pBytes; //����Ѷ������ڴ�ָ�븳ֵ��BMPImage, ��������ͼƬ�Ͷ�ȡ���
}

PBYTE CBilImages::GetCacheImage(INT iIndex, INT& iWidth, INT& iHeight) //��ȡͼƬ, ���Ե�Ӳ�����ڴ��ϸ��
{
	if (!m_Images || !m_Indexs || iIndex < 0 || iIndex >= m_iImageCount) //���BIL�ļ��ĺϷ���, iIndex�Ϸ���
		return NULL;
	
	if (GetTickCount() - m_dwClearCheckTick > 10000) //����˳��������, ÿ�λ�ȡͼƬ����������, 10����һ��
	{
		m_dwClearCheckTick = GetTickCount();
		ClearOldImages();
	}
	
	if (m_Images[iIndex].pBytes) //������ͼƬ�Ѿ�����������, �ڴ���, ��ֱ�ӷ���, ���ٷ���
	{
		m_Images[iIndex].dwLastTick = GetTickCount(); //���÷���ʱ��
		iWidth = m_Images[iIndex].sWidth;   //��ֵ�����ò������ؿ��
		iHeight = m_Images[iIndex].sHeight; //��ֵ�����ò������ظ߶�
		return m_Images[iIndex].pBytes; //ֱ�ӷ���ͼƬ����ָ��
	}
	else
	{   //������Ǳ�ʾͼƬû�����ڴ���, ��Ҫ��Ӳ���м���
		LoadBMPImage(iIndex, &m_Images[iIndex]);  //����ͼƬ, ����ͼƬ����, ���ڴ�ͼƬ�ṹָ��
		m_Images[iIndex].dwLastTick = GetTickCount(); //���÷���ʱ��
		iWidth = m_Images[iIndex].sWidth;    //��ֵ�����ò������ؿ��
		iHeight = m_Images[iIndex].sHeight;  //��ֵ�����ò������ظ߶� 
		return m_Images[iIndex].pBytes;  //ֱ�ӷ���ͼƬ����ָ��
	}
}