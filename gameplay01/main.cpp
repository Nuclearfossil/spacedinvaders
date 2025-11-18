// spacedinvaders.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

// Structs
struct Point
{
	float X;
	float Y;
};

struct Box
{
	Point Start;
	float Width;
	float Height;
};

struct GameObject
{
	bool Visible;
	Point WorldPosition;
	Box Sprite;
};

// Forward Declarations
void Setup();
void Teardown();
void LoadResources();
void InitializeLevel();
void Render(int animFrame);
void UpdateInvaders(int deltaX);
void UpdateLogic(double deltaTime);
void ProcessInput(ALLEGRO_EVENT ev);
bool ShotCollide(GameObject gameObject);

// Constants
const int		kMaxInvaders = 60;
const float		kCellX = 44.0f;
const float		kCellY = 32.0f;
const double	kImmediate = 0.0;
const float		kLateralMovement = 150.0f;
const float		kPlayerShotSpeed = 450.0f;

// Global definitions
ALLEGRO_DISPLAY*		gDisplay = nullptr;
ALLEGRO_FONT*			gFont = nullptr;
ALLEGRO_EVENT_QUEUE*	gEventQueue = nullptr;

ALLEGRO_BITMAP*			gBackground = nullptr;
ALLEGRO_BITMAP*			gImageSheet = nullptr;

GameObject				gInvaders[kMaxInvaders];

GameObject				gGun;
GameObject				gShot;

// Enumerations
enum InputKeys
{
	Left = 0,
	Right = 1,
	Spacebar = 2,
	Size = 3
};

bool gMovementKey[3];

int main()
{
	Setup();

	al_install_keyboard();
	al_register_event_source(gEventQueue, al_get_keyboard_event_source());

	LoadResources();

	InitializeLevel();

	double currentTime = al_get_time();
	double lastSpriteAnimTime = currentTime;
	double lastMoveTime = currentTime;
	double lastTime = currentTime;

	int deltaX = 0;
	int incrementor = 1;
	int animFrame = 0;

	while (true)
	{
		ALLEGRO_EVENT event;
		ALLEGRO_TIMEOUT timeout;
		al_init_timeout(&timeout, kImmediate);

		bool get_event = al_wait_for_event_until(gEventQueue, &event, &timeout);

		if (get_event && event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			break;
		}

		ProcessInput(event);

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
		if ((currentTime - lastSpriteAnimTime) > 0.75)
		{
			animFrame = (int)!(bool)animFrame;
			double over = currentTime - lastSpriteAnimTime - 0.75;
			lastSpriteAnimTime = currentTime - over;
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

		UpdateInvaders(direction);

		UpdateLogic(currentTime - lastTime);
		lastTime = currentTime;
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
		gInvaders[index].Sprite.Start.X = 0;
		gInvaders[index].Sprite.Start.Y = 0;
		gInvaders[index].Sprite.Width  = kCellX;
		gInvaders[index].Sprite.Height = kCellY;
		gInvaders[index].WorldPosition.X = offsetX + 100 + borderOffset * index;
		gInvaders[index].WorldPosition.Y = 80 + 50;

		gInvaders[index + 10].Visible = true;
		gInvaders[index + 10].Sprite.Start.X = 0;
		gInvaders[index + 10].Sprite.Start.Y = 0;
		gInvaders[index + 10].Sprite.Width = kCellX;
		gInvaders[index + 10].Sprite.Height = kCellY;
		gInvaders[index + 10].WorldPosition.X = offsetX + 100 + borderOffset * index;
		gInvaders[index + 10].WorldPosition.Y = 80 + (50 * 2);

		gInvaders[index + 20].Visible = true;
		gInvaders[index + 20].Sprite.Start.X = kCellX * 2;
		gInvaders[index + 20].Sprite.Start.Y = 0;
		gInvaders[index + 20].Sprite.Width = kCellX;
		gInvaders[index + 20].Sprite.Height = kCellY;
		gInvaders[index + 20].WorldPosition.X = offsetX + 100 + borderOffset * index;
		gInvaders[index + 20].WorldPosition.Y = 80 + (50 * 3);

		gInvaders[index + 30].Visible = true;
		gInvaders[index + 30].Sprite.Start.X = kCellX * 2;
		gInvaders[index + 30].Sprite.Start.Y = 0;
		gInvaders[index + 30].Sprite.Width = kCellX;
		gInvaders[index + 30].Sprite.Height = kCellY;
		gInvaders[index + 30].WorldPosition.X = offsetX + 100 + borderOffset * index;
		gInvaders[index + 30].WorldPosition.Y = 80 + (50 * 4);

		gInvaders[index + 40].Visible = true;
		gInvaders[index + 40].Sprite.Start.X = kCellX * 4;
		gInvaders[index + 40].Sprite.Start.Y = 0;
		gInvaders[index + 40].Sprite.Width = kCellX;
		gInvaders[index + 40].Sprite.Height = kCellY;
		gInvaders[index + 40].WorldPosition.X = offsetX + 100 + borderOffset * index;
		gInvaders[index + 40].WorldPosition.Y = 80 + (50 * 5);

		gInvaders[index + 50].Visible = true;
		gInvaders[index + 50].Sprite.Start.X = kCellX * 4;
		gInvaders[index + 50].Sprite.Start.Y = 0;
		gInvaders[index + 50].Sprite.Width = kCellX;
		gInvaders[index + 50].Sprite.Height = kCellY;
		gInvaders[index + 50].WorldPosition.X = offsetX + 100 + borderOffset * index;
		gInvaders[index + 50].WorldPosition.Y = 80 + (50 * 6);
	}

	gGun.Sprite.Start.X = 444;
	gGun.Sprite.Start.Y = 0;
	gGun.Sprite.Width = kCellX;
	gGun.Sprite.Height = kCellY;
	gGun.WorldPosition.X = 10;
	gGun.WorldPosition.Y = 550;

	// Shot has a different width and height than everyone else
	gShot.Sprite.Start.X = 639;
	gShot.Sprite.Start.Y = 9;
	gShot.Sprite.Width = 4;
	gShot.Sprite.Height = 11;
	gShot.WorldPosition.X = 0;
	gShot.WorldPosition.Y = 0;
}

void Render(int animFrame)
{
	// Draw our invaders
	for (int index = 0; index < 10; index++)
	{
		if (gInvaders[index].Visible)
		{
			al_draw_bitmap_region(gImageSheet,
				gInvaders[index].Sprite.Start.X + animFrame * gInvaders[index].Sprite.Width,
				gInvaders[index].Sprite.Start.Y,
				gInvaders[index].Sprite.Width,
				gInvaders[index].Sprite.Height,
				gInvaders[index].WorldPosition.X,
				gInvaders[index].WorldPosition.Y,
				0);
		}

		if (gInvaders[index + 10].Visible)
		{
			al_draw_bitmap_region(gImageSheet,
				gInvaders[index + 10].Sprite.Start.X + animFrame * gInvaders[index].Sprite.Width,
				gInvaders[index + 10].Sprite.Start.Y,
				gInvaders[index + 10].Sprite.Width,
				gInvaders[index + 10].Sprite.Height,
				gInvaders[index + 10].WorldPosition.X,
				gInvaders[index + 10].WorldPosition.Y,
				0);
		}

		if (gInvaders[index + 20].Visible)
		{
			al_draw_bitmap_region(gImageSheet,
				gInvaders[index + 20].Sprite.Start.X + animFrame * gInvaders[index].Sprite.Width,
				gInvaders[index + 20].Sprite.Start.Y,
				gInvaders[index + 20].Sprite.Width,
				gInvaders[index + 20].Sprite.Height,
				gInvaders[index + 20].WorldPosition.X,
				gInvaders[index + 20].WorldPosition.Y,
				0);
		}

		if (gInvaders[index + 30].Visible)
		{
			al_draw_bitmap_region(gImageSheet,
				gInvaders[index + 30].Sprite.Start.X + animFrame * gInvaders[index].Sprite.Width,
				gInvaders[index + 30].Sprite.Start.Y,
				gInvaders[index + 30].Sprite.Width,
				gInvaders[index + 30].Sprite.Height,
				gInvaders[index + 30].WorldPosition.X,
				gInvaders[index + 30].WorldPosition.Y,
				0);
		}

		if (gInvaders[index + 40].Visible)
		{
			al_draw_bitmap_region(gImageSheet,
				gInvaders[index + 40].Sprite.Start.X + animFrame * gInvaders[index].Sprite.Width,
				gInvaders[index + 40].Sprite.Start.Y,
				gInvaders[index + 40].Sprite.Width,
				gInvaders[index + 40].Sprite.Height,
				gInvaders[index + 40].WorldPosition.X,
				gInvaders[index + 40].WorldPosition.Y,
				0);
		}

		if (gInvaders[index + 50].Visible)
		{
			al_draw_bitmap_region(gImageSheet,
				gInvaders[index + 50].Sprite.Start.X + animFrame * gInvaders[index].Sprite.Width,
				gInvaders[index + 50].Sprite.Start.Y,
				gInvaders[index + 50].Sprite.Width,
				gInvaders[index + 50].Sprite.Height,
				gInvaders[index + 50].WorldPosition.X,
				gInvaders[index + 50].WorldPosition.Y,
				0);
		}
	}

	if (gShot.Visible)
	{
		al_draw_bitmap_region(gImageSheet,
			gShot.Sprite.Start.X, gShot.Sprite.Start.Y,
			gShot.Sprite.Width, gShot.Sprite.Height,
			gShot.WorldPosition.X, gShot.WorldPosition.Y,
			0);
	}

	// Draw our gunship
	al_draw_bitmap_region(gImageSheet,
		gGun.Sprite.Start.X, gGun.Sprite.Start.Y,
		gGun.Sprite.Width, gGun.Sprite.Height,
		gGun.WorldPosition.X, gGun.WorldPosition.Y,
		0);
}

void UpdateInvaders(int deltaX)
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

void ProcessInput(ALLEGRO_EVENT ev)
{
	if (ev.type != ALLEGRO_EVENT_KEY_DOWN && ev.type != ALLEGRO_EVENT_KEY_UP) return;

	if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		switch (ev.keyboard.keycode)
		{
			case ALLEGRO_KEY_LEFT:
				gMovementKey[Left] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				gMovementKey[Right] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				gMovementKey[Spacebar] = true;
				break;
			default:
				break;
		}
	}
	else if (ev.type == ALLEGRO_EVENT_KEY_UP)
	{
		switch (ev.keyboard.keycode)
		{
			case ALLEGRO_KEY_LEFT:
				gMovementKey[Left] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				gMovementKey[Right] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				gMovementKey[Spacebar] = false;
				break;
			default:
				break;
		}
	}
}

void UpdateLogic(double deltaTime)
{
	if (gMovementKey[Spacebar] && !gShot.Visible)
	{
		gShot.WorldPosition.X = gGun.WorldPosition.X + gGun.Sprite.Width/2.0f - 3.0f;
		gShot.WorldPosition.Y = gGun.WorldPosition.Y;
		gShot.Visible = true;
	}

	if (gShot.Visible)
	{
		gShot.WorldPosition.Y = gShot.WorldPosition.Y - (kPlayerShotSpeed * deltaTime);

		if (gShot.WorldPosition.Y < 0)
		{
			gShot.Visible = false;
		}
	}

	if (gMovementKey[Left])
	{
		gGun.WorldPosition.X = gGun.WorldPosition.X - (kLateralMovement * deltaTime);
	}

	if (gMovementKey[Right])
	{
		gGun.WorldPosition.X = gGun.WorldPosition.X + (kLateralMovement * deltaTime);
	}

	gGun.WorldPosition.X = gGun.WorldPosition.X > (790.0f-kCellX) ? (790.0f - kCellX) : gGun.WorldPosition.X;
	gGun.WorldPosition.X = gGun.WorldPosition.X < 10.0f ? 10.0f : gGun.WorldPosition.X;

	// Now check for collision of the player's shot

	if (gShot.Visible)
	{
		for (size_t index = 0; index < kMaxInvaders; index++)
		{
			if (gInvaders[index].Visible && ShotCollide(gInvaders[index]))
			{
				gInvaders[index].Visible = false;
				gShot.Visible = false;
				break;
			}
		}
	}
}

bool ShotCollide(GameObject gameObject)
{
	float axmin = gameObject.WorldPosition.X;
	float axmax = axmin + gameObject.Sprite.Width;
	float aymin = gameObject.WorldPosition.Y;
	float aymax = aymin + gameObject.Sprite.Height;

	float bxmin = gShot.WorldPosition.X;
	float bxmax = bxmin + gShot.Sprite.Width;
	float bymin = gShot.WorldPosition.Y;
	float bymax = bymin + gShot.Sprite.Height;

	if (axmax < bxmin || axmin > bxmax) return false;
	if (aymax < bymin || aymin > bymax) return false;

	return true;
}
