// Module:		Brick.cpp
// Author:		Adham Said
// Date:		April 28th, 2023
// Purpose:		Header file for Brick.cpp
//				GDI graphic tool
//


#pragma once
class Brick {
public:
	Brick(HWND);							// constructor

	void Draw(HDC);							// answer WM_PAINT
	bool Delete(HWND);						// mark for deletion
	int UpdatePos(int);

	double dBrickLeft = 0.0;
	double dBrickRight = 0.0;
	double dBrickTop = 0.0;
	double dBrickBottom = 0.0;

	double dCenterBrick = 0.0;

	double x = 0.0;
	double y = 0.0;

	void SetColor();


private:
	RECT rDim;								// dimensions, location, and size of sphere
	int r, g, b;							// color
	POINT pSpeed;							// x,y speed and direction

	int iRightPos = 0;						// track position of brick, to prevent overlay
	int GetRandomInt(int, int);				// return random integer
};