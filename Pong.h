//
// Created by david on 5/31/15.
//

#ifndef PONG_PONG_H
#define PONG_PONG_H

//#include "wx/sizer.h"
#include "Paddle.h"
#include "Ball.h"
#include "AI.h"


class Pong
{
public:
	int m_humanScore;
	int m_AIScore;
	wxPoint m_middle;
	wxSize m_boardSize;

	Paddle m_paddlePlayer;
	Paddle m_paddleAI;
	Ball m_ball;
	AI m_artifitialInteligence;

	Pong()
	{
		m_humanScore = 0;
		m_AIScore = 0;
		//Bind(HUMAN_POINT_EVENT, &Pong::OnHumainPoint, this, wxID_ANY);
		//Bind(AI_POINT_EVENT, &Pong::OnAIPoint, this, wxID_ANY);
	}
	void OnHumanPlayerMove(int newYPosition);
	void Init(wxSize boardSize);
	void ComputeNextStep();
	void Paint(wxPaintDC& dc);
	void BoardPaint(wxPaintDC& dc);
};


#endif //PONG_PONG_H
