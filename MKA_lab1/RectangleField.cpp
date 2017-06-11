#include "RectangleField.h"

RectangleField::RectangleField(double x0, double y0, double x1, double y1, int nx, int ny)
{
	this->x0 = x0;
	this->y0 = y0;
	this->x1 = x1;
	this->y1 = y1;

	this->nx = nx;
	this->ny = ny;
}


RectangleField::~RectangleField()
{
}

double RectangleField::getX0()
{
	return this->x0;
}

void RectangleField::setX0(double value)
{
	this->x0 = value;
}

double RectangleField::getX1()
{
	return this->x1;
}

void RectangleField::setX1(double value)
{
	this->x1 = value;
}

double RectangleField::getY0()
{
	return this->y0;
}

void RectangleField::setY0(double value)
{
	this->y0 = value;
}

double RectangleField::getY1()
{
	return this->y1;
}

void RectangleField::setY1(double value)
{
	this->y1 = value;
}

int RectangleField::getNx()
{
	return this->nx;
}

void RectangleField::setNx(int value)
{
	this->nx = value;
}

int RectangleField::getNy()
{
	return this->ny;
}

void RectangleField::setNy(int value)
{
	this->ny = value;
}

double RectangleField::getHx()
{
	return (x1 - x0)/ (ny - 1);
}

double RectangleField::getHy()
{
	return (y1 - y0) /(nx - 1);
}

void RectangleField::drawField(double scale,
							   double *valuesOfIsolines,
	                           int numberOfIsolines,
							   double(*uFunc)(double x, double y),
							   void(*drawColorFunc)(double x, double y, double x1, double y1, double *u, double scale),
							   void(*drawEdgesFunc)(double x, double y, double x1, double y1, double scale), 
	                           void(*drawIsolinesFunc)(double x, double y, double x1, double y1, double scale))
{

	double x, y;
	double hx = getHx();
	double hy = getHy();

	double n = (nx - 1) * (ny - 1);

	BiliniarRectangleElement *elements = new BiliniarRectangleElement[n];

	size_t k = 0;
	for (size_t i = 0; i < nx - 1; i++)
	{
		y = y0 + i * hy;
		for (size_t j = 0; j < ny - 1; j++)
		{
			x = x0 + j * hx;


			elements[k].setX0(x);
			elements[k].setY0(y);
			elements[k].setHx(hx);
			elements[k].setHx(hy);
		
			elements[k].setNx(8);
			elements[k].setNy(4);

			elements[k].setUAtIndex(uFunc(x, y), 0);  
			elements[k].setUAtIndex(uFunc(x + hx, y), 1);   
			elements[k].setUAtIndex(uFunc(x, y + hy), 2);  
			elements[k].setUAtIndex(uFunc(x + hx, y + hy), 3);  


			elements[k].drawColorElement(scale, drawColorFunc);
			elements[k].drawEdgesOfElement(scale, drawEdgesFunc);
			//elements[k].drawIsolines(valuesOfIsolines, numberOfIsolines, scale, drawIsolinesFunc);

			k++;
		}
	}
}
