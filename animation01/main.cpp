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
void LoadResources();

// Global definitions
ALLEGRO_DISPLAY* gDisplay = nullptr;
ALLEGRO_FONT* gFont = nullptr;
ALLEGRO_EVENT_QUEUE* gEventQueue = nullptr;

ALLEGRO_BITMAP* gBackground = nullptr;
ALLEGRO_BITMAP* gImageSheet = nullptr;

int main()
{
	Setup();

	LoadResources();

	if ((gImageSheet == nullptr) || (gBackground == nullptr))
	{
		printf("Failed to load image resources!\n");
	}

	int deltaX = 0;
	int incrementor = 1;
	int animFrame = 0;

	ALLEGRO_EVENT event;
	ALLEGRO_TIMEOUT timeout;

	while (true)
	{
		al_init_timeout(&timeout, 0.05);
		bool get_event = al_wait_for_event_until(gEventQueue, &event, &timeout);

		if (get_event && event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			break;
		}

		al_draw_bitmap(gBackground, 0, 0, 0);

		const int offset = 50;
		for (int index = 0; index < 10; index++)
		{
			al_draw_bitmap_region(gImageSheet, 0, 32 * animFrame, 44, 32, deltaX + 100 + offset * index, 80, 0);
			al_draw_bitmap_region(gImageSheet, 44, 32 * animFrame, 44, 32, deltaX + 100 + offset * index, 80 + 50, 0);
			al_draw_bitmap_region(gImageSheet, 44, 32 * animFrame, 44, 32, deltaX + 100 + offset * index, 80 + (50 * 2), 0);
			al_draw_bitmap_region(gImageSheet, 44, 32 * animFrame, 44, 32, deltaX + 100 + offset * index, 80 + (50 * 3), 0);
			al_draw_bitmap_region(gImageSheet, 88, 32 * animFrame, 44, 32, deltaX + 100 + offset * index, 80 + (50 * 4), 0);
			al_draw_bitmap_region(gImageSheet, 88, 32 * animFrame, 44, 32, deltaX + 100 + offset * index, 80 + (50 * 5), 0);
		}

		deltaX += incrementor;

		if (deltaX < -100)
		{
			incrementor = 1;
		}
		if (deltaX > 200)
		{
			incrementor = -1;
		}

		if (deltaX % 5 == 0)
		{
			animFrame = (int)!(bool)animFrame;
		}

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

	al_clear_to_color(al_map_rgb(150, 150, 150));

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

void LoadResources()
{
	gImageSheet = al_load_bitmap("..\\resources\\imagesheet01.png");
	gBackground = al_load_bitmap("..\\resources\\background.png");
}