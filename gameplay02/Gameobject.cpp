#include "stdafx.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "Gameobject.h"


GameObject::GameObject()
{
	mVisible = true;
	mWorldPosition.X = 0.0f;
	mWorldPosition.Y = 0.0f;
	mSprite.Start.X = 0.0f;
	mSprite.Start.Y = 0.0f;
	mSprite.Width = 10.0f;
	mSprite.Height = 10.0f;
	mAnimFrame = 0;
	gImageSheet = nullptr;
}

GameObject::GameObject(float originX, float originY, float spriteX, float spriteY, float width, float height, bool visible, ALLEGRO_BITMAP* source)
{
	Init(originX, originY, spriteX, spriteY, width, height, visible, source);
}

void GameObject::Init(float originX, float originY, float spriteX, float spriteY, float width, float height, bool visible, ALLEGRO_BITMAP* source)
{
	mVisible = visible;
	mWorldPosition.X = originX;
	mWorldPosition.Y = originY;
	mSprite.Start.X = spriteX;
	mSprite.Start.Y = spriteY;
	mSprite.Width = width;
	mSprite.Height = height;
	mAnimFrame = 0;
	gImageSheet = source;
}

void GameObject::Render()
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

void GameObject::Update(float delta)
{

}

bool GameObject::CollidesWith(GameObject* other)
{
	if (other == nullptr) return false;

	float axmin = other->mWorldPosition.X;
	float axmax = axmin + other->mSprite.Width;
	float aymin = other->mWorldPosition.Y;
	float aymax = aymin + other->mSprite.Height;

	float bxmin = mWorldPosition.X;
	float bxmax = bxmin + mSprite.Width;
	float bymin = mWorldPosition.Y;
	float bymax = bymin + mSprite.Height;

	if (axmax < bxmin || axmin > bxmax) return false;
	if (aymax < bymin || aymin > bymax) return false;

	return true;
}
