// Module:		Ball.h
// Author:		Adham Said
// Date:		May 11, 2023
// Purpose:		Header file for Ball.cpp
//				GDI graphic tool
//

#pragma once
class Ball
{
public:
	Ball(HWND);							// constructor

	void Draw(HDC);						// answer WM_PAINT
	void Move(HWND);					// update location
	void Direction(HWND);				// set direction to opposite along y-axis
	void SetColorSpeed(HWND);			// set color and increase speed

	// coordinates of ball
	double dBallLeft = 0.0;				// ball left coordinate
	double dBallRight = 0.0;			// ball right coordinate
	double dBallTop = 0.0;				// ball top coordinate
	double dBallBottom = 0.0;			// ball bottom coordinate

	double GetBallLeft();
	


private:
	int r, g, b;						// color
	RECT rDim;							// location and size in double
	POINT rSpeed;						// speed as a double
};

