// Module:		PlayerPaddle.h
// Author:		Adham Said
// Date:		May 2nd, 2023
// Purpose:		Header file for PlayerPaddle.cpp
//

#pragma once
class PlayerPaddle
{
public:
	PlayerPaddle(HWND);						// constructor

	void Draw(HDC);							// answer WM_PAINT
	void Move(HDC);
	bool Move(HWND);						// update location
	char GetRealTimeInput();

	double dBrickLeft = 0.0;
	double dBrickRight = 0.0;
	double dBrickTop = 0.0;
	double dBrickBottom = 0.0;

	double dCenterBrick = 0.0;

	double x = 0.0;
	double y = 0.0;

private:
	RECT rDim;								// dimensions, location, and size of sphere
	int r, g, b;							// color
	POINT pSpeed;							// x,y speed and direction

	int GetRandomInt(int, int);				// return random integer
};

