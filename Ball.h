//
// Created by david on 5/31/15.
//

#ifndef PONG_CBALL_H
#define PONG_CBALL_H

#include "wx/sizer.h"
#include "wx/wx.h"
#include "Paddle.h"

class Ball;



class Ball : public wxCommandEvent
{
public:
	static double maxBounceAngle;
	static double ballSpead;
	int m_humainScore;
	int m_AIScore;
	bool m_scoreChanged;
	wxRealPoint m_position;
	wxRealPoint m_unitVector;
	int m_radius;
	wxSize m_boardSize;
	Paddle* m_leftPaddle, * m_rightPaddle;
	wxRealPoint generateRandomUnitVector();
	void Init(const wxRealPoint &position, int radius, const wxSize &boardSize, Paddle& leftPaddle, Paddle& rightPaddle);


public:
	bool WillRebound(bool& up, bool& down, bool& left ,bool& right);
	wxRealPoint GetNextPosition();
	void SetPosition (wxRealPoint position);
	bool GetScore(int& humainScore, int& AIScore);
	void Paint(wxPaintDC & dc);
	bool WillRebound(int yPaddlePosition);
	wxRealPoint ComputeReboundUnitVector(double paddleY);
};


#endif //PONG_CBALL_H
