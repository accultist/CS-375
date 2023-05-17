// Module:		Brick.cpp
// Author:		Adham Said
// Date:		May 11, 2023
// Purpose:		Implementation of Ball class
//				Creates ball that will interact with objects
//				Ball also collides with sides of window
//

#include "main.h"

Ball::Ball(HWND hWnd)
{
	// get client window dimensions
	RECT rClient;
	GetClientRect(hWnd, &rClient);					// window

	// set start location
	rDim.left = rClient.right / 2;
	rDim.top = rClient.bottom / 2;

	// set ball size
	int dSize = 20;							// balls are round
	rDim.right = rDim.left + dSize;
	rDim.bottom = rDim.top + dSize;

	// set initial speed and direction
	do
	{
		rSpeed.x = 5;			// left or right
	} while (rSpeed.x == 0);						// but not vertical
	do
	{
		rSpeed.y = 5;			// up or down
	} while (rSpeed.y == 0);						// but not horizontal

	// set rgb color to pinkish tone
	//r = 255;						// red
	r = 150;						// red
	g = 160;						// green
	b = 160;						// blue
}

/* function responsible for handling drawing ball */
void Ball::Draw(HDC hdc)
{
	// create brushes
	HBRUSH brush, oldBrush;
	brush = CreateSolidBrush(RGB(r, g, b));
	oldBrush = (HBRUSH)SelectObject(hdc, brush);

	// draw sphere
	Ellipse(hdc, rDim.left, rDim.top, rDim.right, rDim.bottom);

	// release brushes
	SelectObject(hdc, oldBrush);
	DeleteObject(brush);
}

/* function responsible for handling ball movement */
void Ball::Move(HWND hWnd)
{
	// get client window dimensions
	RECT rClient;
	GetClientRect(hWnd, &rClient);					// window

	// update stored coordinates of ball
	dBallLeft = rDim.left;
	dBallRight = rDim.right;
	dBallTop = rDim.top;
	dBallBottom = rDim.bottom;

	

	// check for collision
	// if it bounces of the sides, that's okay
	// reverse direction if it goes anywhere but the bottom
	if (rDim.left <= 0)								// did ball hit left wall
		rSpeed.x = abs(rSpeed.x);
	if (rDim.right >= rClient.right)				// did ball hit right wall
		rSpeed.x = abs(rSpeed.x) * -1.0;
	if (rDim.top <= 0)								// did ball hit top
		rSpeed.y = abs(rSpeed.y);

	
	// game over if ball hits bottom
	if (rDim.bottom >= rClient.bottom) 				// did ball hit bottom
		rSpeed.y = abs(rSpeed.y) * -1.0;
	
	// move according to speed
	rDim.top += rSpeed.y;
	rDim.left += rSpeed.x;
	rDim.bottom += rSpeed.y;
	rDim.right += rSpeed.x;
}

/* returns left-most float value of */
double Ball::GetBallLeft()
{
	return dBallLeft;
}


/* function reverses the direction of ball
	simulates "bouncing" off brick object */
void Ball::Direction(HWND hWnd)
{
	// reverse direction along y-axis
	rSpeed.y = abs(rSpeed.y);
}

/* function reverses the direction of ball
	simulates "bouncing" off brick object */
void Ball::SetColorSpeed(HWND hWnd)
{
	// set color
	r = (r + 1);
	g = (g - 1);
	b = (b - 1);
}

