#pragma once

#include "BiliniarRectangleElement.h"

class RectangleField
{
private:
	double x0, x1, y0, y1;
	int nx, ny;
 
public:

	RectangleField(double x0, double x1, double y0, double y1, int nx, int ny);
	~RectangleField();

	// accessors and mutators
	double getX0();
	void setX0(double value);

	double getX1();
	void setX1(double value);

	double getY0();
	void setY0(double value);

	double getY1();
	void setY1(double value);

	int getNx();
	void setNx(int value);

	int getNy();
	void setNy(int value);


	double getHx();
	double getHy();

	 
	// 
	void drawField(double scale,
				   double *valuesOfIsolines, 
				   int numberOfIsolines,
				   double(*uFunc)(double x, double y),
				   void(*drawColorFunc)(double x, double y, double x1, double y1, double *u, double scale),
				   void(*drawEdgesFunc)(double x, double y, double x1, double y1, double scale),
				   void(*drawIsolinesFunc)(double x, double y, double x1, double y1, double scale));

};

