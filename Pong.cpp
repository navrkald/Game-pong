//
// Created by david on 5/31/15.
//

#include "Pong.h"

void Pong::Init(wxSize boardSize)
{
	m_boardSize = boardSize;
	m_middle.x = boardSize.x / 2;
	m_middle.y = boardSize.y / 2;
	wxPoint leftPaddle, rightPaddle;
	leftPaddle.x = 0;
	leftPaddle.y = m_middle.y;
	rightPaddle.x = boardSize.x - Paddle::width;
	rightPaddle.y = m_middle.y;
	int radius = 15;


	m_paddlePlayer.Init(leftPaddle);
	m_paddleAI.Init(rightPaddle);
	m_ball.Init(m_middle, radius, boardSize, m_paddlePlayer, m_paddleAI);
	m_artifitialInteligence.Init(m_ball,m_paddleAI, m_middle);
}

void Pong::OnHumanPlayerMove(int newYPosition)
{
	m_paddlePlayer.m_position.y = newYPosition;
}

void Pong::ComputeNextStep()
{
	m_artifitialInteligence.ComputePaddlePos();
	// Score changed
	if(m_ball.GetScore(m_humanScore, m_AIScore))
	{
		m_ball.SetPosition(m_middle);
	}
	else
	{
		m_ball.SetPosition(m_ball.GetNextPosition());
	}
}



void Pong::Paint(wxPaintDC& dc)
{
	dc.Clear();
	m_paddlePlayer.Paint(dc);
	m_paddleAI.Paint(dc);
	m_ball.Paint(dc);
	BoardPaint(dc);

}

void Pong::BoardPaint(wxPaintDC &dc)
{
	dc.SetTextForeground(*wxWHITE);
	dc.SetFont(wxFont(30, wxFONTFAMILY_SWISS, wxNORMAL, wxBOLD));
	wxString humainScoreStr = wxString::Format(wxT("%d"), m_humanScore);
	dc.DrawText(humainScoreStr, m_middle.x / 2, m_middle.y /6);

	wxString AIScoreStr = wxString::Format(wxT("%d"), m_AIScore);
	dc.DrawText(AIScoreStr, m_middle.x + m_middle.x / 2, m_middle.y /6);

	dc.SetPen(wxPen( wxColor(255,255,255), 1 , wxLONG_DASH));
	dc.DrawLine(wxPoint(m_middle.x,0), wxPoint(m_middle.x, m_boardSize.y));
}
