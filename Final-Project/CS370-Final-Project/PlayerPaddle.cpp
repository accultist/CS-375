// Module:		PlayerPaddle.cpp
// Author:		Adham Said
// Date:		May 2nd, 2023
// Purpose:		Implementation of PlayerPaddle class
//				Construct paddle that will be controlled by player
//

//#include "PlayerPaddle.h"
#include "framework.h"
#include "main.h"
#include <Windows.h>

PlayerPaddle::PlayerPaddle(HWND hWnd) {
	RECT rClient;										// get size of window
	GetClientRect(hWnd, &rClient);

	// set start location
	rDim.left = (rClient.right / 2 - 40);					// start at middle of screen
	rDim.top = (rClient.bottom - 100);					// start at the bottom of window

	// set rectangle size size
	rDim.right = rDim.left + 120;
	rDim.bottom = rDim.top + 20;
	

	// random values for red, green, and blue variables
	r = 205;
	g = 205;
	b = 205;
}

void PlayerPaddle::Draw(HDC hdc)
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

bool PlayerPaddle::Move(HWND hWnd)
{
	RECT rClient;										// get size of window
	GetClientRect(hWnd, &rClient);

	
		char input = GetRealTimeInput();

		// Handle the input
		if (input == 'a')
		{
			// Process 'a' input
			int i = 0;
		}
		else if (input == 'd')
		{
			// Process 'd' input
			int b = 0;
		}
		else
		{
			// handle other input
			// update stored coordinates of paddle
			dBrickLeft = rDim.left;
			dBrickRight = rDim.right;
			dBrickTop = rDim.top;
			dBrickBottom = rDim.bottom;

			// flag objects that are within 50 pixels of the top of the window
			if (rDim.top <= (rClient.top + 50))					// is it close to the top?
			{
				//	return false;									//		flag object for deletion
			}
		}

	

	return true;
}

int PlayerPaddle::GetRandomInt(int iMin, int iMax)
{
	random_device rd;								// non-deterministic generator
	mt19937 gen(rd());								// to seed mersenne twister.
	uniform_int_distribution<> dist(iMin, iMax);	// distribute results inside center rect

	return dist(gen);								// return random # between iMin and iMax
}

char PlayerPaddle::GetRealTimeInput()
{

	char input = '\0';
	DWORD charsRead;

	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD inputRecord;

	//while (true)
	//{
		ReadConsoleInput(hInput, &inputRecord, 1, &charsRead);

		if (inputRecord.EventType == KEY_EVENT && inputRecord.Event.KeyEvent.bKeyDown)
		{
			input = inputRecord.Event.KeyEvent.uChar.AsciiChar;
			
		}
//	}

	return input;
}

