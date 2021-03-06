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

const int kCellX = 44;
const int kCellY = 32;

const double kImmediate = 0.0;

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

	double currentTime = al_get_time();
	double lastTime = currentTime;
	double lastMoveTime = currentTime;

	while (true)
	{
		al_init_timeout(&timeout, kImmediate);
		bool get_event = al_wait_for_event_until(gEventQueue, &event, &timeout);

		if (get_event && event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			break;
		}

		al_draw_bitmap(gBackground, 0, 0, 0);

		const int borderOffset = 50;
		for (int index = 0; index < 10; index++)
		{
			al_draw_bitmap_region(gImageSheet, kCellX * animFrame, 0, kCellX, kCellY, deltaX + 100 + borderOffset * index, 80, 0);
			al_draw_bitmap_region(gImageSheet, (kCellX * (2 + animFrame)), 0, kCellX, kCellY, deltaX + 100 + borderOffset * index, 80 + 50, 0);
			al_draw_bitmap_region(gImageSheet, (kCellX * (2 + animFrame)), 0, kCellX, kCellY, deltaX + 100 + borderOffset * index, 80 + (50 * 2), 0);
			al_draw_bitmap_region(gImageSheet, (kCellX * (4 + animFrame)), 0, kCellX, kCellY, deltaX + 100 + borderOffset * index, 80 + (50 * 3), 0);
			al_draw_bitmap_region(gImageSheet, (kCellX * (4 + animFrame)), 0, kCellX, kCellY, deltaX + 100 + borderOffset * index, 80 + (50 * 4), 0);
			al_draw_bitmap_region(gImageSheet, (kCellX * (4 + animFrame)), 0, kCellX, kCellY, deltaX + 100 + borderOffset * index, 80 + (50 * 5), 0);
		}

		currentTime = al_get_time();

		// Move our characters
		if ((currentTime - lastMoveTime) > 0.1)
		{
			deltaX += incrementor;

			if (deltaX < -100)
			{
				incrementor = 1;
			}
			if (deltaX > 200)
			{
				incrementor = -1;
			}

			double over = currentTime - lastMoveTime - 0.1;
			lastMoveTime = currentTime - over;
		}

		// Animate our sprites
		if ((currentTime - lastTime) > 0.75)
		{
			animFrame = (int)!(bool)animFrame;
			double over = currentTime - lastTime - 0.75;
			lastTime = currentTime - over;
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
	gImageSheet = al_load_bitmap("..\\resources\\spacedspritesheet.png");
	gBackground = al_load_bitmap("..\\resources\\background.png");
}