//
// Created by david on 5/31/15.
//

#include "Ball.h"
#include <stdlib.h>     // srand, rand
#include <time.h>       // time

double Ball::maxBounceAngle = 1.30900; // 75 degrees
double Ball::ballSpead = 4;

void Ball::Init(const wxRealPoint &position, int radius, const wxSize &boardSize, Paddle& leftPaddle, Paddle& rightPaddle)
{
	this->m_position = position;
	this->m_unitVector =generateRandomUnitVector();
	this->m_radius = radius;
	this->m_boardSize = boardSize;
	this->m_leftPaddle = &leftPaddle;
	this->m_rightPaddle = &rightPaddle;
	this->m_humainScore = 0;
	this->m_AIScore = 0;
	m_scoreChanged = false;
}



void Ball::SetPosition(wxRealPoint position)
{
	m_position = position;
}

bool Ball::WillRebound(int yPaddlePosition) {
	return (m_position.y < (yPaddlePosition + (Paddle::height /2)) ) && (m_position.y > (yPaddlePosition - (Paddle::height / 2)) );
}

wxRealPoint Ball::GetNextPosition()
{
	bool up, down, left, right = false;
	if(WillRebound(up,down, left, right))
	{
		if(left || right)
		{
			int yPaddlePos = (left) ? m_leftPaddle->m_position.y : m_rightPaddle->m_position.y;
			if(WillRebound(yPaddlePos))
			{
				//m_unitVector = ComputeReboundUnitVector(yPaddlePos);
				m_unitVector.x *= -1;
			}
			else
			{
				m_scoreChanged = true;
				m_unitVector = generateRandomUnitVector();
				(left) ? m_AIScore ++ : m_humainScore ++;
			}
		}
		if(up || down)
			m_unitVector.y *= -1;
	}
	return m_position + m_unitVector;
}

bool Ball::WillRebound(bool& up, bool& down, bool& left ,bool& right)
{
	up = m_position.y - m_radius <= 0;
	down = m_position.y + m_radius >= m_boardSize.y;
	left = m_position.x - m_radius <= 0;
	right = m_position.x + m_radius >= m_boardSize.x;
	return up || down || left || right;
}

wxRealPoint Ball::generateRandomUnitVector()
{
	srand (time(NULL));
	double pi = 3.14159265359;
	double _15deg = pi /12.0;
	double _90deg = pi /2.0;
	double _75deg = _90deg - _15deg;
	double _105deg = _90deg + _15deg;
	double _255deg = 3.0*_90deg - _15deg;
	double _285deg = 3.0*_90deg + _15deg;
	double angle = ( ((double)(rand() % 1000 )) / 1000.0) * 2 * pi;

	//get rid of extreme angles
  if(angle>_75deg && angle < _105deg)
	{
		angle = _75deg;
	}
	else if(angle > _255deg && angle < _285deg)
	{
		angle = _255deg;
	}

	wxRealPoint unitVector;
	unitVector.y	= sin(angle) * ballSpead;
	unitVector.x	= cos(angle) * ballSpead;
	return unitVector;
}

void Ball::Paint(wxPaintDC &dc)
{
	dc.DrawCircle(m_position,m_radius);
}

bool Ball::GetScore(int &humainScore, int &AIScore)
{
	bool tmpScoreChanged = m_scoreChanged;
	m_scoreChanged = false;
	humainScore = this->m_humainScore;
	AIScore = this->m_AIScore;
	return tmpScoreChanged;
}


wxRealPoint Ball::ComputeReboundUnitVector(double paddleY)
{
	double relativeIntersectY = paddleY + (Paddle::height / 2) - m_position.y;
	double normalizedRelativeIntersectionY = relativeIntersectY / (Paddle::height / 2);
	double bounceAngle = normalizedRelativeIntersectionY * maxBounceAngle;
	wxRealPoint newUnitVector;
	newUnitVector.x = cos(bounceAngle) * ballSpead;
	newUnitVector.y = sin(bounceAngle) * ballSpead;
	return newUnitVector;
}
