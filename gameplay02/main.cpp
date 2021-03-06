// spacedinvaders.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

#include "Gameobject.h"

// Forward Declarations
void Setup();
void Teardown();
void LoadResources();
void InitializeLevel();
void UpdateInvaders(float deltaX, int animFrame);
void UpdateLogic(double deltaTime);
void Render(int animFrame);
void ProcessInput(ALLEGRO_EVENT ev);

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

		UpdateInvaders(direction, animFrame);

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
		gInvaders[index].Init(offsetX + 100 + borderOffset * index, 80 + 50, 0, 0, kCellX, kCellY, true, gImageSheet);
		gInvaders[index + 10].Init(offsetX + 100 + borderOffset * index, 80 + (50 * 2), 0, 0, kCellX, kCellY, true, gImageSheet);
		gInvaders[index + 20].Init(offsetX + 100 + borderOffset * index, 80 + (50 * 3), kCellX * 2, 0, kCellX, kCellY, true, gImageSheet);
		gInvaders[index + 30].Init(offsetX + 100 + borderOffset * index, 80 + (50 * 4), kCellX * 2, 0, kCellX, kCellY, true, gImageSheet);
		gInvaders[index + 40].Init(offsetX + 100 + borderOffset * index, 80 + (50 * 5), kCellX * 4, 0, kCellX, kCellY, true, gImageSheet);
		gInvaders[index + 50].Init(offsetX + 100 + borderOffset * index, 80 + (50 * 6), kCellX * 4, 0, kCellX, kCellY, true, gImageSheet);
	}

	// initialize the gun
	gGun.Init(10, 550, 444, 0, kCellX, kCellY, true, gImageSheet);

	// Shot has a different width and height than everyone else
	gShot.Init(0, 0, 639, 9, 4, 11, true, gImageSheet);
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

void Render(int animFrame)
{
	// Draw our invaders
	for (int index = 0; index < 10; index++)
	{
		gInvaders[index].Render();
		gInvaders[index + 10].Render();
		gInvaders[index + 20].Render(); 
		gInvaders[index + 30].Render();
		gInvaders[index + 40].Render();
		gInvaders[index + 50].Render();
	}

	// render the shot
	gShot.Render();

	// Draw our gunship
	gGun.Render();
}

void UpdateInvaders(float deltaX, int animFrame)
{
	for (int index = 0; index < 10; index++)
	{
		gInvaders[index].Update(deltaX, animFrame);
		gInvaders[index + 10].Update(deltaX, animFrame);
		gInvaders[index + 20].Update(deltaX, animFrame);
		gInvaders[index + 30].Update(deltaX, animFrame);
		gInvaders[index + 40].Update(deltaX, animFrame);
		gInvaders[index + 50].Update(deltaX, animFrame);
	}
}

void UpdateLogic(double deltaTime)
{
	if (gMovementKey[Spacebar] && !gShot.IsVisible())
	{
		gShot.mWorldPosition.X = gGun.mWorldPosition.X + gGun.SpriteWidth() / 2.0f - 3.0f;
		gShot.mWorldPosition.Y = gGun.mWorldPosition.Y;
		gShot.SetVisible(true);
	}

	if (gShot.IsVisible())
	{
		gShot.mWorldPosition.Y = gShot.mWorldPosition.Y - (kPlayerShotSpeed * deltaTime);

		if (gShot.mWorldPosition.Y < 0)
		{
			gShot.SetVisible(false);
		}
	}

	if (gMovementKey[Left])
	{
		gGun.mWorldPosition.X = gGun.mWorldPosition.X - (kLateralMovement * deltaTime);
	}

	if (gMovementKey[Right])
	{
		gGun.mWorldPosition.X = gGun.mWorldPosition.X + (kLateralMovement * deltaTime);
	}

	gGun.mWorldPosition.X = gGun.mWorldPosition.X > (790.0f - kCellX) ? (790.0f - kCellX) : gGun.mWorldPosition.X;
	gGun.mWorldPosition.X = gGun.mWorldPosition.X < 10.0f ? 10.0f : gGun.mWorldPosition.X;

	// Now check for collision of the player's shot
	if (gShot.IsVisible())
	{
		for (size_t index = 0; index < kMaxInvaders; index++)
		{
			if (gInvaders[index].IsVisible() && gShot.CollidesWith(&gInvaders[index]))
			{
				gInvaders[index].SetVisible(false);
				gShot.SetVisible(false);
				break;
			}
		}
	}
}
