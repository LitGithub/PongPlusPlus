#include <allegro5/allegro.h>
#include<allegro5\allegro_primitives.h>
#include <iostream>
#include "ball.h"
#include "paddle.h"
using namespace std;

int stage = 0;
int red = 255;
int green = 0;
int blue = 0;
void rainbow();

int main() {
	//init allegro stuff
	al_init();
	al_init_primitives_addon();
	al_install_keyboard();
	//allegro display / timer
	ALLEGRO_DISPLAY* display = al_create_display(500, 500);
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60);
	al_start_timer(timer);

	enum MYKEYS {
		KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_W, KEY_S
	};

	Ball PongBall(0, 255, 255, 250, 250);
	Paddle paddle1(255, 255, 255, 10, 250);
	Paddle paddle2(255, 255, 255, 470, 250);

	bool key[6] = { false, false, false, false };
	bool redraw = true;

	//ball thingy
	double xpos = PongBall.getX();
	double ypos = PongBall.getY();
	double vx = PongBall.getXVel();
	double vy = PongBall.getYVel();

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	while (1) {
		//gets keyboard input
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (xpos < 0) {
			vx *= 0;
			vy *= 0;
		}

		if (xpos + 30 >= 500) {
			vx *= 0;
			vy *= 0;
		}
		if (ypos < 0)
			vy *= -1;
		if (ypos + 30 >= 500)
			vy *= -1;

		if (((paddle1.getX() + 20) >= PongBall.getX()) && ((paddle1.getY() <= PongBall.getY() && (paddle1.getY() + 100) >= PongBall.getY()))) {
			vx *= -1;
		}
		if (((paddle2.getX()) <= (PongBall.getX() + 30)) && ((paddle2.getY() <= PongBall.getY() && (paddle2.getY() + 100) >= PongBall.getY()))) {
			vx *= -1;
		}

		xpos += vx;
		ypos += vy;

		PongBall.setYVel(vy);
		PongBall.setXVel(vx);
		PongBall.setY(ypos);
		PongBall.setX(xpos);
		
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			rainbow();
			paddle1.setColor(red, green, blue);
			paddle2.setColor(red, green, blue);
			PongBall.setColor(red, green, blue);
			//move player 4 pixels in a direction when key is pressed
			if (key[KEY_UP] && paddle2.getY() != 0) {
				paddle2.setY(paddle2.getY() - 5.0);
			}

			if (key[KEY_DOWN] && paddle2.getY() + 100 != 500) {
				paddle2.setY(paddle2.getY() + 5.0);
			}

			if (key[KEY_W] && paddle1.getY() != 0) {
				paddle1.setY(paddle1.getY() - 5.0);
			}

			if (key[KEY_S] && paddle1.getY() + 100 != 500) {
				paddle1.setY(paddle1.getY() + 5.0);
			}

			redraw = true;
		}

		//keyboard and screen sections//////////////////////////////////////////
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;
			case ALLEGRO_KEY_W:
				key[KEY_W] = true;
				break;

			case ALLEGRO_KEY_S:
				key[KEY_S] = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;
			case ALLEGRO_KEY_W:
				key[KEY_W] = false;
				break;

			case ALLEGRO_KEY_S:
				key[KEY_S] = false;
				break;
			case ALLEGRO_KEY_ESCAPE:
				
				break;
			}
		}
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));
			PongBall.draw();
			paddle1.draw();
			paddle2.draw();
			al_flip_display();
		}//end render
		
	}

	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
}


void rainbow() {
	switch (stage) {
	case 0: // blue up
		blue++;
		if (blue >= 255)
			stage++;
		break;
	case 1: // red down
		red--;
		if (red == 0)
			stage++;
		break;
	case 2: // green up
		green++;
		if (green >= 255)
			stage++;
		break;
	case 3: // blue down
		blue--;
		if (blue == 0)
			stage++;
		break;
	case 4: // red up
		red++;
		if (red >= 255)
			stage++;
		break; // green removal
	case 5:
		green--;
		if (green == 0)
			stage++;
		break;
	case 6: // blue and green increase
		if (blue != 255)
			blue++;
		if (green != 255)
			green++;
		if (red == 255 && blue == 255 && green == 255)
			stage++;
		break;
	case 7: // rgb decrease
		if (red != 0)
			red--;
		if (green != 0)
			green--;
		if (blue != 0)
			blue--;
		if (red <= 0 && blue <= 0 && green <= 0)
			stage++;
		break;
	case 8: // red increase to reset
		red++;
		if (red == 255)
			stage = 0;
		break;

	}
	cout << "RGB: " << red << ", " << green << ", " << blue << endl;
};