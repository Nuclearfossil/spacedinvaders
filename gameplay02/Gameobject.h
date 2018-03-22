#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "Utils.h"

class GameObject
{
private:
	bool mVisible;
	Box mSprite;
	int mAnimFrame;
	ALLEGRO_BITMAP*	gImageSheet;

public:
	Point mWorldPosition;

public:
	GameObject();
	GameObject(float originX, float originY, float spriteX, float spriteY, float width, float height, bool visible, ALLEGRO_BITMAP* source);

	int SpriteWidth() { return mSprite.Width; }
	int SpriteHeight() { return mSprite.Height; }

	bool IsVisible() { return mVisible; }
	void SetVisible(bool value) { mVisible = value; }

	void Init(float originX, float originY, float spriteX, float spriteY, float width, float height, bool visible, ALLEGRO_BITMAP* source);

	void Render();

	void Update(float delta, int animFrame);

	bool CollidesWith(GameObject* other);
};

