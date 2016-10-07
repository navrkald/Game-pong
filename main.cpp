#include "wx/wx.h"
#include "wx/sizer.h"
#include "Ball.h"
#include "Pong.h"
enum
{
  MY_TIMER_ID = 100500,
};

class Board : public wxPanel
{
private:

public:
  wxTimer m_timer;
  Ball ball;
  wxSize windowSize;
  wxPoint paddlePos;
  Pong m_pong;
  Board(wxFrame* parent);
  void OnTimerTimeout(wxTimerEvent& event);
  void mouseMoved(wxMouseEvent& event);
  void StartGame();
  void OnPause(wxCommandEvent &event);
  void OnPlay(wxCommandEvent &event);
  DECLARE_EVENT_TABLE()
};

Board::Board(wxFrame* parent) : wxPanel(parent)
{
  windowSize = parent->GetClientSize();
  m_timer.SetOwner(this,MY_TIMER_ID);
}

class MyApp: public wxApp
{
  bool OnInit();

  wxFrame *frame;
  Board * drawPane;

  wxMenuBar *menubar;
  wxMenu *file;
  wxMenu *game;
public:
  void OnQuit(wxCommandEvent& event);

};

IMPLEMENT_APP(MyApp)

#define PAUSE_ID 10000
#define PLAY_ID  10001

bool MyApp::OnInit()
{
  wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
  frame = new wxFrame((wxFrame *)NULL, -1,  wxT("Hello wxDC"), wxPoint(50,50), wxSize(800,600));
  frame->SetBackgroundColour(wxColour(* wxBLACK));
  drawPane = new Board( (wxFrame*) frame );
  drawPane->SetBackgroundColour(wxColour(* wxBLACK));
  sizer->Add(drawPane, 1, wxEXPAND);

  frame->SetSizer(sizer);
  frame->SetAutoLayout(true);

  menubar = new wxMenuBar;
  file = new wxMenu;
  file->Append(wxID_EXIT, wxT("&Quit"));
  game = new wxMenu;
  game->Append(PAUSE_ID  ,wxT("&Pause"));
  game->Append(PLAY_ID  ,wxT("&Play"));
  menubar->Append(file, wxT("&File"));
  menubar->Append(game, wxT("&Game"));
  frame->SetMenuBar(menubar);
  Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyApp::OnQuit));
  Connect(PAUSE_ID, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Board::OnPause));
  Connect(PLAY_ID, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Board::OnPlay));
  frame->Show();


  drawPane->StartGame();
  return true;
}

void MyApp::OnQuit(wxCommandEvent &event) {
  frame->Close();
}

void Board::OnPause(wxCommandEvent &event)
{
  this->Disconnect(MY_TIMER_ID, wxEVT_TIMER, wxTimerEventHandler(Board::OnTimerTimeout), NULL, this);
  m_timer.Stop();
}

void Board::OnPlay(wxCommandEvent &event)
{
  this->Connect(MY_TIMER_ID, wxEVT_TIMER, wxTimerEventHandler(Board::OnTimerTimeout),NULL, this);
  m_timer.Start(10);
}


void Board::OnTimerTimeout(wxTimerEvent& event)
{

  m_pong.ComputeNextStep();
  wxPaintDC paintDC(this);
  m_pong.Paint(paintDC);

};

void Board::StartGame()
{
	m_pong.Init(windowSize);
  //m_timer = wxTimer(this,TIMER_ID);
  this->Connect(MY_TIMER_ID, wxEVT_TIMER, wxTimerEventHandler(Board::OnTimerTimeout),NULL, this);
  m_timer.Start(10);
}



void Board::mouseMoved(wxMouseEvent& event)
{
	m_pong.OnHumanPlayerMove(event.GetPosition().y);
}

BEGIN_EVENT_TABLE(Board, wxPanel)
    EVT_MOTION(Board::mouseMoved)
//    EVT_TIMER(TIMER_ID, Board::OnTimerTimeout)
END_EVENT_TABLE()


