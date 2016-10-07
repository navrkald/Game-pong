//
// Created by david on 2.6.15.
//

#include "AI.h"

void AI::Init(Ball &ball, Paddle &paddle, wxPoint middle)
{
	m_ball = &ball;
	m_paddle = &paddle;
	m_middle = middle;
}

void AI::ComputePaddlePos()
{
	//m_paddle->m_position.y = m_ball->m_position.y;
  if(m_ball->m_position.x > m_middle.x)
  {
	  if(m_ball->m_position.y > m_paddle->m_position.y)
	  {
		  m_paddle->m_position.y += 2;
	  }
	  else
	  {
		  m_paddle->m_position.y -= 2;
	  }
  }
}
