//
// Created by david on 5/31/15.
//

#include "Paddle.h"
#include "wx/wx.h"

int Paddle::width = 10;
int Paddle::height = 80;

void Paddle::Init(wxPoint& position)
{
	m_position = position;
}

void Paddle::Paint(wxPaintDC & dc)
{
	dc.DrawRectangle(m_position.x, m_position.y - Paddle::height / 2,Paddle::width, Paddle::height);
}
