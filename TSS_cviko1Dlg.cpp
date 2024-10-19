
// TSS_cviko1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "TSS_cviko1.h"
#include "TSS_cviko1Dlg.h"
#include "afxdialogex.h"
#include <stdio.h>
#include <gdiplus.h> 
#include <gdipluspixelformats.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


void CStaticImage::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStuct)
{
	GetParent()->SendMessage(WM_DRAW_IMAGE, (WPARAM)lpDrawItemStuct);
};

void CStaticHist::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStuct)
{
	GetParent()->SendMessage(WM_DRAW_HISTOGRAM, (WPARAM)lpDrawItemStuct);
};


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTSScviko1Dlg dialog


CTSScviko1Dlg::CTSScviko1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TSS_CVIKO1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME); 
}

void CTSScviko1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FILE_LIST, m_fileList);
	DDX_Control(pDX, IDC_STATIC_HISTOGRAM, m_staticHistogram);
	DDX_Control(pDX, IDC_STATIC_IMAGE, m_staticImage);
}

BEGIN_MESSAGE_MAP(CTSScviko1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_FILE_LIST, &CTSScviko1Dlg::OnLvnItemchangedFileList)
	ON_COMMAND(ID_FILE_OPEN32771, &CTSScviko1Dlg::OnFileOpen32771)
	ON_COMMAND(ID_FILE_CLOSE32772, &CTSScviko1Dlg::OnFileClose32772)
	//Messages
	ON_MESSAGE(WM_DRAW_IMAGE, OnDrawImage)
	ON_MESSAGE(WM_DRAW_HISTOGRAM, OnDrawHist)

	ON_WM_SIZE()
	ON_WM_DRAWITEM()

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_FILE_LIST, &CTSScviko1Dlg::OnLvnItemchangedFileList) // Linking the LVN_ITEMCHANGED event
	//ON_BN_CLICKED(IDC_BUTTON_LOAD_IMAGE, &CTSScviko1Dlg::OnBnClickedLoadImage) // Linking a button click event

	ON_STN_CLICKED(IDC_STATIC_IMAGE, &CTSScviko1Dlg::OnStnClickedStaticImage)
	ON_COMMAND(ID_HISTOGRAM_RED, &CTSScviko1Dlg::OnHistogramRed)
	ON_COMMAND(ID_HISTOGRAM_GREEN, &CTSScviko1Dlg::OnHistogramGreen)
	ON_COMMAND(ID_HISTOGRAM_BLUE, &CTSScviko1Dlg::OnHistogramBlue)
	ON_UPDATE_COMMAND_UI(ID_HISTOGRAM_RED, &CTSScviko1Dlg::OnUpdateHistogramRed)
END_MESSAGE_MAP()



// CTSScviko1Dlg message handlers

BOOL CTSScviko1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	m_menu = GetMenu();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	GetClientRect(&m_rect);
	m_fileList.GetWindowRect(&m_rectFileList);
	m_staticImage.GetWindowRect(&m_rectStaticImage);
	m_staticHistogram.GetWindowRect(&m_rectStaticHistogram);
	GetWindowRect(&m_rect);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTSScviko1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTSScviko1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTSScviko1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// handler function
void CTSScviko1Dlg::OnLvnItemchangedFileList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	//when a selection in ListControl is selected it calles OnDrawImage

	m_staticImage.Invalidate(FALSE); //updates image 
	m_staticHistogram.Invalidate(FALSE); //updates histogram channels

	*pResult = 0;
}


void CTSScviko1Dlg::DisplayListControl()
{
	m_fileList.DeleteAllItems();

	for (int i = 0; i < m_imageList.size(); ++i)
	{
		m_fileList.InsertItem(i, m_imageList[i].filename);
	}

	if (m_imageList.size() > 0)
	{
		m_fileList.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);
		
		//m_staticImage.Invalidate(FALSE);
		Invalidate(FALSE);
	}
}


void CTSScviko1Dlg::CalculateHistogram(Img& img)
{
	if (!img.bitmap) return;

	Gdiplus::Bitmap* bitmap = static_cast<Gdiplus::Bitmap*>(img.bitmap);

	img.redChannel.resize(256, 0);
	img.greenChannel.resize(256, 0);
	img.blueChannel.resize(256, 0);

	for (UINT y = 0; y < bitmap->GetHeight(); ++y)
	{
		for (UINT x = 0; x < bitmap->GetWidth(); ++x)
		{
			Gdiplus::Color color;
			bitmap->GetPixel(x, y, &color);

			int r = color.GetR();
			int g = color.GetG();
			int b = color.GetB();

			img.redChannel[r]++;
			img.greenChannel[g]++;
			img.blueChannel[b]++;
		}
	}

	/*
	//Gdiplus::PixelFormat format = bitmap->GetPixelFormat();

	Gdiplus::Rect rect(0, 0, bitmap->GetWidth(), bitmap->GetHeight());
	Gdiplus::BitmapData bitmapData;

	// Set the bitmap data to read the pixels
	if (bitmap->LockBits(&rect, Gdiplus::ImageLockModeRead, bitmap->GetPixelFormat(), &bitmapData) == Gdiplus::Ok)
	{
		// Pointer to the pixel data
		UINT8* pixels = static_cast<UINT8*>(bitmapData.Scan0);

		// Calculate the histogram
		for (UINT y = 0; y < bitmap->GetHeight(); ++y)
		{
			for (UINT x = 0; x < bitmap->GetWidth(); ++x)
			{
				UINT index = (y * bitmapData.Stride) + (x * 4); // 4 bytes per pixel (ARGB)

				int r = pixels[index + 2]; 
				int g = pixels[index + 1]; 
				int b = pixels[index + 0]; 

				img.redChannel[r]++;
				img.greenChannel[g]++;
				img.blueChannel[b]++;
			}
		}

		// Unlock the bitmap after processing
		bitmap->UnlockBits(&bitmapData);
	}*/
}


void CTSScviko1Dlg::OnFileOpen32771()
{
	// TODO: Add your command handler code here
	// into struct of image add GDI+ Image* 

	CString	filename;
	CString filepath;

	TCHAR fileTypeFilters[] = _T("Files (*.bmp;*.png;*.jpg)|*.bmp;*.png;*.jpg||");

	CFileDialog dlg(TRUE, _T(""), _T(""), OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT, fileTypeFilters);

	if (dlg.DoModal() == IDOK)
	{
		POSITION pos = dlg.GetStartPosition();

		while (pos != NULL)
		{
			CString filepath = dlg.GetNextPathName(pos);
			// Get just the file name from the full path
			CString filename = filepath.Mid(filepath.ReverseFind('\\') + 1);

			bool imageExists = false; // Flag to check if the image already exists

			for (const auto& img : m_imageList)
			{
				if (img.filepath == filepath && img.filename == filename)
				{
					imageExists = true; 
					CString message;
					message.Format(_T("The file \"%s\" is already opened."), filename);
					AfxMessageBox(message);
					break; 
				}
			}

			if (!imageExists)
			{
				Img image; 
				image.filename = filename;
				image.filepath = filepath; 
				image.bitmap = Gdiplus::Image::FromFile(filepath);
				CalculateHistogram(image);
				m_imageList.push_back(image);

				DisplayListControl();
			}

		}
	}
	else
		return;
}


void CTSScviko1Dlg::OnFileClose32772()
{
	POSITION pos = m_fileList.GetFirstSelectedItemPosition();

	// Check if any item is selected
	if (pos != NULL)
	{
		int selectedIndex = m_fileList.GetNextSelectedItem(pos);

		CString selectedFile = m_fileList.GetItemText(selectedIndex, 0);

		CString message;
		message.Format(_T("Are you sure you want to close the file: %s?"), selectedFile);
		int response = AfxMessageBox(message, MB_YESNO | MB_ICONQUESTION);

		// If the user clicked 'Yes', proceed to close the file
		if (response == IDYES)
		{
			CString filenameToDelete = m_fileList.GetItemText(selectedIndex, 0);

			bool imageFound = false;

			for (size_t i = 0; i < m_imageList.size(); ++i)
			{
				if (m_imageList[i].filename.CompareNoCase(filenameToDelete) == 0)
				{
					m_imageList.erase(m_imageList.begin() + i);
					break; // Exit the loop once the item is found and deleted
				}
			}

			DisplayListControl();
			Invalidate(TRUE); 
		}
	}
	else
	{
		// No item is selected
		AfxMessageBox(_T("No image selected to close."));
	}
}


void CTSScviko1Dlg::OnSize(UINT nType, int cx, int cy)
{
	/*CDialogEx::OnSize(nType, cx, cy);

	int nDiffY = cy - m_rect.Height();
	int nDiffX = cx - m_rect.Width();

	if (::IsWindow(m_fileList) && ::IsWindow(m_staticImage) && ::IsWindow(m_staticHistogram)) {

		m_fileList.SetWindowPos(nullptr, 0, 0, m_rectFileList.Width(), m_rectFileList.Height() + nDiffY, SWP_NOMOVE);

		m_staticImage.SetWindowPos(nullptr, 0, 0, m_rectStaticImage.Width() + nDiffX, m_rectStaticImage.Height() + nDiffY, SWP_NOMOVE);

		int histDiff = m_rectFileList.Height() - m_rectStaticHistogram.Height();
		int histRight = cy - m_rectStaticHistogram.Height() - m_rectFileList.Height();

		m_staticHistogram.SetWindowPos(nullptr, m_rectFileList.Width(), m_rectFileList.Height() + nDiffY, m_rectFileList.Width() + nDiffX, m_rectFileList.Height() + nDiffY + m_rectStaticHistogram.Height(), SWP_NOMOVE);
	}

	Invalidate(TRUE);
	*/

	CDialogEx::OnSize(nType, cx, cy);

	int nDiffY = cy - m_rect.Height();
	int nDiffX = cx - m_rect.Width();

	if (::IsWindow(m_fileList) && ::IsWindow(m_staticImage) && ::IsWindow(m_staticHistogram))
	{
		m_fileList.SetWindowPos(nullptr, 0, 0, m_rectFileList.Width(), m_rectFileList.Height() + nDiffY, SWP_NOMOVE);
		m_staticImage.SetWindowPos(nullptr, 0, 0, m_rectStaticImage.Width() + nDiffX, m_rectStaticImage.Height() + nDiffY, SWP_NOMOVE);
		
		m_staticHistogram.SetWindowPos(nullptr, m_rectStaticHistogram.left, m_rectStaticHistogram.top + nDiffY, m_rectStaticHistogram.Width(), m_rectStaticHistogram.Height(), SWP_NOSIZE);
	}

	Invalidate(TRUE);

}


LRESULT CTSScviko1Dlg::OnDrawImage(WPARAM wParam, LPARAM lParam)
{
	LPDRAWITEMSTRUCT st = (LPDRAWITEMSTRUCT)wParam;
	Gdiplus::Graphics gr(st->hDC);

	if (m_imageList.empty())
		return -1;

	int selectedIndex = m_fileList.GetNextItem(-1, LVNI_SELECTED);

	if (selectedIndex == -1 || selectedIndex >= m_imageList.size())
		return S_OK;

	Gdiplus::Image* pImage = m_imageList[selectedIndex].bitmap;

	if (pImage && pImage->GetLastStatus() == Gdiplus::Ok)
	{
		CRect rect;
		m_staticImage.GetClientRect(&rect);

		float imageAspectRatio = static_cast<float>(pImage->GetWidth()) / static_cast<float>(pImage->GetHeight());
		float controlAspectRatio = static_cast<float>(rect.Width()) / static_cast<float>(rect.Height());

		float scaleFactor;
		if (imageAspectRatio > controlAspectRatio)
		{
			scaleFactor = static_cast<float>(rect.Width()) / pImage->GetWidth();
		}
		else
		{
			scaleFactor = static_cast<float>(rect.Height()) / pImage->GetHeight();
		}

		int scaledWidth = static_cast<int>(pImage->GetWidth() * scaleFactor);
		int scaledHeight = static_cast<int>(pImage->GetHeight() * scaleFactor);

		int xPos = (rect.Width() - scaledWidth) / 2;   // Center horizontally
		int yPos = (rect.Height() - scaledHeight) / 2; // Center vertically

		gr.Clear(Gdiplus::Color::White);

		gr.DrawImage(pImage, xPos, yPos, scaledWidth, scaledHeight);
	}

	return S_OK;
}


LRESULT CTSScviko1Dlg::OnDrawHist(WPARAM wParam, LPARAM lParam)
{
	LPDRAWITEMSTRUCT st = (LPDRAWITEMSTRUCT)wParam;

	auto gr = Gdiplus::Graphics::FromHDC(st->hDC); 

	if (m_imageList.empty())
		return -1;

	int selectedIndex = m_fileList.GetNextItem(-1, LVNI_SELECTED);

	if (selectedIndex == -1 || selectedIndex >= m_imageList.size())
		return S_OK;

	Img& currentImg = m_imageList[selectedIndex];

	Gdiplus::Pen redPen(Gdiplus::Color(255, 255, 0, 0), 2);   // Red pen
	Gdiplus::Pen greenPen(Gdiplus::Color(255, 0, 255, 0), 2); // Green pen
	Gdiplus::Pen bluePen(Gdiplus::Color(255, 0, 0, 255), 2);  // Blue pen

	
	int maxHeight = 0;
	gr->Clear(Gdiplus::Color(255, 255, 255));
	
	// Set drawing dimensions
	int width = st->rcItem.right - st->rcItem.left;
	int height = st->rcItem.bottom - st->rcItem.top;
	
	// the maximum value for scaling
	if (m_RedChecked)
	{	
		for (int i = 0; i < currentImg.redChannel.size(); i++) {
			if (currentImg.redChannel[i] > maxHeight) {
				maxHeight = currentImg.redChannel[i];
			}
		}
	}
	if (m_GreenChecked) 
	{
		for (int i = 0; i < currentImg.greenChannel.size(); i++) {
			if (currentImg.greenChannel[i] > maxHeight) {
				maxHeight = currentImg.greenChannel[i];
			}
		}
	}
	if (m_BlueChecked) 
	{
		for (int i = 0; i < currentImg.blueChannel.size(); i++) {
			if (currentImg.blueChannel[i] > maxHeight) {
				maxHeight = currentImg.blueChannel[i];
			}
		}
	}

	// (Re)Draw histograms
	if (m_RedChecked) {
		Gdiplus::PointF* redPoints = new Gdiplus::PointF[currentImg.redChannel.size()];
		for (int i = 0; i < currentImg.redChannel.size(); i++) {
			float barHeight = static_cast<float>(currentImg.redChannel[i]) / maxHeight * height;
			redPoints[i] = Gdiplus::PointF(static_cast<float>(i), height - barHeight); // Invert Y-axis
		}
		gr->DrawCurve(&redPen, redPoints, currentImg.redChannel.size());
		delete[] redPoints; 
	}

	if (m_GreenChecked) {
		Gdiplus::PointF* greenPoints = new Gdiplus::PointF[currentImg.greenChannel.size()];
		for (int i = 0; i < currentImg.greenChannel.size(); i++) {
			float barHeight = static_cast<float>(currentImg.greenChannel[i]) / maxHeight * height;
			greenPoints[i] = Gdiplus::PointF(static_cast<float>(i), height - barHeight); // Invert Y-axis
		}
		gr->DrawCurve(&greenPen, greenPoints, currentImg.greenChannel.size());
		delete[] greenPoints; 
	}

	if (m_BlueChecked) {
		Gdiplus::PointF* bluePoints = new Gdiplus::PointF[currentImg.blueChannel.size()];
		for (int i = 0; i < currentImg.blueChannel.size(); i++) {
			float barHeight = static_cast<float>(currentImg.blueChannel[i]) / maxHeight * height;
			bluePoints[i] = Gdiplus::PointF(static_cast<float>(i), height - barHeight); // Invert Y-axis
		}
		gr->DrawCurve(&bluePen, bluePoints, currentImg.blueChannel.size());
		delete[] bluePoints; 
	}

	return S_OK;
}

void CTSScviko1Dlg::OnStnClickedStaticImage()
{
	// TODO: Add your control notification handler code here
}


void CTSScviko1Dlg::OnHistogramRed()
{
	m_RedChecked = !m_RedChecked;
	if (m_RedChecked) 
	{
		m_menu->CheckMenuItem(ID_HISTOGRAM_RED, MF_CHECKED | MF_BYCOMMAND);
	}
	else 
	{
		m_menu->CheckMenuItem(ID_HISTOGRAM_RED, MF_UNCHECKED | MF_BYCOMMAND);
	}
	m_staticHistogram.Invalidate(FALSE);
}

void CTSScviko1Dlg::OnHistogramGreen()
{
	m_GreenChecked = !m_GreenChecked; 
	if (m_GreenChecked) 
	{
		m_menu->CheckMenuItem(ID_HISTOGRAM_GREEN, MF_CHECKED | MF_BYCOMMAND);
	}
	else 
	{
		m_menu->CheckMenuItem(ID_HISTOGRAM_GREEN, MF_UNCHECKED | MF_BYCOMMAND);
	}
	m_staticHistogram.Invalidate(FALSE);
}

void CTSScviko1Dlg::OnHistogramBlue()
{
	m_BlueChecked = !m_BlueChecked;
	if (m_BlueChecked) 
	{
		m_menu->CheckMenuItem(ID_HISTOGRAM_BLUE, MF_CHECKED | MF_BYCOMMAND);
	}
	else 
	{
		m_menu->CheckMenuItem(ID_HISTOGRAM_BLUE, MF_UNCHECKED | MF_BYCOMMAND);
	}
	m_staticHistogram.Invalidate(FALSE);
}


void CTSScviko1Dlg::OnUpdateHistogramRed(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	//pCmdUI->SetCheck(m_RedChecked);
}
