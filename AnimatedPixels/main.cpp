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

struct Colour
{
	int R;
	int G;
	int B;
};

struct Pixel
{
	int X;
	int Y;
	Colour ElementColour;
};

void DrawPixel(Pixel* pixel, int deltaX, int deltaY)
{
	pixel->X += deltaX;
	pixel->Y += deltaY;

	int x = pixel->X;
	int y = pixel->Y;
	ALLEGRO_COLOR drawcolor = al_map_rgb(pixel->ElementColour.R, pixel->ElementColour.G, pixel->ElementColour.B);
	al_put_pixel(x, y, drawcolor);
	al_put_pixel(x, y + 1, drawcolor);
	al_put_pixel(x, y + 2, drawcolor);
	al_put_pixel(x + 1, y, drawcolor);
	al_put_pixel(x + 1, y + 1, drawcolor);
	al_put_pixel(x + 1, y + 2, drawcolor);
	al_put_pixel(x + 2, y, drawcolor);
	al_put_pixel(x + 2, y + 1, drawcolor);
	al_put_pixel(x + 2, y + 2, drawcolor);
}

int main()
{
	Setup();

	Pixel pixelsToDraw[4];

	for (int index = 0; index < 4; index++)
	{
		pixelsToDraw[index].X = 400;
		pixelsToDraw[index].Y = 300;
		pixelsToDraw[index].ElementColour.R = rand() % 255;
		pixelsToDraw[index].ElementColour.G = rand() % 255;
		pixelsToDraw[index].ElementColour.B = rand() % 255;
	}

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

 		for (int index = 0; index < 4; index++)
		{
			int deltaX = (rand() % 8) - 4;
			int deltaY = (rand() % 8) - 4;

			DrawPixel(&pixelsToDraw[index], deltaX, deltaY);
		}
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