#include "ground.h"

float difference(float a, float b)
	{
	float c = a - b;
	c = fabs(c);
	return c;
	}


//***************************
/*int BGround_::InsertBMP(CRaster *img, int x, int y)
	{
	x *= 3;
	int h = img->Height;
	int w = img->Width;
	if (x<0)x = 0;
	//if((x+w)>Width)x=Width-w;
	for (int ii = 0; ii<h; ii++)
		{
		if ((ii + y)<0) continue;
		blackcpy(Img + (ii + y)*BytesPerRow + x, img->Raster + ii*img->BytesPerRow, w);
		}
	return 0;
	}*/
//*********************************************************************************
int BGround_::start()
	{
	if (!Raster) return 0;
	if (!Img) return 0;
	memcpy(Img, Raster, BytesPerRow*Height);
	return 1;
	}
///////////////7
int BGround_::LoadBG(char * szFile)
	{
	if (Raster) delete[] Raster;
	if (pbmi)	delete[] pbmi;
	Raster = 0;
	pbmi = 0;

	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;

	FILE *pp = fopen(szFile, "rb");
	if (!pp) return 1;
	fclose(pp);
	// Open file.
	ifstream bmpfile(szFile, ios::in | ios::binary);
	if (!bmpfile.is_open()) return 1;		// Error opening file

											// Load bitmap fileheader & infoheader
	bmpfile.read((char*)&bmfh, sizeof(BITMAPFILEHEADER));
	bmpfile.read((char*)&bmih, sizeof(BITMAPINFOHEADER));

	// Check filetype signature
	if (bmfh.bfType != 'MB') return 2;		// File is not BMP

											// Assign some short variables:
	BPP = bmih.biBitCount;
	Width = bmih.biWidth;
	Height = (bmih.biHeight>0) ? bmih.biHeight : -bmih.biHeight; // absoulte value
	BytesPerRow = Width * BPP / 8;
	BytesPerRow += (4 - BytesPerRow % 4) % 4;	// int alignment

												// If BPP aren't 24, load Palette:
	if (BPP == 24)
		{
		pbmi = (BITMAPINFO*)new char[sizeof(BITMAPINFO)];
		}
	else
		{
		pbmi = (BITMAPINFO*) new char[sizeof(BITMAPINFOHEADER) + (1 << BPP)*sizeof(RGBQUAD)];
		Palette = (RGBQUAD*)((char*)pbmi + sizeof(BITMAPINFOHEADER));
		bmpfile.read((char*)Palette, sizeof(RGBQUAD) * (1 << BPP));
		}
	pbmi->bmiHeader = bmih;

	// Load Raster
	bmpfile.seekg(bmfh.bfOffBits, ios::beg);
	Raster = new char[BytesPerRow*Height];
	Img = new char[BytesPerRow*Height * 2];

	// (if height is positive the bmp is bottom-up, read it reversed)
	if (bmih.biHeight>0)
		for (int n = Height - 1; n >= 0; n--)
			bmpfile.read(Raster + BytesPerRow*n, BytesPerRow);
	else
		bmpfile.read(Raster, BytesPerRow*Height);
	// so, we always have a up-bottom raster (that is negative height for windows):
	pbmi->bmiHeader.biHeight = -Height;
	bmpfile.close();

	return 0;
	}

//******************************
int BGround_::InitBG24(int x, int y, int r, int g, int b)
	{
	if (Raster) delete[] Raster;
	if (pbmi)	delete[] pbmi;
	Raster = 0;
	pbmi = 0;


	
	Width = x;
	BPP = 24;
	Height = (y>0) ? y : -y; // absoulte value

	BytesPerRow = Width * BPP / 8;
	BytesPerRow += (4 - BytesPerRow % 4) % 4;	// int alignment
	
							
	pbmi = (BITMAPINFO*)new char[sizeof(BITMAPINFO)];
		
	

	Raster = new char[BytesPerRow*Height];
	Img = new char[BytesPerRow*Height * 2];

	set_background(r, g, b);

	pbmi->bmiHeader.biSize = 40;
	pbmi->bmiHeader.biWidth = Width;
	pbmi->bmiHeader.biHeight = -Height;
	pbmi->bmiHeader.biPlanes = 1;
	pbmi->bmiHeader.biBitCount = BPP;
	pbmi->bmiHeader.biCompression = 0;
	pbmi->bmiHeader.biSizeImage = Width * Height * 3 + 2;
	pbmi->bmiHeader.biXPelsPerMeter = 2834;
	pbmi->bmiHeader.biYPelsPerMeter = 2834;
	pbmi->bmiHeader.biClrUsed = 0;
	pbmi->bmiHeader.biClrImportant = 0;
	

	return 0;
	}
int BGround_::GDIPaint(HDC hdc, int x, int y)
	{
	if (!Img) return 0;
	// Paint the image to the device.
	return SetDIBitsToDevice(hdc, x, y, Width, Height, 0, 0,
							 0, Height, (LPVOID)Img, pbmi, 0);
	}