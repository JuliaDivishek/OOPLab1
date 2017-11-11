#include "Draw.h"


Draw::Draw()
{
	outline = { 0, 0, 0 };
	filler = { 255,255,255 };
	hNewPen = CreatePen(PS_SOLID, 3, RGB(this->outline.R, this->outline.G, this->outline.B));
	hNewBrush = CreateSolidBrush(RGB(this->filler.R, this->filler.G, this->filler.B));
}

Draw::Draw(color *outlineColor, color *fillerColor)
{
	outline = *outlineColor;
	filler = *fillerColor;
	hNewPen = CreatePen(PS_SOLID, 3, RGB(this->outline.R, this->outline.G, this->outline.B));
	hNewBrush = CreateSolidBrush(RGB(this->filler.R, this->filler.G, this->filler.B));

}



Draw::~Draw()
{
}

void Draw::drawRhomb(HDC hdc, Rhomb *rhomb)
{
	this->hNewPen = SelectPen(hdc, this->hNewPen);
	this->hNewBrush = SelectBrush(hdc, GetStockBrush(NULL_BRUSH));
	Polygon(hdc, rhomb->points, 4);
	setDefaultBrush();
	system("pause");

}

void Draw::drawFilledRhomb(HDC hdc, Rhomb *rhomb)
{
	this->hNewPen = SelectPen(hdc, this->hNewPen);
	this->hNewBrush = SelectBrush(hdc, this->hNewBrush);
	Polygon(hdc, rhomb->points, 4);
	system("pause");
}


void Draw::setPen(int R, int G, int B)
{
	this->hNewPen = CreatePen(PS_SOLID, 3, RGB(R, G, B));
}

void Draw::setDefaultPen()
{
	this->hNewPen = CreatePen(PS_SOLID, 3, RGB(this->outline.R, this->outline.G, this->outline.B));
}

void Draw::setBrush(int R, int G, int B)
{
	this->hNewBrush = CreateSolidBrush(RGB(R, G, B));
}

void Draw::setDefaultBrush()
{
	this->hNewBrush = CreateSolidBrush(RGB(this->filler.R, this->filler.G, this->filler.B));
}

