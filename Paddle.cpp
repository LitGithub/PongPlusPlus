#include "Paddle.h"
#include <allegro5/allegro.h>
#include<allegro5\allegro_primitives.h>

//constructor
Paddle::Paddle(int red, int green, int blue, double x, double y) {
	setColor(red, green, blue);
	setPosition(x, y);
}
//setColor
void Paddle::setColor(int red, int green, int blue) {
	r = red;
	g = green;
	b = blue;
}

void Paddle::setPosition(double x, double y) {
	xPos = x;
	yPos = y;
}

void Paddle::draw() {
	al_draw_filled_rectangle(xPos, yPos, xPos + 20, yPos + 100, al_map_rgb(r, g, b));
}

double Paddle::getX() {
	return xPos;
}

double Paddle::getY() {
	return yPos;
}

double Paddle::getXVel() {
	return xVel;
}

double Paddle::getYVel() {
	return yVel;
}

void Paddle::setX(double x) {
	xPos = x;
}

void Paddle::setY(double y) {
	yPos = y;
}