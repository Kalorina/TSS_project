
// TSS_cviko1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "TSS_cviko1.h"
#include "TSS_cviko1Dlg.h"
#include "afxdialogex.h"
#include <stdio.h>

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


	/*if (pNMLV->iItem != -1 && (pNMLV->uChanged & LVIF_STATE))
	{
		if ((pNMLV->uNewState & LVIS_SELECTED) == LVIS_SELECTED)
		{
			int selectedIndex = pNMLV->iItem;

			if (selectedIndex >= 0 && selectedIndex < m_imageList.size())
			{
				m_currentImage = &m_imageList[selectedIndex];

				SendMessage(WM_DRAW_IMAGE, 0, 0);  
			}
		}
		else if ((pNMLV->uNewState & LVIS_SELECTED) == 0) 
		{
			SendMessage(WM_DRAW_IMAGE, 0, 0);
		}
	}*/

	//this is allfor this function, this means when a selection in ListControl is selected it calles OnDrawImage

	m_staticImage.Invalidate(FALSE);

	*pResult = 0;
}


void CTSScviko1Dlg::DisplayListControl()
{
	m_fileList.DeleteAllItems();

	for (size_t i = 0; i < m_imageList.size(); ++i)
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

	CDialogEx::OnSize(nType, cx, cy);

	int nDiffY = cy - m_rect.Height();
	int nDiffX = cx - m_rect.Width();

	if (::IsWindow(m_fileList) && ::IsWindow(m_staticImage) && ::IsWindow(m_staticHistogram)) {

		m_fileList.SetWindowPos(nullptr, 0, 0, m_rectFileList.Width(), m_rectFileList.Height() + nDiffY, SWP_NOMOVE);

		m_staticImage.SetWindowPos(nullptr, 0, 0, m_rectStaticImage.Width() + nDiffX, m_rectStaticImage.Height() + nDiffY, SWP_NOMOVE);

		int histY = cy - m_rectStaticHistogram.Height() - m_rectFileList.Height() - 18;

		m_staticHistogram.SetWindowPos(nullptr, m_rectStaticHistogram.left - 9, histY,  m_rectStaticHistogram.Width(), m_rectStaticHistogram.Height(), SWP_NOZORDER);
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

//finish Histogram display, nova zlozka ako file, kde budu RGB items a podla toho sa vykresli RGB zlozky
LRESULT CTSScviko1Dlg::OnDrawHist(WPARAM wParam, LPARAM lParam)
{
	LPDRAWITEMSTRUCT st = (LPDRAWITEMSTRUCT)wParam;

	//Vyssie urovnovy
	auto gr = Gdiplus::Graphics::FromHDC(st->hDC);

	//gr->DrawCurve();

	return S_OK;
}

void CTSScviko1Dlg::OnStnClickedStaticImage()
{
	// TODO: Add your control notification handler code here
}
