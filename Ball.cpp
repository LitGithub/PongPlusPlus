#include "Ball.h"
#include <allegro5/allegro.h>
#include<allegro5\allegro_primitives.h>

//constructor
Ball::Ball(int red, int green, int blue, double x, double y) {
	setColor(red, green, blue);
	setPosition(x, y);
	setXVel(2);
	setYVel(2);
}
//setColor
void Ball::setColor(int red, int green, int blue) {
	r = red;
	g = green;
	b = blue;
}

void Ball::setPosition(double x, double y) {
	xPos = x;
	yPos = y;
}

void Ball::draw() {
	al_draw_filled_rectangle(xPos, yPos, xPos + 30, yPos + 30, al_map_rgb(r, g, b));
}

double Ball::getX() {
	return xPos;
}

double Ball::getY() {
	return yPos;
}

double Ball::getXVel() {
	return xVel;
}

double Ball::getYVel () {
	return yVel;
}

void Ball::setX(double x) {
	xPos = x;
}

void Ball::setY(double y) {
	yPos = y;
}

void Ball::setXVel(double vel) {
	xVel = vel;
}

void Ball::setYVel(double vel) {
	yVel = vel;
}