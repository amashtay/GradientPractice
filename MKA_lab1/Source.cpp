#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include "glut.h"

#include "BiliniarRectangleElement.h"
#include "RectangleField.h"


#define isDisplayPolygonLines true
#define isDisplayTextInPolygon false
#define COUNT_OF_COLOR_AREAS 100
#define COUNT_OF_ISOLINES 70
#define SCALE 80.0

struct Color {
	double value;
	unsigned short red, green, blue;
};
Color rainbow[COUNT_OF_COLOR_AREAS];
GLint Width, Height;

void drawText(std::string text,  int x, int y)
{
	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, Width, 0, Height, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	for (unsigned int i = 0; i < text.length(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, (int)text[i]);//GLUT_BITMAP_9_BY_15
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);

}


void generateColors(double minValue, double maxValue)
{

	double hValues = (maxValue - minValue) / (COUNT_OF_COLOR_AREAS - 1);
	for (size_t i = 0; i < COUNT_OF_COLOR_AREAS; i++)
	{
		rainbow[i].value = minValue + i*hValues;
	}


	//if (COUNT_OF_COLOR_AREAS == 7) {
	//	rainbow[0].red = 255; rainbow[0].green = 0; rainbow[0].blue = 0;	//каждый
	//	rainbow[1].red = 255; rainbow[1].green = 128; rainbow[1].blue = 0;	//охотник
	//	rainbow[2].red = 255; rainbow[2].green = 255; rainbow[2].blue = 0;	//желает
	//	rainbow[3].red = 0; rainbow[3].green = 255; rainbow[3].blue = 0;	//знать
	//	rainbow[4].red = 0; rainbow[4].green = 255; rainbow[4].blue = 255;	//где
	//	rainbow[5].red = 0; rainbow[5].green = 0; rainbow[5].blue = 255;	//сидит
	//	rainbow[6].red = 128; rainbow[6].green = 0; rainbow[6].blue = 128;	//фазан
	//}
	//else if (COUNT_OF_COLOR_AREAS == 2)
	//{
	//	rainbow[0].red = 255; rainbow[0].green = 0; rainbow[0].blue = 0;
	//	rainbow[1].red = 0; rainbow[5].green = 0; rainbow[5].blue = 255;
	//}

	int colorRedMin = 0, colorGreenMin = 5, colorBlueMin = 255;
	int colorRedMax = 0, colorGreenMax = 255, colorBlueMax = 25;

	rainbow[0].red = colorRedMin; rainbow[0].green = colorGreenMin; rainbow[0].blue = colorBlueMin; 
	rainbow[COUNT_OF_COLOR_AREAS - 1].red = colorRedMax; rainbow[COUNT_OF_COLOR_AREAS - 1].green = colorGreenMax; rainbow[COUNT_OF_COLOR_AREAS - 1].blue = colorBlueMax;

	int colorRedH = (colorRedMax - colorRedMin) / (COUNT_OF_COLOR_AREAS - 1);
	int colorGreenH = (colorGreenMax - colorGreenMin) / (COUNT_OF_COLOR_AREAS - 1);
	int colorBlueH = (colorBlueMax - colorBlueMin) / (COUNT_OF_COLOR_AREAS - 1);

	for (size_t i = 0; i < COUNT_OF_COLOR_AREAS; i++)
	{
		rainbow[i].red = colorRedMin + i*colorRedH;
		rainbow[i].green = colorGreenMin + i*colorGreenH;
		rainbow[i].blue = colorBlueMin + i*colorBlueH;
	}

}

double* generateIsolines(double minValue, double maxValue)
{
	double *result = new double[COUNT_OF_ISOLINES];
	double hValues = (maxValue - minValue) / (COUNT_OF_ISOLINES - 1);
	for (size_t i = 0; i < COUNT_OF_ISOLINES; i++)
	{
		result[i] = minValue + i*hValues;
	}

	return  result;
}
                                                                                                                                                                         
void setColorWithPointValue(double u)
{
	int i;
	for (i = 0; i < COUNT_OF_COLOR_AREAS - 1 && u >= rainbow[i + 1].value; i++);
	
	double red = rainbow[i].red;
	double green = rainbow[i].green;
	double blue = rainbow[i].blue;

	glColor3ub(red, green, blue);
}


void drawQuadPolygon(double x, double y, double x1, double y1, double *u, double scale)
{
	glBegin(GL_POLYGON);
	setColorWithPointValue(u[0]);
	glVertex2d(x * scale, y * scale);

	setColorWithPointValue(u[1]);
	glVertex2d(x * scale, y1 * scale);

	setColorWithPointValue(u[2]);
	glVertex2d(x1 * scale, y1 * scale);

	setColorWithPointValue(u[3]);
	glVertex2d(x1 * scale, y * scale);
	glEnd();
}


void drawLinePolygon(double x, double y, double x1, double y1, double *u, double scale)
{
	glColor3ub(0, 0, 0);
	std::string temp;

	glColor4ub(155, 155, 155, 115);
	glBegin(GL_LINE_LOOP);
	std::ostringstream osstream;
	
	osstream << u[0];
	drawText(osstream.str(), x * scale, y * scale);
	glVertex2d(x * scale, y * scale);
	osstream.clear();

	osstream << u[1];
	drawText(osstream.str(), x * scale, y1 * scale);
	glVertex2d(x * scale, y1 * scale);
	osstream.clear();

	osstream << u[3];
	drawText(osstream.str(), x1 * scale, y1 * scale);
	glVertex2d(x1 * scale, y1 * scale);
	osstream.clear();

	osstream << u[3];
	drawText(osstream.str(), x1 * scale, y * scale);
	glVertex2d(x1 * scale, y * scale);
	osstream.clear();
	
	glEnd();
}

void drawLineLoop(double x, double y, double x1, double y1, double scale)
{
	glColor3ui(0,0,0);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glVertex2d(x * scale, y * scale);
	glVertex2d(x * scale, y1 * scale);
	glVertex2d(x1 * scale, y1 * scale);
	glVertex2d(x1 * scale, y * scale);
	glEnd();
}

void drawLineStrip(double x, double y, double x1, double y1, double scale)
{
	glColor3ui(0, 0, 0);
	glLineWidth(2);
	glBegin(GL_LINE_STRIP);
	glVertex2d(x * scale, y * scale);
	glVertex2d(x1 * scale, y1 * scale);
	glEnd();
}

double uFunc(double x, double y)
{
	return x + y;
}

void Display(void)
{
	glClearColor(1, 1, 1, 1); 
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3ub(0, 0, 0);

	
	
	glColor3ub(255, 0, 0);

	BiliniarRectangleElement *linElement = new BiliniarRectangleElement(0.0, 0.0);
	
	generateColors(uFunc(0.0, 0.0), uFunc(13.0, 8.0));
	
	//linElement->setNx(9);
	//linElement->setNy(5);

	//linElement->setHx(8.0);
	//linElement->setHy(4.0);

	//linElement->setUAtIndex(11.0, 0);  //7.0;
	//linElement->setUAtIndex(7.0, 1);   //3.0;
	//linElement->setUAtIndex(23.0, 2);  //linElement->setUAtIndex(13.0, 2);
	//linElement->setUAtIndex(9.0, 3);   //linElement->setUAtIndex(9.0, 3);

	//
	//linElement->drawColorElement(100., drawQuadPolygon);

	//if (isDisplayPolygonLines)
	//	linElement->drawColorElement(100., drawLinePolygon);
	//
	//linElement->drawEdgesOfElement(100., drawLineLoop);
	//
	//linElement->drawIsolines(generateIsolines(7.0, 13.0), COUNT_OF_ISOLINES, 100., drawLineStrip);

	RectangleField *rectangleField = new RectangleField(0.0, 0.0, 13.0, 8.0, 9, 14);
	rectangleField->drawField(SCALE, generateIsolines(uFunc(0.0, 0.0), uFunc(13.0, 8.0)), COUNT_OF_ISOLINES, uFunc, drawQuadPolygon, drawLineLoop, drawLineStrip);



	drawText("sample", Width / 2 - 100, Height / 2);

	glFlush();
	glFinish();
	
	delete linElement;
}

void Reshape(GLint w, GLint h) // При изменении размеров окна
{
	Width = w;
	Height = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "rus");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);

	Width = 1366;
	Height = 768;
	glutInitWindowSize(Width, Height);
	glutCreateWindow("GLUT");
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutIdleFunc(Display);
	glutMainLoop();
	return 1;
}