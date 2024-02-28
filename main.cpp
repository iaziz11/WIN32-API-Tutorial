#include <windows.h>


LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {

	WNDCLASSW wc = { 0 };

	int screenHeight = 1000;
	int screenWidth = screenHeight;

	// background color of window
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	// cursor in window
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);

	// window instance given by os
	wc.hInstance = hInst;

	// class name of window
	wc.lpszClassName = L"myWindowClass";

	// callback function where messages (events) will be sent to and handled
	wc.lpfnWndProc = WindowProcedure;

	// registers class to allow it to be used as a window
	// returns true or false if successful or not
	if (!RegisterClassW(&wc)) {
		return -1;
	}
	
	// once window is registered, we can create the window
	CreateWindowW(L"myWindowClass", L"Test Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 
		screenWidth, screenHeight, NULL, NULL, NULL, NULL);

	MSG msg = { 0 };

	// GetMessage returns false when application quits
	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}


// hWnd = the window indentifier (which window is calling this function)
// message = the actual message
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wp, LPARAM lp) {
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		// handles any messages that our switch statement does not account for
		return DefWindowProcW(hWnd, message, wp, lp);
	}
}