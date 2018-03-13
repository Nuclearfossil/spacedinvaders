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
void InitializeLevel();
void Render(int animFrame);
void Update(int deltaX);

// Constants
const int kCellX = 44;
const int kCellY = 32;

const double kImmediate = 0.0;

// Structs
struct Point
{
	int X;
	int Y;
};

struct Invader
{
	Point WorldPosition;

	Point SpriteOrigin;
	Point Size;

	bool Visible;
};

// Global definitions
ALLEGRO_DISPLAY* gDisplay = nullptr;
ALLEGRO_FONT* gFont = nullptr;
ALLEGRO_EVENT_QUEUE* gEventQueue = nullptr;

ALLEGRO_BITMAP* gBackground = nullptr;
ALLEGRO_BITMAP* gImageSheet = nullptr;

Invader gInvaders[60];

int main()
{
	Setup();

	LoadResources();

	InitializeLevel();
	InitializeLevel();

	double currentTime = al_get_time();
	double lastTime = currentTime;
	double lastMoveTime = currentTime;

	int deltaX = 0;
	int incrementor = 1;
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

		// Render off the background
		al_draw_bitmap(gBackground, 0, 0, 0);

		Render(animFrame);

		// Debug ==========================================
		char buffer[15];
		sprintf_s(buffer, "deltaX: %d", deltaX);

		al_draw_text(gFont,
			al_map_rgb(255, 255, 255),
			700, 550,
			ALLEGRO_ALIGN_CENTER,
			buffer);
		// ================================================

		al_flip_display();

		currentTime = al_get_time();

		// Animate our sprites
		if ((currentTime - lastTime) > 0.75)
		{
			animFrame = (int)!(bool)animFrame;
			double over = currentTime - lastTime - 0.75;
			lastTime = currentTime - over;
		}

		// Move our characters
		int direction = 0;
		if ((currentTime - lastMoveTime) > 0.1)
		{
			deltaX += incrementor;

			if (deltaX < -150)
			{
				incrementor = 1;
			}
			if (deltaX > 150)
			{
				incrementor = -1;
			}

			double over = currentTime - lastMoveTime - 0.1;
			lastMoveTime = currentTime - over;
			direction = incrementor;
		}

		Update(direction);
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

void LoadResources()
{
	gImageSheet = al_load_bitmap("..\\resources\\spacedspritesheet.png");
	gBackground = al_load_bitmap("..\\resources\\background.png");
}

void InitializeLevel()
{
	// set up our references for each row
	int borderOffset = 50;
	int offsetX = 50;

	for (int index = 0; index < 10; index++)
	{
		gInvaders[index].Visible = true;
		gInvaders[index].SpriteOrigin.X = 0;
		gInvaders[index].SpriteOrigin.Y = 0;
		gInvaders[index].Size.X = kCellX;
		gInvaders[index].Size.Y = kCellY;
		gInvaders[index].WorldPosition.X = offsetX + 100 + borderOffset * index;
		gInvaders[index].WorldPosition.Y = 80 + 50;

		gInvaders[index + 10].Visible = true;
		gInvaders[index + 10].SpriteOrigin.X = 0;
		gInvaders[index + 10].SpriteOrigin.Y = 0;
		gInvaders[index + 10].Size.X = kCellX;
		gInvaders[index + 10].Size.Y = kCellY;
		gInvaders[index + 10].WorldPosition.X = offsetX + 100 + borderOffset * index;
		gInvaders[index + 10].WorldPosition.Y = 80 + (50 * 2);

		gInvaders[index + 20].Visible = true;
		gInvaders[index + 20].SpriteOrigin.X = kCellX * 2;
		gInvaders[index + 20].SpriteOrigin.Y = 0;
		gInvaders[index + 20].Size.X = kCellX;
		gInvaders[index + 20].Size.Y = kCellY;
		gInvaders[index + 20].WorldPosition.X = offsetX + 100 + borderOffset * index;
		gInvaders[index + 20].WorldPosition.Y = 80 + (50 * 3);

		gInvaders[index + 30].Visible = true;
		gInvaders[index + 30].SpriteOrigin.X = kCellX * 2;
		gInvaders[index + 30].SpriteOrigin.Y = 0;
		gInvaders[index + 30].Size.X = kCellX;
		gInvaders[index + 30].Size.Y = kCellY;
		gInvaders[index + 30].WorldPosition.X = offsetX + 100 + borderOffset * index;
		gInvaders[index + 30].WorldPosition.Y = 80 + (50 * 4);

		gInvaders[index + 40].Visible = true;
		gInvaders[index + 40].SpriteOrigin.X = kCellX * 4;
		gInvaders[index + 40].SpriteOrigin.Y = 0;
		gInvaders[index + 40].Size.X = kCellX;
		gInvaders[index + 40].Size.Y = kCellY;
		gInvaders[index + 40].WorldPosition.X = offsetX + 100 + borderOffset * index;
		gInvaders[index + 40].WorldPosition.Y = 80 + (50 * 5);

		gInvaders[index + 50].Visible = true;
		gInvaders[index + 50].SpriteOrigin.X = kCellX * 4;
		gInvaders[index + 50].SpriteOrigin.Y = 0;
		gInvaders[index + 50].Size.X = kCellX;
		gInvaders[index + 50].Size.Y = kCellY;
		gInvaders[index + 50].WorldPosition.X = offsetX + 100 + borderOffset * index;
		gInvaders[index + 50].WorldPosition.Y = 80 + (50 * 6);
	}
}

void Render(int animFrame)
{
	for (int index = 0; index < 10; index++)
	{
		if (gInvaders[index].Visible)
		{
			al_draw_bitmap_region(gImageSheet,
				gInvaders[index].SpriteOrigin.X + animFrame * gInvaders[index].Size.X,
				gInvaders[index].SpriteOrigin.Y,
				gInvaders[index].Size.X,
				gInvaders[index].Size.Y,
				gInvaders[index].WorldPosition.X,
				gInvaders[index].WorldPosition.Y,
				0);
		}

		if (gInvaders[index].Visible)
		{
			al_draw_bitmap_region(gImageSheet,
				gInvaders[index + 10].SpriteOrigin.X + animFrame * gInvaders[index].Size.X,
				gInvaders[index + 10].SpriteOrigin.Y,
				gInvaders[index + 10].Size.X,
				gInvaders[index + 10].Size.Y,
				gInvaders[index + 10].WorldPosition.X,
				gInvaders[index + 10].WorldPosition.Y,
				0);
		}

		if (gInvaders[index + 20].Visible)
		{
			al_draw_bitmap_region(gImageSheet,
				gInvaders[index + 20].SpriteOrigin.X + animFrame * gInvaders[index].Size.X,
				gInvaders[index + 20].SpriteOrigin.Y,
				gInvaders[index + 20].Size.X,
				gInvaders[index + 20].Size.Y,
				gInvaders[index + 20].WorldPosition.X,
				gInvaders[index + 20].WorldPosition.Y,
				0);
		}

		if (gInvaders[index + 30].Visible)
		{
			al_draw_bitmap_region(gImageSheet,
				gInvaders[index + 30].SpriteOrigin.X + animFrame * gInvaders[index].Size.X,
				gInvaders[index + 30].SpriteOrigin.Y,
				gInvaders[index + 30].Size.X,
				gInvaders[index + 30].Size.Y,
				gInvaders[index + 30].WorldPosition.X,
				gInvaders[index + 30].WorldPosition.Y,
				0);
		}

		if (gInvaders[index + 40].Visible)
		{
			al_draw_bitmap_region(gImageSheet,
				gInvaders[index + 40].SpriteOrigin.X + animFrame * gInvaders[index].Size.X,
				gInvaders[index + 40].SpriteOrigin.Y,
				gInvaders[index + 40].Size.X,
				gInvaders[index + 40].Size.Y,
				gInvaders[index + 40].WorldPosition.X,
				gInvaders[index + 40].WorldPosition.Y,
				0);
		}

		if (gInvaders[index + 50].Visible)
		{
			al_draw_bitmap_region(gImageSheet,
				gInvaders[index + 50].SpriteOrigin.X + animFrame * gInvaders[index].Size.X,
				gInvaders[index + 50].SpriteOrigin.Y,
				gInvaders[index + 50].Size.X,
				gInvaders[index + 50].Size.Y,
				gInvaders[index + 50].WorldPosition.X,
				gInvaders[index + 50].WorldPosition.Y,
				0);
		}
	}
}

void Update(int deltaX)
{
	for (int index = 0; index < 10; index++)
	{
		gInvaders[index].WorldPosition.X += deltaX;
		gInvaders[index + 10].WorldPosition.X += deltaX;
		gInvaders[index + 20].WorldPosition.X += deltaX;
		gInvaders[index + 30].WorldPosition.X += deltaX;
		gInvaders[index + 40].WorldPosition.X += deltaX;
		gInvaders[index + 50].WorldPosition.X += deltaX;
	}
}