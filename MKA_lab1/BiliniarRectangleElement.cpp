#include "BiliniarRectangleElement.h"



BiliniarRectangleElement::BiliniarRectangleElement()
{
	hx = 1.0;
	hy = 1.0;

	x0 = 0.0;
	y0 = 0.0;
	nx = 2;
	ny = 2;

	u = new double[4];
	for (int i = 0; i < 4; i++)
	{
		u[i] = 0.0;
	}
}

BiliniarRectangleElement::BiliniarRectangleElement(double x0, double y0)
{
	hx = 1.0;
	hy = 1.0;

	x0 = x0;
	y0 = y0;
	nx = 2;
	ny = 2;

	u = new double[4];
	for (int i = 0; i < 4; i++)
	{
		u[i] = 0.0;
	}
}


BiliniarRectangleElement::~BiliniarRectangleElement()
{
	delete u;
}

int BiliniarRectangleElement::getNx()
{
	return this->nx;
}

void BiliniarRectangleElement::setNx(int nx)
{
	this->nx = nx;
}

int BiliniarRectangleElement::getNy()
{
	return this->ny;
}

void BiliniarRectangleElement::setNy(int ny)
{
	this->ny = ny;
}

double BiliniarRectangleElement::getHx()
{
	return this->hx;
}

void BiliniarRectangleElement::setHx(double hx)
{
	this->hx = hx;
}

double BiliniarRectangleElement::getHy()
{
	return this->hy;
}

void BiliniarRectangleElement::setHy(double hy)
{
	this->hy = hy;
}

double * BiliniarRectangleElement::getU()
{
	return this->u;
}

void BiliniarRectangleElement::setU(double * u)
{
	this->u = u;
}

double BiliniarRectangleElement::getUAtIndex(int index)
{
	if (index >= 0 && index < 4) 
	{
		return this->u[index];
	}
	return 0;
}

void BiliniarRectangleElement::setUAtIndex(double u, int index)
{
	if (index >= 0 && index < 4)
	{
		this->u[index] = u;
	}
}

double BiliniarRectangleElement::getX0()
{
	return this->x0;
}

void BiliniarRectangleElement::setX0(double x0)
{
	this->x0 = x0;
}

double BiliniarRectangleElement::getY0()
{
	return this->y0;
}

void BiliniarRectangleElement::setY0(double y0)
{
	this->y0 = y0;
}

double BiliniarRectangleElement::getXp()
{
	return x0 + hx;
}

double BiliniarRectangleElement::getYs()
{
	return y0 + hy;
}

double BiliniarRectangleElement::valueAtPoint(double x, double y)
{
	double res = 0.0;

	double X1 = (getXp() - x) / getHx();
	double X2 = (x - getX0()) / getHx();
	double Y1 = (getYs() - y) / getHy();
	double Y2 = (y - getY0()) / getHy();
	

	res = u[0] * X1 * Y1 + u[1] * X2 * Y1 + u[2] * X1 * Y2 + u[3] * X2 * Y2;

	return res;
}



void BiliniarRectangleElement::drawColorElement(double scale, void(*drawPolygon)(double x, double y, double x1, double y1, double *u, double scale))
{

	double nnx = getNx() - 1;
	double nny = getNy() - 1;

	double xStep = getHx() / (nnx);
	double yStep = getHy() / (nny);

	for (int i = nny; i >= 1; i--)
	{
		for (int j = 0; j < nnx; j++)
		{
			double x = getX0() + j * xStep;
			double y = getY0() + (i - 1) * yStep;

			double x1 = getX0() + (j + 1) * xStep;
			double y1 = getY0() + i * yStep;

			
			double *uValue = new double[4];
			uValue[0] = valueAtPoint(x,y);
			uValue[1] = valueAtPoint(x, y1);
			uValue[2] = valueAtPoint(x1, y1);
			uValue[3] = valueAtPoint(x1, y);
			
			drawPolygon(x,y, x1, y1, uValue, scale);
		}
	}
}

void BiliniarRectangleElement::drawEdgesOfElement(double scale, void(*drawFunc)(double x, double y, double x1, double y1, double scale))
{
	drawFunc(x0, y0, x0 + hx, y0 + hy, scale);
}


double BiliniarRectangleElement::yCoordOfIsolineWithXCoord(double x, double valueOfIsoline)
{
	double a = u[0] / (hx*hy);
	double b = u[1] / (hx*hy);
	double c = u[2] / (hx*hy);
	double d = u[3] / (hx*hy);


	return (valueOfIsoline - a*getXp()*getYs() + a*getYs()*x - b*getYs()*x + b*getX0()*getYs() - c*getXp()*getY0() - c*getY0()*x + d*getY0()*x - d*getX0()*getY0()) / 
		   (a*x - a*getXp() - b*x + b*getX0() + c*getXp() - c*x + d*x - d*getX0());
}

double BiliniarRectangleElement::getXValueOfPolygon(double x0, double y0, double x1, double y1, double y)
{
	double res;

	double a = (y1 - y0) / (x1 - x0);
	double b = y0 - a*x0;

	res = (y - b) / a;
	return res;
}

void BiliniarRectangleElement::drawIsolines(double *valuesOfIsolines, int numberOfIsolines, double scale, void(*drawFunc)(double x, double y, double x1, double y1, double scale))
{

	double nnx = getNx() - 1;

	double xStep = getHx() / (nnx);
	
	for (int j = 0; j < nnx; j++)
	{
		double x = getX0() + j * xStep;
		double x1 = getX0() + (j + 1) * xStep;

		for (size_t i = 0; i < numberOfIsolines; i++)
		{
			double y = yCoordOfIsolineWithXCoord(x, valuesOfIsolines[i]);
			double y1 = yCoordOfIsolineWithXCoord(x1, valuesOfIsolines[i]);
			
			if (y <= getYs() && y1 <= getYs())
			{
				drawFunc(x, y, x1, y1, scale);
			}
			else
			{
				drawFunc(
					(y <= getYs() && y >= getY0()) ? x : getXValueOfPolygon(x, y, x1, y1, getYs()),
					(y <= getYs() && y >= getY0()) ? y : getYs(),
					(y1 <= getYs() && y1 >= getY0()) ? x1 : getXValueOfPolygon(x, y, x1, y1, getYs()),
					(y1 <= getYs() && y1 >= getY0()) ? y1 : getYs(),
					scale
				);
			}
		}
	}
}