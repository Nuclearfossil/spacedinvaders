// spacedinvaders.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

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

class GameObject
{
private:
	bool mVisible;
	Point mWorldPosition;
	Box mSprite;
	int mAnimFrame;

public:
	GameObject()
	{
		mVisible = true;
		mWorldPosition.X = 0.0f;
		mWorldPosition.Y = 0.0f;
		mSprite.Start.X = 0.0f;
		mSprite.Start.Y = 0.0f;
		mSprite.Width = 10.0f;
		mSprite.Height = 10.0f;
		mAnimFrame = 0;
	}

	GameObject(float originX, float originY, float spriteX, float spriteY, float width, float height, bool visible)
	{
		Init(originX, originY, spriteX, spriteY, width, height, visible);
	}

	void Init(float originX, float originY, float spriteX, float spriteY, float width, float height, bool visible)
	{
		mVisible = visible;
		mWorldPosition.X = originX;
		mWorldPosition.Y = originY;
		mSprite.Start.X = spriteX;
		mSprite.Start.Y = spriteY;
		mSprite.Width = width;
		mSprite.Height = height;
		mAnimFrame = 0;
	}

	void Render()
	{
		if (mVisible)
		{
			al_draw_bitmap_region(gImageSheet,
				mSprite.Start.X + mAnimFrame * mSprite.Width,
				mSprite.Start.Y,
				mSprite.Width,
				mSprite.Height,
				mWorldPosition.X,
				mWorldPosition.Y,
				0);
		}
	}

	void Update(float delta)
	{

	}

	bool CollidesWith(GameObject* other)
	{
		return false;
	}

	bool Collide(GameObject gameObject)
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
};

// Forward Declarations
void Setup();
void Teardown();
void LoadResources();

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

int main()
{
	Setup();
	al_install_keyboard();
	al_register_event_source(gEventQueue, al_get_keyboard_event_source());

	LoadResources();

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

		for (int index = 0; index < 25; index++)
		{
			al_put_pixel(rand() % 800, rand() % 600, al_map_rgb(rand() % 255, rand() % 255, rand() % 255));
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
		gInvaders[index].Init(offsetX + 100 + borderOffset * index, 80 + 50, 0, 0, kCellX, kCellY, true);
		gInvaders[index + 10].Init(offsetX + 100 + borderOffset * index, 80 + (50 * 2), 0, 0, kCellX, kCellY, true);
		gInvaders[index + 20].Init(offsetX + 100 + borderOffset * index, 80 + (50 * 3), kCellX * 2, 0, kCellX, kCellY, true);
		gInvaders[index + 30].Init(offsetX + 100 + borderOffset * index, 80 + (50 * 4), kCellX * 2, 0, kCellX, kCellY, true);
		gInvaders[index + 40].Init(offsetX + 100 + borderOffset * index, 80 + (50 * 5), kCellX * 4, 0, kCellX, kCellY, true);
		gInvaders[index + 50].Init(offsetX + 100 + borderOffset * index, 80 + (50 * 6), kCellX * 4, 0, kCellX, kCellY, true);
	}

	// initialize the gun
	gGun.Init(10, 550, 444, 0, kCellX, kCellY, true);

	// Shot has a different width and height than everyone else
	gShot.Init(0, 0, 639, 9, 4, 11, true);
}
