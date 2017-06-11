#pragma once

class BiliniarRectangleElement
{
private:
	int nx;
	int ny;

	double hx;
	double hy;
	double *u;

	double x0, y0;


	double yCoordOfIsolineWithXCoord(double x, double valueOfIsoline);
	double getXValueOfPolygon(double x0, double y0, double x1, double y1, double y);

public:
	BiliniarRectangleElement();
	BiliniarRectangleElement(double x0, double y0);
	~BiliniarRectangleElement();

	// accessors and mutators
	int getNx();
	void setNx(int nx);

	int getNy();
	void setNy(int ny);

	double getHx();
	void setHx(double hx);

	double getHy();
	void setHy(double hy);

	double *getU();
	void setU(double *u);

	double getUAtIndex(int index);
	void setUAtIndex(double u, int index);

	double getX0();
	void setX0(double x0);

	double getY0();
	void setY0(double y0);


	double getXp();
	double getYs();


	// methods
	double valueAtPoint(double x, double y);

	
	void drawColorElement(double scale, void (*drawColorFunc)(double x, double y, double x1, double y1, double *u, double scale));
	
	void drawEdgesOfElement(double scale, void(*drawEdgesFunc)(double x, double y, double x1, double y1, double scale));

	void drawIsolines(double *valuesOfIsolines, int numberOfIsolines, double scale, void(*drawIsolinesFunc)(double x, double y, double x1, double y1, double scale));

};

