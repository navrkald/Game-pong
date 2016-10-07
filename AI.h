//
// Created by david on 2.6.15.
//

#ifndef PONG_AI_H
#define PONG_AI_H

#include "Ball.h"
#include "Paddle.h"

class AI
{
public:
	Ball* m_ball;
	Paddle* m_paddle;
	wxPoint m_middle;
	void Init(Ball& ball, Paddle& paddle, wxPoint m_middle);
	void ComputePaddlePos();
};


#endif //PONG_AI_H
