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

	ALLEGRO_BITMAP*	mSpriteSheet = al_load_bitmap("..\\resources\\animsheet.png");
	int animFrame = 0;

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

		al_clear_to_color(al_map_rgb(0, 0, 0));

		al_draw_bitmap_region(mSpriteSheet, 95 * animFrame, 0, 95, 158, 100, 80, 0);

		animFrame = animFrame++;
		animFrame = animFrame % 12;

		al_flip_display();
	}

	Teardown();

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