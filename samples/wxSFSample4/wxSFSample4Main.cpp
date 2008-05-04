/***************************************************************
 * Name:      wxSFSample4Main.cpp
 * Purpose:   Code for Application Frame
 * Author:    Michal Bližňák (michal.bliznak@tiscali.cz)
 * Created:   2007-08-31
 * Copyright: Michal Bližňák ()
 * License:
 **************************************************************/
#include "wx_pch.h"

#include "wxSFSample4Main.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

BEGIN_EVENT_TABLE(wxSFSample1Frame, wxFrame)
    EVT_CLOSE(wxSFSample1Frame::OnClose)
    EVT_MENU(idMenuQuit, wxSFSample1Frame::OnQuit)
    EVT_MENU(idMenuAbout, wxSFSample1Frame::OnAbout)
END_EVENT_TABLE()

wxSFSample1Frame::wxSFSample1Frame(wxFrame *frame, const wxString& title)
    : wxFrame(frame, -1, title)
{
    SetSize(800, 600);

#if wxUSE_MENUS
    // create a menu bar
    wxMenuBar* mbar = new wxMenuBar();
    wxMenu* fileMenu = new wxMenu(_T(""));
    fileMenu->Append(idMenuQuit, _("&Quit\tAlt-F4"), _("Quit the application"));
    mbar->Append(fileMenu, _("&File"));

    wxMenu* helpMenu = new wxMenu(_T(""));
    helpMenu->Append(idMenuAbout, _("&About\tF1"), _("Show info about this application"));
    mbar->Append(helpMenu, _("&Help"));

    SetMenuBar(mbar);
#endif // wxUSE_MENUS

    // set some diagram manager properties if necessary...
    // set accepted shapes (accept only wxSFControlShape)
    m_Manager.AcceptShape(wxT("wxSFControlShape"));

    // create shape canvas and associate it with shape manager
    m_pCanvas = new wxSFShapeCanvas(&m_Manager, this);
    // set some shape canvas properties if necessary...
	m_pCanvas->AddStyle(wxSFShapeCanvas::sfsGRID_SHOW);
    m_pCanvas->AddStyle(wxSFShapeCanvas::sfsGRID_USE);

    // connect event handlers to shape canvas
    m_pCanvas->Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(wxSFSample1Frame::OnLeftClickCanvas), NULL, this);
    m_pCanvas->Connect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(wxSFSample1Frame::OnRightClickCanvas), NULL, this);

#if wxUSE_STATUSBAR
    // create a status bar with some information about the used wxWidgets version
    CreateStatusBar(2);
    SetStatusText(_("Hello Code::Blocks user!"),0);
    SetStatusText(wxbuildinfo(short_f), 1);
#endif // wxUSE_STATUSBAR

    Center();
}


wxSFSample1Frame::~wxSFSample1Frame()
{
}

void wxSFSample1Frame::OnLeftClickCanvas(wxMouseEvent& event)
{
    // HINT: perform your user actions here...

    // ... and then process standard canvas operations
    event.Skip();
}

void wxSFSample1Frame::OnRightClickCanvas(wxMouseEvent& event)
{
    // add new rectangular shape to the diagram ...
    wxSFControlShape* pShape = (wxSFControlShape*)m_Manager.AddShape(CLASSINFO(wxSFControlShape), event.GetPosition());
    // set some shape's properties...
    if(pShape)
    {
        // set accepted child shapes for the new shape
        pShape->ClearAcceptedChilds();

        // Assign managed GUI control to the canvas. Remember the control shape now owns the GUI control and it is
        // deleted by shape control in its destructor. If you want to remove the GUI control from the parent shape
        // just assign a new control or NULL value to it.
        pShape->SetControl(new wxButton(m_pCanvas, wxID_ANY, wxT("Hello World!")));
    }

    // ... and process standard canvas operations
    event.Skip();
}

void wxSFSample1Frame::OnClose(wxCloseEvent& WXUNUSED(event))
{
    Destroy();
}

void wxSFSample1Frame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Destroy();
}

void wxSFSample1Frame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxString msg = wxbuildinfo(long_f);

    msg += wxT("\nWelcome to wxSFShapeFramework Sample 4 (c) Michal Bliznak, 2007\n\n");
    msg += wxT("Sample demostrates posibility to manage GUI controls (widgets) by the wxSFControlShape.\n");
    msg += wxT("wxSF event handlers are connected via 'Connect' function.\n\n");
    msg += wxT("Usage:\n");
    msg += wxT(" - Left mouse click operates with inserted shapes\n");
    msg += wxT(" - Right mouse click inserts a rectangular shape to the canvas\n");
    msg += wxT(" - DEL key removes selected shape\n");

    wxMessageBox(msg, wxT("wxShapeFramework Sample 1"));
}
