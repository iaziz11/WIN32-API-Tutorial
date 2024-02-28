#include <windows.h>

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define CHANGE_TITLE 4


LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND);

void AddControls(HWND);

HMENU hMenu;
HWND hEdit;


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {

	WNDCLASSW wc = { 0 };

	
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
		500, 500, NULL, NULL, NULL, NULL);

	MSG msg = { 0 };

	// GetMessage returns false when application quits
	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}


// hWnd = the window indentifier (which window is calling this function)
// message = the actual message given by DispatchMessage
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wp, LPARAM lp) {
	switch (message) {

		// when user clicks menu item, id of menu item is passed to wp
		case WM_COMMAND:
			switch (wp){
			case FILE_MENU_NEW:
				// produces sound
				MessageBeep(MB_OK);
				break;
			case FILE_MENU_OPEN:
				MessageBeep(MB_ICONERROR);
				break;
			case FILE_MENU_EXIT:
				DestroyWindow(hWnd);
				break;
			case CHANGE_TITLE:
				WCHAR text[100];
				GetWindowTextW(hEdit, text, 100);
				SetWindowTextW(hWnd, text);
				break;
			default:
				return DefWindowProcW(hWnd, message, wp, lp);;
			} 
		// passed once when window is created using the CreateWindow function
		case WM_CREATE:
			AddMenus(hWnd);
			AddControls(hWnd);
			break;
		// when user clicks x button
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			// handles any messages that our switch statement does not account for
			return DefWindowProcW(hWnd, message, wp, lp);
	}
}

void AddMenus(HWND hWnd) {
	hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
	HMENU hSubMenu = CreateMenu();

	AppendMenu(hSubMenu, MF_STRING, CHANGE_TITLE, L"Change Title");

	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, L"New");
	AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSubMenu, L"Open submenu");
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, L"Exit");

	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"File");
	AppendMenu(hMenu, MF_STRING, NULL, L"Help");

	SetMenu(hWnd, hMenu);
}

void AddControls(HWND hWnd) {
	// need WS_CHILD for all children windows
	CreateWindowW(L"static", L"Enter Text Here: ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 200, 100, 100, 50, hWnd, NULL, NULL, NULL);
	hEdit = CreateWindowW(L"edit", L"...", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 200, 152, 100, 50, hWnd, NULL, NULL, NULL);
}