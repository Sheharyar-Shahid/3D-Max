#include<iostream>
#include<Windows.h>
#include<fstream>
#include<shellapi.h>
#pragma comment (lib,"winmm.lib")
#define ICO1 101
#define ID_TRAY_APP_ICON    1001
#define ID_TRAY_EXIT        1002
#define WM_SYSICON          (WM_USER + 1)
using namespace std;

/*variables*/
UINT WM_TASKBAR = 0;
HWND Hwnd;
HMENU Hmenu;
NOTIFYICONDATA notifyIconData;
TCHAR szTIP[64] = TEXT("EyeGate is Running...");
char szClassName[] = "Snoopy's System Tray Demo.";



/*procedures  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void minimize();
void restore();
void InitNotifyIconData();


//
//int WINAPI WinMain(HINSTANCE hThisInstance,
//	HINSTANCE hPrevInstance,
//	LPSTR lpszArgument,
//	int nCmdShow)
ofstream put;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	/* This is the handle for our window */
	MSG messages;            /* Here messages to the application are saved */
	WNDCLASSEX wincl;        /* Data structure for the windowclass */
//	WM_TASKBAR = RegisterWindowMessageA("TaskbarCreated");
	/* The Window structure */
	wincl.hInstance = NULL;//hThisInstance;
	wincl.lpszClassName = szClassName;
	wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
	wincl.style = 0;                 /* Catch double-clicks */
	wincl.cbSize = sizeof(WNDCLASSEX);

	/* Use default icon and mouse-pointer */
	wincl.hIcon = 0;// LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(ICO1));
	wincl.hIconSm = 0;// LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(ICO1));
	wincl.hCursor = 0; LoadCursor(NULL, IDC_ARROW);
	wincl.lpszMenuName = NULL;                 /* No menu */
	wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
	wincl.cbWndExtra = 0;                      /* structure or the window instance */
	wincl.hbrBackground = 0;// (HBRUSH)(CreateSolidBrush(RGB(255, 255, 255)));
	/* Register the window class, and if it fails quit the program */
	if (!RegisterClassEx(&wincl))
	{
		MessageBox(0, "Light failed", "Error", MB_OK);
		return 0;
	}
	/* The class is registered, let's create the program*/
	Hwnd = CreateWindowEx(
		0,                   /* Extended possibilites for variation */
		szClassName,         /* Classname */
		szClassName,       /* Title Text */
		WS_OVERLAPPEDWINDOW, /* default window */
		CW_USEDEFAULT,       /* Windows decides the position */
		CW_USEDEFAULT,       /* where the window ends up on the screen */
		-1,                 /* The programs width */
		-1,                 /* and height in pixels */
		HWND_DESKTOP,        /* The window is a child-window to desktop */
		NULL,                /* No menu */
		0,//hThisInstance,       /* Program Instance handler */
		NULL                 /* No Window Creation data */
		);
	/*Initialize the NOTIFYICONDATA structure only once*/
//	InitNotifyIconData();
	//Shell_NotifyIcon(NIM_ADD, &notifyIconData);
	/* Make the window visible on the screen */
	//ShowWindow(Hwnd, SW_SHOW);

	/* Run the message loop. It will run until GetMessage() returns 0 */

	while (GetMessage(&messages, NULL, 0, 0))
	{
		/* Translate virtual-key messages into character messages */
		TranslateMessage(&messages);
		/* Send message to WindowProcedure */
		DispatchMessage(&messages);
	}

	return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	//if (message == WM_TASKBAR && !IsWindowVisible(Hwnd))
	//{
		//minimize();
		//return 0;
//	}
	
	switch (message)                  /* handle the messages */
	{
	case WM_ENDSESSION:

		while (!GetKeyState(VK_CAPITAL)) {
			keybd_event(VK_CAPITAL,
				0x3A,
				KEYEVENTF_EXTENDEDKEY | 0,
				0);

			// Simulate a key release
			keybd_event(VK_CAPITAL,
				0x3A,
				KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
				0);
		}
	
		//PlaySound(TEXT("SystemStart"), NULL, SND_ALIAS);
		break;
	/*case WM_ACTIVATE:
		Shell_NotifyIcon(NIM_ADD, &notifyIconData);
		break;
	case WM_CREATE:
		
	//	ShowWindow(Hwnd, SW_HIDE);
		Hmenu = CreatePopupMenu();
		menref = &Hmenu;
		AppendMenu(Hmenu, MF_STRING, ID_TRAY_EXIT + 2, TEXT("Show"));
		//if (poweron) 	AppendMenu(Hmenu, MF_STRING, ID_TRAY_EXIT + 1, TEXT("Turn off"));
		else AppendMenu(Hmenu, MF_STRING, ID_TRAY_EXIT + 1, TEXT("Turn on"));
		AppendMenu(Hmenu, MF_STRING, ID_TRAY_EXIT, TEXT("Exit"));
		
		break;
		
	case WM_SYSCOMMAND:
		/*In WM_SYSCOMMAND messages, the four low-order bits of the wParam parameter
		are used internally by the system. To obtain the correct result when testing the value of wParam,
		an application must combine the value 0xFFF0 with the wParam value by using the bitwise AND operator.

		switch (wParam & 0xFFF0)
		{
		case SC_MINIMIZE:
		case SC_CLOSE:
			minimize();
			return 0;
			break;
		}
		break;


		// Our user defined WM_SYSICON message.
	case WM_SYSICON:
	{

		switch (wParam)
		{
		case ID_TRAY_APP_ICON:
			SetForegroundWindow(Hwnd);

			break;
		}



		if (lParam == WM_LBUTTONUP)
		{
			// Get current mouse position.
			POINT curPoint;
			GetCursorPos(&curPoint);
			SetForegroundWindow(Hwnd);

			// TrackPopupMenu blocks the app until TrackPopupMenu returns

			UINT clicked = TrackPopupMenu(Hmenu, TPM_RETURNCMD | TPM_NONOTIFY, curPoint.x, curPoint.y, 0, hwnd, NULL);



			SendMessage(hwnd, WM_NULL, 0, 0); // send benign message to window to make sure the menu goes away.
			if (clicked == ID_TRAY_EXIT + 2)
			{

				//ShowWindow(pshow->getSystemHandle(), SW_RESTORE);
			}
			else
				if (clicked == ID_TRAY_EXIT + 1)
				{

					// quit the application.
					//poweron = !poweron;



					for (size_t i = 0; i < 3; i++)
					{
						DeleteMenu(Hmenu, 0, MF_BYPOSITION);
					}

				//	Hmenu = CreatePopupMenu();
					//AppendMenu(Hmenu, MF_STRING, ID_TRAY_EXIT + 2, TEXT("Show"));
					//if (poweron) 	AppendMenu(Hmenu, MF_STRING, ID_TRAY_EXIT + 1, TEXT("Turn off"));
					//else AppendMenu(Hmenu, MF_STRING, ID_TRAY_EXIT + 1, TEXT("Turn on"));
					//AppendMenu(Hmenu, MF_STRING, ID_TRAY_EXIT, TEXT("Exit"));
				//	altermain();
				}
				else
					if (clicked == ID_TRAY_EXIT)
					{

						// quit the application.
						Shell_NotifyIcon(NIM_DELETE, &notifyIconData);
						PostQuitMessage(0);
						exit(1);
					}
		}
	}
	break;

	// intercept the hittest message..
	case WM_NCHITTEST:
	{
		UINT uHitTest = DefWindowProc(hwnd, WM_NCHITTEST, wParam, lParam);
		if (uHitTest == HTCLIENT)
			return HTCAPTION;
		else
			return uHitTest;
	}

	case WM_CLOSE:

		minimize();
		return 0;
		break;

	case WM_DESTROY:

		PostQuitMessage(0);
		break;
		*/
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}


void minimize()
{
	// hide the main window
	ShowWindow(Hwnd, SW_HIDE);
}


void restore()
{
	ShowWindow(Hwnd, SW_SHOW);
}

void InitNotifyIconData()
{
	memset(&notifyIconData, 0, sizeof(NOTIFYICONDATA));

	notifyIconData.cbSize = sizeof(NOTIFYICONDATA);
	notifyIconData.hWnd = Hwnd;
	notifyIconData.uID = ID_TRAY_APP_ICON;
	notifyIconData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	notifyIconData.uCallbackMessage = WM_SYSICON; //Set up our invented Windows Message
	notifyIconData.hIcon = (HICON)LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(ICO1));
	strncpy_s(notifyIconData.szTip, szTIP, sizeof(szTIP));
}
