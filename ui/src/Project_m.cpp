#include "stdafx.h"
#include "hostQtUi.h"
#include "Widget.h"


extern "C" __declspec(dllexport) void showDialog(HWND parent)
{
  QWinWidget win(parent);
  win.showCentered();

  QMessageBox::about(&win, "adaptive_commands.dll", "Hello, Qt in nanoCAD!");
}
extern "C" __declspec(dllexport) void showSimpleDialog()
{
    showDialog("adaptive_commands.dll", "Hello, Qt in nanoCAD!");
}

void helloQtModalDlgCmd()
{
  ncutPrintf(L"\nHello, hostQt.dll!\n");
  showDialog(ndsw_ncadMainWnd());
}

hostQtPaletteSetWrap* m_pPalSet = nullptr;
hostQtPaletteWidget* m_pPaletteWidget = nullptr;


//class helloQtPalette : public hostQtPalette
//{
//    DECLARE_DYNAMIC(helloQtPalette)
//
//public:
//    helloQtPalette()
//    {};
//
//    afx_msg void    OnSize(UINT nType, int cx, int cy)
//    {
//        if (m_pWinWidget)
//        {
//            HWND wnd = (HWND)m_pWinWidget->windowHandle()->winId();
//            ::SetWindowPos(wnd, nullptr, 0, 0, cx, cy, SWP_NOZORDER);
//        }
//    }
//
//    DECLARE_MESSAGE_MAP();
//};


void helloQtPaletteCmd()
{
  if (!m_pPalSet)
  {
    //create palleteSet
    m_pPalSet = new hostQtPaletteSetWrap();
    m_pPalSet->Create(L"Commands", WS_CHILD | WS_DLGFRAME | WS_VISIBLE, QRect(30, 50, 270, 300),
                      PalleteSetStyle::Snap | PalleteSetStyle::PropertiesMenu | PalleteSetStyle::AutoRollup | PalleteSetStyle::CloseButton);
    m_pPalSet->EnableDocking(PalleteSetAlign::Any);
    m_pPalSet->RestoreControlBar();
    //create pallete
    m_pPaletteWidget = new hostQtPaletteWidget();
    m_pPaletteWidget->Create(WS_CHILD | WS_VISIBLE, L"Commands", m_pPalSet, 0);
    //create user widget and set it on pallete
    Widget* pWidgetsClass = new Widget(m_pPaletteWidget);

    QVBoxLayout* vbox = new QVBoxLayout(m_pPaletteWidget);
    vbox->setSpacing(0);
    vbox->setMargin(0);
    vbox->addWidget(pWidgetsClass);
    vbox->addStretch();


    //pWidgetsClass->connect(pWidgetsClass, &Widget::signal1,
    //                       []
    //                       {
    //                           showSimpleDialog();
    //                       });

    m_pPaletteWidget->setLayout(vbox);
    m_pPaletteWidget->showPallete(m_pPalSet);
  }
  else
  {
    m_pPalSet->Show(!m_pPalSet->IsWindowVisible());
  }
}

//void helloQtPaletteCmd()
//{
//    if (!m_pPalSet)
//    {
//        CAcModuleResourceOverride ThisRes;
//        m_pPalSet = new hostUiPaletteSet();
//        m_pPalSet->Create(L"PolyQtTable", WS_CHILD | WS_DLGFRAME | WS_VISIBLE, CRect(30, 50, 270, 300),
//            CWnd::FromHandle(adsw_acadMainWnd()), PSS_SNAP | PSS_PROPERTIES_MENU | PSS_AUTO_ROLLUP | PSS_CLOSE_BUTTON);
//        m_pPalSet->EnableDocking(CBRS_ALIGN_ANY);
//        m_pPalSet->RestoreControlBar();
//
//        helloQtPalette* pPal = new helloQtPalette();
//        pPal->Create(WS_CHILD | WS_VISIBLE, L"PolyQtTable", m_pPalSet, 0);
//        m_pPalSet->AddPalette(pPal);
//
//        QWidget* pPaletteWidget1 = pPal->paletteWidget();
//
//        /*Widget*/Project_mChild* pWidgetsClass = new Project_mChild(pPaletteWidget1);
//
//        QVBoxLayout* vbox = new QVBoxLayout(pPaletteWidget1);
//        vbox->setSpacing(0);
//        vbox->setMargin(0);
//        vbox->addWidget(pWidgetsClass);
//        vbox->addStretch();
//
//        //WId winId = le3->winId(); // Make Qt windows real HWND windows
//
//        pPaletteWidget1->setLayout(vbox);
//        pPaletteWidget1->show();
//
//        CRect cr;
//        m_pPalSet->GetClientRect(&cr);
//        pPal->OnSize(0, cr.Width(), cr.Height()); // Force to resize palette widget, needed when system scale !=100%
//    }
//    else
//    {
//        m_pPalSet->Show(!m_pPalSet->IsWindowVisible());
//    }
//}



void initApp()
{
  //ncedRegCmds->addCommand(L"PROJECT_M_GROUP",
  //                        L"_PROJECT_MMODALDLG",
  //                        L"PROJECT_MMODALDLG",
  //                        NCRX_CMD_TRANSPARENT,
  //                        helloQtModalDlgCmd);

  ncedRegCmds->addCommand(L"ADAPTCMD_GROUP",
                          L"_ADAPTCMD",
                          L"ADAPTCMD",
                          NCRX_CMD_TRANSPARENT,
                          helloQtPaletteCmd);
}

void uninitApp()
{
  ncedRegCmds->removeGroup(L"ADAPTCMD_GROUP");
  if (m_pPaletteWidget)
  {
      m_pPalSet->RemovePalette(m_pPaletteWidget);
      delete m_pPaletteWidget;
      m_pPaletteWidget = nullptr;
  }
  if (m_pPalSet)
  {
    m_pPalSet->DestroyWindow();
    m_pPalSet = nullptr;
  }
}

extern "C" __declspec(dllexport) NcRx::AppRetCode
ncrxEntryPoint(NcRx::AppMsgCode msg, void* appId) 
{
  switch (msg) 
  {
  case NcRx::kInitAppMsg:
    ncrxDynamicLinker->unlockApplication(appId);
    ncrxDynamicLinker->registerAppMDIAware(appId);
    initApp();
    break;

  case NcRx::kUnloadAppMsg:
    uninitApp();
    break;
  }

  return NcRx::kRetOK;
}