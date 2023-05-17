// Module:		Brick.cpp
// Author:		Adham Said
// Date:		April 28th, 2023
// Purpose:		Implementation of Brick class
//				Create bricks that will be hit in game
//

#include "main.h"

// global variable(s)
int iNextBrickPos = 0;					// prevents overlap by tracking the right position of previous brick
int iTierBy20 = 0;						// tracks total rows (standard is 3)

// intialize rgb max int limitations
// these will decrease with every creation of a brick
int iRedLimit = 255;
int iGreenLimit = 255;
int iBlueLimit = 255;


int iBrickCount = 0;



Brick::Brick(HWND hWnd) {
	RECT rClient;										// get size of window
	GetClientRect(hWnd, &rClient);

	// if we would potentially create a new object outside of the actual window, create a new row
	if (iNextBrickPos >= rClient.right) {
		iNextBrickPos = 0;							// reset brick pos (starts far left of window)
		iTierBy20 = iTierBy20 + 20;					// increment by 20 (down by 20 pixels on y-axis) therefore creating a new row
	}

	rDim.left = (rClient.left + iNextBrickPos);		// increments based upon previous brick's location, bricks will be side by side
	rDim.top = rClient.top + iTierBy20;				// start at the bottom of window

	// set rectangle size size
	rDim.right = rDim.left + 80;
	rDim.bottom = rDim.top + 20;

	// store sides of brick for collision with ball
	dBrickLeft = rDim.left;					
	dBrickRight = rDim.right;
	dBrickTop = rDim.top;
	dBrickBottom = rDim.bottom;

	// random values for red, green, and blue variables
	r = GetRandomInt(0, iRedLimit);
	g = GetRandomInt(0, iGreenLimit);
	b = GetRandomInt(0, iBlueLimit);

	// if check makes sure we don't give our rgb limits negative values
	// note that currently there are 91 bricks being created
	// decrement rgb values by 2 ea, which will gradually make the bricks darker
	if (iRedLimit > 4 ) {
		iRedLimit = (iRedLimit - 2);
		iGreenLimit = (iGreenLimit - 2);
		iBlueLimit = (iBlueLimit - 2);
	}
	
	// increment new left position for next brick
	iNextBrickPos = (iNextBrickPos + 80);
}

void Brick::Draw(HDC hdc)
{
	// create brushes
	HBRUSH brush, oldBrush;
	brush = CreateSolidBrush(RGB(r, g, b));
	oldBrush = (HBRUSH)SelectObject(hdc, brush);

	// draw rectangle
	Rectangle(hdc, rDim.left, rDim.top, rDim.right, rDim.bottom);

	// release brushes
	SelectObject(hdc, oldBrush);
	DeleteObject(brush);
}

bool Brick::Delete(HWND hWnd)
{
	return false;
}

int Brick::UpdatePos(int iNum)
{
	iRightPos = (iRightPos + 80);

	return iRightPos;
}

int Brick::GetRandomInt(int iMin, int iMax)
{
	random_device rd;								// non-deterministic generator
	mt19937 gen(rd());								// to seed mersenne twister.
	uniform_int_distribution<> dist(iMin, iMax);	// distribute results inside center rect

	return dist(gen);								// return random # between iMin and iMax
}

// debug function
void Brick::SetColor()
{
	r = 255;
	g = 0;
	b = 0;
}

