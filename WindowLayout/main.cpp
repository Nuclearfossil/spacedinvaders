// spacedinvaders.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

// Forward Declarations
void Setup();
void Teardown();

// Global definitions
ALLEGRO_DISPLAY* gDisplay = nullptr;
ALLEGRO_FONT* gFont = nullptr;
ALLEGRO_EVENT_QUEUE* gEventQueue = nullptr;

int main()
{
	Setup();

	while (true)
	{
		ALLEGRO_EVENT event;
		ALLEGRO_TIMEOUT timeout;
		al_init_timeout(&timeout, 0.06);

		bool get_event = al_wait_for_event_until(gEventQueue, &event, &timeout);

		if (get_event && event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			break;
		}

		al_put_pixel(0, 0, al_map_rgb(255, 255, 255));
		al_put_pixel(0, 1, al_map_rgb(255, 255, 255));
		al_put_pixel(0, 2, al_map_rgb(255, 255, 255));
		al_put_pixel(1, 0, al_map_rgb(255, 255, 255));
		al_put_pixel(1, 1, al_map_rgb(255, 255, 255));
		al_put_pixel(1, 2, al_map_rgb(255, 255, 255));
		al_put_pixel(2, 0, al_map_rgb(255, 255, 255));
		al_put_pixel(2, 1, al_map_rgb(255, 255, 255));
		al_put_pixel(2, 2, al_map_rgb(255, 255, 255));

		al_put_pixel(797, 0, al_map_rgb(0, 255, 0));
		al_put_pixel(797, 1, al_map_rgb(0, 255, 0));
		al_put_pixel(797, 2, al_map_rgb(0, 255, 0));
		al_put_pixel(798, 0, al_map_rgb(0, 255, 0));
		al_put_pixel(798, 1, al_map_rgb(0, 255, 0));
		al_put_pixel(798, 2, al_map_rgb(0, 255, 0));
		al_put_pixel(799, 0, al_map_rgb(0, 255, 0));
		al_put_pixel(799, 1, al_map_rgb(0, 255, 0));
		al_put_pixel(799, 2, al_map_rgb(0, 255, 0));

		al_put_pixel(0, 597, al_map_rgb(255, 0, 0));
		al_put_pixel(0, 598, al_map_rgb(255, 0, 0));
		al_put_pixel(0, 599, al_map_rgb(255, 0, 0));
		al_put_pixel(1, 597, al_map_rgb(255, 0, 0));
		al_put_pixel(1, 598, al_map_rgb(255, 0, 0));
		al_put_pixel(1, 599, al_map_rgb(255, 0, 0));
		al_put_pixel(2, 597, al_map_rgb(255, 0, 0));
		al_put_pixel(2, 598, al_map_rgb(255, 0, 0));
		al_put_pixel(2, 599, al_map_rgb(255, 0, 0));

		al_put_pixel(797, 597, al_map_rgb(255, 255, 0));
		al_put_pixel(797, 598, al_map_rgb(255, 255, 0));
		al_put_pixel(797, 599, al_map_rgb(255, 255, 0));
		al_put_pixel(798, 597, al_map_rgb(255, 255, 0));
		al_put_pixel(798, 598, al_map_rgb(255, 255, 0));
		al_put_pixel(798, 599, al_map_rgb(255, 255, 0));
		al_put_pixel(799, 597, al_map_rgb(255, 255, 0));
		al_put_pixel(799, 598, al_map_rgb(255, 255, 0));
		al_put_pixel(799, 599, al_map_rgb(255, 255, 0));

		al_flip_display();
	}

	return 0;
}

void Setup()
{
	al_init();
	al_init_font_addon();
	al_init_image_addon();
	al_init_primitives_addon();

	gDisplay = al_create_display(800, 600);
	gFont = al_create_builtin_font();
	gEventQueue = nullptr;

	gEventQueue = al_create_event_queue();
	al_register_event_source(gEventQueue, al_get_display_event_source(gDisplay));

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_draw_text(gFont,
		al_map_rgb(255, 255, 255),
		400, 300,
		ALLEGRO_ALIGN_CENTER,
		"SPAAAAACED INVADERS!");
}

void Teardown()
{
	al_destroy_font(gFont);
	al_destroy_display(gDisplay);
}