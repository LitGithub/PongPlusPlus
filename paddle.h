#pragma once
class Paddle {
private:
	int r;
	int g;
	int b;
	double xPos;
	double yPos;
	double xVel;
	double yVel;
public:
	Paddle(int red, int green, int blue, double x, double y);
	void setColor(int red, int green, int blue);
	void setPosition(double x, double y);
	void setX(double x);
	void setY(double y);
	void draw();

	double getXVel();
	double getYVel();
	double getX();
	double getY();
};