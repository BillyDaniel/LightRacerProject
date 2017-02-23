#include "ground.h""



#define MAX_LOADSTRING 1000
// Globale Variablen:
HINSTANCE hInst;								// Aktuelle Instanz
TCHAR szTitle[MAX_LOADSTRING];					// Titelleistentext
TCHAR szWindowClass[MAX_LOADSTRING];			// Klassenname des Hauptfensters
HFONT editfont;
HWND hMain = NULL;
//-----------------------
static char MainWin[] = "MainWin";

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

HBRUSH  hWinCol = CreateSolidBrush(RGB(180, 180, 180));

HWND g_hwnd=NULL;
//timer:
#define TIMER1 111

// Vorwärtsdeklarationen der in diesem Codemodul enthaltenen Funktionen:
/*ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

*/

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{

	
	hInst = hInstance;												//						save in global variable for further use
	// TODO: Hier Code einfügen.
	MSG msg;
	
	// Globale Zeichenfolgen initialisieren
	LoadString(hInstance, 103, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, 104, szWindowClass, MAX_LOADSTRING);
	//register Window													<<<<<<<<<<			STEP ONE: REGISTER WINDOW						!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	WNDCLASSEX wcex;												//						=> Filling out struct WNDCLASSEX
	BOOL Result = TRUE;
	wcex.cbSize = sizeof(WNDCLASSEX);								//						size of this struct (don't know why
	wcex.style = CS_HREDRAW | CS_VREDRAW;							//						?
	wcex.lpfnWndProc = (WNDPROC)WndProc;							//						The corresponding Proc File -> Message loop switch-case file
	wcex.cbClsExtra = 0;											//
	wcex.cbWndExtra = 0;											//
	wcex.hInstance = hInstance;										//						The number of the program
	wcex.hIcon = LoadIcon(hInstance, NULL);							//
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);						//
	wcex.hbrBackground = hWinCol;									//						Background color
	wcex.lpszMenuName = NULL;										//
	wcex.lpszClassName = MainWin;									//						Name of the window (must the the same as later when opening the window)
	wcex.hIconSm = LoadIcon(wcex.hInstance, NULL);					//
	Result = (RegisterClassEx(&wcex) != 0);							//						Register this struct in the OS

				//													STEP TWO: OPENING THE WINDOW with x,y position and xlen, ylen !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	hMain = CreateWindow(MainWin, "RoadView Server Programm", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500, NULL, NULL, hInst, NULL);
	if (!hMain)return 0;
	ShowWindow(hMain, nCmdShow);
	UpdateWindow(hMain);

	//													STEP THRE: Going into the infinity message loop							  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	// Hauptmeldungsschleife:
	bool quit = FALSE;
	while (!quit)
	{
		//if (GetMessage(&msg, NULL, 0, 0) > 0)
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) == TRUE)
		{
			if (msg.message == WM_QUIT){ quit = TRUE; break; }

			
				TranslateMessage(&msg);								//						IF a meessage occurs, the WinProc will be called!!!!
				DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}
///////////////////////////////////////////////////
void redr_win_full(HWND hwnd, bool erase)
	{
	RECT rt;
	GetClientRect(hwnd, &rt);
	InvalidateRect(hwnd, &rt, erase);
	}
input input_info;
///////////////////////////////////
//		This Function is called every time the Left Mouse Button is down
///////////////////////////////////
void OnLBD(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
input_info.l_button_down = TRUE;
}
///////////////////////////////////
//		This Function is called every time the Right Mouse Button is down
///////////////////////////////////
void OnRBD(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
	{
	input_info.r_button_down = TRUE;
	}
///////////////////////////////////
//		This Function is called every time a character key is pressed
///////////////////////////////////
void OnChar(HWND hwnd, UINT ch, int cRepeat)
{

}
///////////////////////////////////
//		This Function is called every time the Left Mouse Button is up
///////////////////////////////////
void OnLBU(HWND hwnd, int x, int y, UINT keyFlags)
{
input_info.l_button_down = FALSE;
	
}
///////////////////////////////////
//		This Function is called every time the Right Mouse Button is up
///////////////////////////////////
void OnRBU(HWND hwnd, int x, int y, UINT keyFlags)
	{
	input_info.r_button_down = FALSE;

	}
///////////////////////////////////
//		This Function is called every time the Mouse Moves
///////////////////////////////////
void OnMM(HWND hwnd, int x, int y, UINT keyFlags)
{
input_info.x_mouse = x;
input_info.y_mouse = y;
if ((keyFlags & MK_LBUTTON) == MK_LBUTTON)
	input_info.l_button_down = TRUE;
else
	input_info.l_button_down = FALSE;
if ((keyFlags & MK_RBUTTON) == MK_RBUTTON)
	input_info.r_button_down = TRUE;
else
	input_info.r_button_down = FALSE;
}
///////////////////////////////////
//		This Function is called once at the begin of a program
///////////////////////////////////
#define TIMER1 1
BGround_ BGround;
BOOL OnCreate(HWND hwnd, CREATESTRUCT FAR* lpCreateStruct)
{
g_hwnd = hwnd;
	editfont = CreateFont(-10, 0, 0, 0, 0, FALSE, 0, 0, 0, 0, 0, 0, 0, "Arial");	
	if (!SetTimer(hwnd, TIMER1, 20, NULL))
		{
		MessageBox(hwnd, "No Timers Available", "Info", MB_OK);
		return FALSE;
		}


	if (BGround.LoadBG("test.bmp") != 0)	//not successful: test.bmp is nowhere not be found
		{
		BGround.InitBG24(500, 500, 255, 255, 255);
		}


	return TRUE;
}

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	HWND hwin;
	
	switch (id)
	{
	default:
		break;
	}

}
//************************************************************************
void OnTimer(HWND hwnd, UINT id)
	{
	redr_win_full(hwnd, FALSE);
	}
//************************************************************************
///////////////////////////////////
//		This Function is called every time the window has to be painted again
///////////////////////////////////

HDC g_hdc = NULL;
void OnPaint(HWND hwnd)
	{
	PAINTSTRUCT PaintStruct;
	smartdraw_ sdraw;
	HDC dc = g_hdc=sdraw.begin(hwnd, &PaintStruct, RGB(255, 255, 255));
	BGround.start();
	BGround.GDIPaint(dc, 0, 0);
	draw_main(input_info);
	
	sdraw.end();
	g_hdc = NULL;
	}
//****************************************************************************
void draw_pixel(int x, int y, int r, int g, int b,int draw_into_background)
	{
	if (!g_hdc) return;
	if(draw_into_background==0)
		SetPixel(g_hdc, x, y, RGB(r, g, b));
	else
		{
		BGround.set_pix(x, y, r, g, b);
		}
	}

void draw_line(int x, int y, int a, int b, int red, int green, int blue, int width)
	{
	if (!g_hdc) return;
	HPEN Stift = CreatePen(PS_SOLID, width, RGB(red, green, blue));
	SelectObject(g_hdc, Stift);
	MoveToEx(g_hdc, x, y, NULL);
	LineTo(g_hdc, a, b);
	DeleteObject(Stift);
	}
/////******************
void draw_text( char text[], int x, int y, int r, int g, int b)
	{
	if (!g_hdc) return;
	COLORREF rgb = RGB(r, g, b);
	SetTextColor(g_hdc, rgb);
	SetBkMode(g_hdc, TRANSPARENT);
	TextOut(g_hdc, x, y, text, strlen(text));
	}
//*************************************************************************
void OnKeyDown(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags)
	{

	switch (vk)
		{
			default:break;
			case 87://w
				input_info.w_key_down = TRUE;
				break;
			case 65://a
				input_info.a_key_down = TRUE;
				break;
			case 83://s
				input_info.s_key_down = TRUE;
				break;
			case 68://d
				input_info.d_key_down = TRUE;
				break;
			case 37://left
				input_info.left_cursor_down = TRUE;
				break;
			case 38://up
				input_info.up_cursor_down = TRUE;
				break;
			case 39://right
				input_info.right_cursor_down = TRUE;
				break;
			case 40://down
				input_info.down_cursor_down = TRUE;
				break;
		}
	}

//*************************************************************************
void OnKeyUp(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags)
	{
	switch (vk)
		{
			default:break;
			case 87://w
			input_info.w_key_down = FALSE;
			break;
			case 65://a
			input_info.a_key_down = FALSE;
			break;
			case 83://s
			input_info.s_key_down = FALSE;
			break;
			case 68://d
			input_info.d_key_down = FALSE;
			break;
			case 37://left
			input_info.left_cursor_down = FALSE;
			break;
			case 38://up
			input_info.up_cursor_down = FALSE;
			break;
			case 39://right
			input_info.right_cursor_down = FALSE;
			break;
			case 40://down
			input_info.down_cursor_down = FALSE;
			break;
		}

	}


//**************************************************************************
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	SCROLLINFO si;


	
	switch (message)
	{
		
		HANDLE_MSG(hwnd, WM_CHAR, OnChar);
		HANDLE_MSG(hwnd, WM_LBUTTONDOWN, OnLBD);
		HANDLE_MSG(hwnd, WM_LBUTTONUP, OnLBU);
		HANDLE_MSG(hwnd, WM_RBUTTONDOWN, OnRBD);
		HANDLE_MSG(hwnd, WM_RBUTTONUP, OnRBU);
		HANDLE_MSG(hwnd, WM_MOUSEMOVE, OnMM);	
		HANDLE_MSG(hwnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hwnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hwnd, WM_TIMER, OnTimer);
		HANDLE_MSG(hwnd, WM_KEYDOWN, OnKeyDown);
		HANDLE_MSG(hwnd, WM_KEYUP, OnKeyUp);

	case WM_ERASEBKGND:
		return (LRESULT)1;
	case WM_DESTROY:
		
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}
///////////////////////////////////////
void set_background(int r, int g, int b)
	{
	BGround.set_background(r, g, b);		
	}