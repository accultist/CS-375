// CS370-Final-Project.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "main.h"

#define MAX_LOADSTRING 100
#define WM_TIMER_CREATE 2001
#define WM_TIMER_MOVE 2002

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// declared vectors
vector<Brick> vBrick;                           // responsible for holding brick objects
vector<PlayerPaddle> vPlayerPaddle;             // player paddle
vector<Ball> vBall;                             // bouncing ball



/*declared enumeration data types for char input from user,
    user input will be converted to uppercase instead of having multiple symbols*/
enum symbols {
    //LEFT = 'A',
    RIGHT = 'D',
    DOWN = 'S',
   // UP = 'W'
};
//left arrow : 37
//up arrow : 38
//right arrow : 39
//down arrow : 40



// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CS370FINALPROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CS370FINALPROJECT));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CS370FINALPROJECT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CS370FINALPROJECT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

  // HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
   //   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   //HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
   //   3.7, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   // setup display window
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT, 1055, 600, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // reduce flicker by double-buffering 

        // get window client rectangle sizes
        RECT rClient;
        int cx, cy;
        GetClientRect(hWnd, &rClient);
        cx = rClient.right - rClient.left;
        cy = rClient.bottom - rClient.top;

        // create memory device
        HDC memdc = CreateCompatibleDC(hdc);			// create memory copy of dc
        unsigned bpp = GetDeviceCaps(hdc, BITSPIXEL);	// discover color depth
        HBITMAP hBmp = CreateBitmap(cx, cy, 1, bpp, NULL); // create bitmap for background
        HBITMAP hTmpBmp = (HBITMAP)SelectObject(memdc, (HGDIOBJ)hBmp); // fill memory dc


        // draw GDI background
        FillRect(memdc, &rClient, (HBRUSH)GetStockObject(WHITE_BRUSH));

        for (auto& vObj : vBrick)					// scroll through vector
        {
            vObj.Draw(memdc);						// draw object from node
        }
        for(auto & vObj : vBall)					// scroll through vector
        {
            vObj.Draw(memdc);						// draw object from node
        }

        /*
        for (auto& vObj : vPlayerPaddle)			// scroll through vector
        {
            vObj.Draw(memdc);						// draw object from node
        }
        */

        //update the main DC
        BitBlt(hdc, 0, 0, cx, cy, memdc, 0, 0, SRCCOPY); // blt memory dc to window dc

        // clean up
        SelectObject(memdc, (HGDIOBJ)hTmpBmp);			// return to original dc
        DeleteDC(memdc);								// delete temp dc
        DeleteObject(hBmp);								// delete object

        // end
        EndPaint(hWnd, &ps);
        }
        break;
    case WM_TIMER:
    {
        if (wParam == WM_TIMER_CREATE)						  // create timer
        {
            Brick appendNode(hWnd);					          // create new node object

            vBrick.push_back(appendNode);				      // append node to the end of the list

            InvalidateRect(hWnd,					// force WM_PAINT message
                NULL,								// entire window
                FALSE);								// false for non-flicker with hmemdc

            // PlayerPaddle appendNode(hWnd);				// create new node object

            // vPlayerPaddle.push_back(appendNode);			 // append node to the end of the list

            // once we reach 91 bricks, delete timer as we do not want to create anymore objects
            // basically allows for 7 rows with the default window size
            if (vBrick.size() == 91) {
                KillTimer(hWnd, WM_TIMER_CREATE);
                SetTimer(hWnd, WM_TIMER_MOVE, 10, NULL);
            }

            // we only want to create one instance of the moveable ball
            if (vBrick.size() == 1) {
                Ball moveableBall(hWnd);					// create new node object for bouncing ball
                vBall.push_back(moveableBall);

                PlayerPaddle moveablePaddle(hWnd);			// create new node object for controlled paddle
                vPlayerPaddle.push_back(moveablePaddle);

            }
        }
        
        else if (wParam == WM_TIMER_MOVE)				      // move timer
        {
            
            


            int iPos = 0;                                     // save position of object in vector 
            double dBrick_lastpos = 0;
            
            vBall.at(0).Move(hWnd);                 // move ball

            vPlayerPaddle.at(0).Move(hWnd);

            InvalidateRect(hWnd,					// force WM_PAINT message
                NULL,								// entire window
                FALSE);								// false for non-flicker with hmemdc
          
            for (auto& vBrickObj : vBrick)					      // scroll through vector
            {

                    //double dBrickPos = (vBrick.at(iPos).dBrickLeft - vBrick.at(iPos).dBrickTop);
                    double dBrickPos_x_axis = (vBrick.at(iPos).dBrickRight / 2);
                    double dPaddlePos_x_axis = (vPlayerPaddle.at(0).dBrickRight / 2);

                   //double dBallPos = (vBall.at(0).dBallLeft - vBall.at(0).dBallTop);
                    double dBallPos_x_axis = (vBall.at(0).dBallRight / 2);

                    double dBrickPos_y_axis = (vBrick.at(iPos).dBrickBottom / 2);
                    //double dBallPos = (vBall.at(0).dBallLeft - vBall.at(0).dBallTop);
                    double dBallPos_y_axis = (vBall.at(0).dBallBottom / 2);
                    double dPaddlePos_y_axis = (vPlayerPaddle.at(0).dBrickBottom / 2);
                    
                    //if (dBallPos_x_axis < dPaddlePos_x_axis && dBallPos_y_axis == dPaddlePos_y_axis) {
                    if (dPaddlePos_y_axis == dBallPos_y_axis) {
                        vBall.at(0).Direction(hWnd);                // call function to change to opposite direction 
                        vBall.at(0).SetColorSpeed(hWnd);                // call function to change increase speed + red color

                    }

                    //if (vBrick.at(iPos).dBrickRight == vBall.at(0).dBallLeft && vBrick.at(iPos).dBrickBottom == vBall.at(0).dBallTop) {
                    if (dBallPos_x_axis <= dBrickPos_x_axis && dBallPos_y_axis == dBrickPos_y_axis) {
                        // this is a multiple condition if check that verifys several things for brick collision
                        // 1: check if vector position in brick vector is valid (there are a total of 91 bricks
                        // 2: if last recorded collision was along the same axis, ignore this particular instance
                        //    - this is because there is a bug where a brick a couple of positions away on the
                        //      x-axis can have a false hit

                        if (iPos >= 0 && iPos <= 91 && dBrick_lastpos != dBallPos_y_axis) {
                            vBrick.erase(vBrick.begin() + iPos);
                            vBall.at(0).Direction(hWnd);                // call function to change to opposite direction 
                            dBrick_lastpos = dBallPos_y_axis;            // record position for error check
                            vBall.at(0).SetColorSpeed(hWnd);                // call function to change increase speed + red color
                            break;
                        }
                       

                    }
                    iPos++;                             // add 1 to position counter

                    InvalidateRect(hWnd,					// force WM_PAINT message
                        NULL,								// entire window
                        FALSE);								// false for non-flicker with hmemdc
            }
        
        }
    }
    break;
    case WM_CREATE:
    {
        // create timers for ball objects
        SetTimer(hWnd, WM_TIMER_CREATE, 1, NULL);       // default was 500
        //SetTimer(hWnd, WM_TIMER_MOVE, 10, NULL);
        
        
    }
    break;
    case WM_DESTROY:
        vBrick.clear();								// empty vector list
        KillTimer(hWnd, WM_TIMER_MOVE);
        KillTimer(hWnd, WM_TIMER_CREATE);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
