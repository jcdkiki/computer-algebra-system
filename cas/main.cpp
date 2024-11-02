#include <wx/gdicmn.h>
#include <wx/sizer.h>
#include <wx/stringimpl.h>
#include <wx/wx.h>
 
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};
 
class MyFrame : public wxFrame
{
public:
    MyFrame();
 
private:
    void OnExit(wxCommandEvent& event);
    void OnHelp(wxCommandEvent& event);
};
 
enum
{
    ID_Natural
};
 
wxIMPLEMENT_APP(MyApp);
 
bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}
 
MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "Hello World", wxDefaultPosition, wxSize(300, 400), wxCAPTION)
{
    wxToolBar *toolbar = CreateToolBar();
    toolbar->AddTool(wxID_HELP, "Help", wxBitmap("data/help.png"));
    toolbar->AddTool(wxID_HELP, "Natural", wxBitmap("data/plus32.png"));
    toolbar->AddTool(wxID_HELP, "Integer", wxBitmap("data/plus-minus32.png"));
    toolbar->AddTool(wxID_HELP, "Rational", wxBitmap("data/percentage32.png"));
    toolbar->AddTool(wxID_HELP, "Polynomial", wxBitmap("data/x32.png"));


    wxTextCtrl *ctrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    ctrl->SetSize(300, 32);

    new wxButton(this, wxID_ANY, "1");
    new wxButton(this, wxID_ANY, "2");

    CreateStatusBar();
    SetStatusText("Welcome to Computer Algebra System");
    new wxStaticBoxSizer(wxVERTICAL, this);
    
    Bind(wxEVT_MENU, &MyFrame::OnHelp, this, wxID_HELP);
    //Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
    //Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
}
 
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
 
void MyFrame::OnHelp(wxCommandEvent& event)
{
    wxMessageBox("Help message will be placed here...",
                 "Help", wxOK | wxICON_INFORMATION);
}
