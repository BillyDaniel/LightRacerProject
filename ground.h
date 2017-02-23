#define WIN32_LEAN_AND_MEAN  
#include <windows.h>
#include <windowsx.h>
#include <malloc.h>
#include <stdio.h>
#include <conio.h>
#include <io.h>
#include <time.h>
#include <stdlib.h>
#include <sys/timeb.h>
#include <fstream>
using namespace std;
#include <direct.h>
#include <commdlg.h>
#include <malloc.h>
#include <cmath>
#include <string.h>
#include <tchar.h>



class smartdraw_
	{
	private:
		HWND failsavehwnd;
		HDC m_dc, m_DC;
		HBITMAP hbmMem, hbmOld;
		PAINTSTRUCT *ps;
		bool sub_dc;
		RECT drawrect;
	public:
		smartdraw_()
			{
			sub_dc = FALSE;
			failsavehwnd = NULL;
			ps = NULL;
			m_dc = m_DC = NULL;
			}
		~smartdraw_()
			{
			if (failsavehwnd)
				end();
			}
		HDC begin(HWND hwnd, HDC dc_parent, COLORREF bg, RECT rect)
			{
			failsavehwnd = hwnd;
			sub_dc = TRUE;
			m_DC = dc_parent;
			m_dc = CreateCompatibleDC(m_DC);
			RECT rc;
			GetClientRect(hwnd, &rc);
			hbmMem = CreateCompatibleBitmap(m_DC, rc.right - rc.left, 2000);
			hbmOld = (HBITMAP)SelectObject(m_dc, hbmMem);
			HBRUSH hbrBkGnd = CreateSolidBrush(bg);
			FillRect(m_dc, &rc, hbrBkGnd);
			DeleteObject(hbrBkGnd);
			drawrect = rect;
			ps = NULL;
			return m_dc;
			}
		HDC begin(HWND hwnd, PAINTSTRUCT *PaintStruct, COLORREF bg)
			{
			ps = PaintStruct;
			failsavehwnd = hwnd;
			m_DC = BeginPaint(hwnd, PaintStruct);
			m_dc = CreateCompatibleDC(m_DC);
			RECT rc;
			GetClientRect(hwnd, &rc);
			hbmMem = CreateCompatibleBitmap(m_DC, rc.right - rc.left, 2000);
			hbmOld = (HBITMAP)SelectObject(m_dc, hbmMem);
			HBRUSH hbrBkGnd = CreateSolidBrush(bg);
			FillRect(m_dc, &rc, hbrBkGnd);
			DeleteObject(hbrBkGnd);
			return m_dc;
			}

		void end()
			{
			RECT rc;
			if (!failsavehwnd)return;
			GetClientRect(failsavehwnd, &rc);
			if (m_DC && m_dc)
				{
				if (!sub_dc)	BitBlt(m_DC, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, m_dc, 0, 0, SRCCOPY);
				else			BitBlt(m_DC, drawrect.left, drawrect.top, drawrect.right, drawrect.bottom, m_dc, drawrect.left, drawrect.top, SRCCOPY);
				}
			SelectObject(m_dc, hbmOld);
			if (hbmMem)	DeleteObject(hbmMem);
			if (m_dc)	DeleteDC(m_dc);
			if (ps)		EndPaint(failsavehwnd, ps);
			failsavehwnd = NULL;
			}
	};


class input
	{
	public:
	int l_button_down;		//left mouse button down	1 .. down	0 .. up
	int r_button_down;		//right mouse button down	1 .. down	0 .. up
	int x_mouse;			//mouse coordinates in the window (x)
	int y_mouse;			//mouse coordinates in the window (y)
	int w_key_down;			//w key down	1 .. down	0 .. up
	int a_key_down;		//a key down	1 .. down	0 .. up
	int s_key_down;		//s key down	1 .. down	0 .. up
	int d_key_down;		//d key down	1 .. down	0 .. up
	int up_cursor_down;		//cursor up key down	1 .. down	0 .. up
	int down_cursor_down;	//cursor down key down	1 .. down	0 .. up
	int left_cursor_down;	//cursor left key down	1 .. down	0 .. up
	int right_cursor_down;	//cursor right key down	1 .. down	0 .. up
	input()
	{
		 l_button_down = 0;		//left mouse button down	1 .. down	0 .. up
		 r_button_down = 0;		//right mouse button down	1 .. down	0 .. up
		 x_mouse = 0;			//mouse coordinates in the window (x)
		 y_mouse = 0;			//mouse coordinates in the window (y)
		 w_key_down = 0;			//w key down	1 .. down	0 .. up
		 a_key_down = 0;		//a key down	1 .. down	0 .. up
		 s_key_down = 0;		//s key down	1 .. down	0 .. up
		 d_key_down = 0;		//d key down	1 .. down	0 .. up
		 up_cursor_down = 0;		//cursor up key down	1 .. down	0 .. up
		 down_cursor_down = 0;	//cursor down key down	1 .. down	0 .. up
		 left_cursor_down = 0;	//cursor left key down	1 .. down	0 .. up
		 right_cursor_down = 0;	//cursor right key down	1 .. down	0 .. up
	}
	};

void draw_main(input input_info);
void draw_text(char text[], int x, int y, int r, int g, int b);
void draw_pixel(int x, int y, int r, int g, int b, int draw_into_background);
void draw_line(int x, int y, int a, int b, int red, int green, int blue, int width);
void set_background(int r, int g, int b);

//////////////////////////////
//allmighty bground class
class BGround_
	{
	private:
		int Width, Height;		// Dimensions
		int BPP;				// Bits Per Pixel.
		char *Raster;			// Bits of the Image.
		char *Img;			// Bits of the Image.
		RGBQUAD * Palette;		// RGB Palette for the image.
		int BytesPerRow;		// Row Width (in bytes).
		BITMAPINFO *pbmi;		// BITMAPINFO structure

	public:
		void reset();
		RECT get_Rect() { RECT rc; rc.bottom = Height; rc.right = Width; return rc; Img = NULL; }

		void set_background(int r, int g, int b)
			{
			for (int xx = 0; xx < Width; xx++)
				for (int yy = 0; yy < Height; yy++)
					set_pix(xx, yy, r, g, b);
			}

		// Member functions (defined later):
		int LoadBG(char * szFile);
		int InitBG24(int x,int y,int r,int g,int b);
		//int InsertBMP(CRaster *img, int x, int y);
		//int InsertBMP(CRaster *img, int x, int y, int divfaktor);
	//	int InsertBMPRot(CRaster *img, int x, int y);
	//	int InsertBMPRot(CRaster *img, int x, int y, int divfaktor);
		int GDIPaint(HDC hdc, int x, int y);
		int start();
		BGround_() { Raster = NULL; pbmi = NULL; }
		~BGround_()
			{
			if (Raster)
				delete[]Raster;
			if (pbmi)
				delete[]pbmi;
			}
		//draws a pixel
		void set_pix(int x, int y, int r, int g, int b)
			{
			if (!Raster)
				return;
			if (x >= Width)return;
			if (x <0)return;
			if (y >= Height)return;
			if (y <0)return;

			Raster[x * 3 + Width*y * 3 + 0] = b;
			Raster[x * 3 + Width*y * 3 + 1] = g;
			Raster[x * 3 + Width*y * 3 + 2] = r;

			}
	};
