//
// Created by david on 5/31/15.
//

#ifndef PONG_PADDLE_H
#define PONG_PADDLE_H


#include <wx/wx.h>


class Paddle
{
public:
	wxRealPoint m_position;
	static int width;
	static int height;

public:
	void Init(wxPoint& position);
	void Paint(wxPaintDC& dc);
};


#endif //PONG_PADDLE_H
