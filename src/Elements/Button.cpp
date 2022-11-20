#include "Button.hpp"

/*
 * FILE DESCRIPTION:
 * Includes definitions for the Button class's functions.
 */

Button::Button(TextureAttributes data, bool* boolP)
{
	//--- button info ---//
	buttonState = DEFAULT;

	buttonData = data;
	buttonData.center = true;

	hitbox = buttonData.dstRect;
	hitbox.x -= hitbox.w / 2;
	hitbox.y -= hitbox.h / 2;

	attachedBool = boolP;
	children.push_back(std::make_shared<Texture>(&buttonData));
}

void Button::default_update(float dt)
{
	buttonData.color = { 255, 255, 255, 255 };
}

void Button::hovered_update(float dt)
{
	buttonData.color = { 200, 200, 200, 255 };
}

void Button::down_update(float dt)
{
	buttonData.color = { 200, 200, 200, 255 };
}

void Button::handle_input(SDL_Event e)
{
	switch (e.type)
	{
	case SDL_MOUSEMOTION:
		if (e.motion.x > hitbox.x && e.motion.x < hitbox.x + hitbox.w && e.motion.y > hitbox.y && e.motion.y < hitbox.y + hitbox.h)
		{
			if (e.button.button == 0)					
				buttonState = MOUSE_HOVERED;
			else if (e.button.button == SDL_BUTTON_LEFT)	
				buttonState = MOUSE_DOWN;
		}
		else
			buttonState = DEFAULT;
		break;

	case SDL_MOUSEBUTTONDOWN:
		if (e.button.button == SDL_BUTTON_LEFT && e.motion.x > hitbox.x && e.motion.x < hitbox.x + hitbox.w && e.motion.y > hitbox.y && e.motion.y < hitbox.y + hitbox.h)
			buttonState = MOUSE_DOWN;
		break;

	case SDL_MOUSEBUTTONUP:
		if (e.button.button == SDL_BUTTON_LEFT && e.motion.x > hitbox.x && e.motion.x < hitbox.x + hitbox.w && e.motion.y > hitbox.y && e.motion.y < hitbox.y + hitbox.h)
		{
			*attachedBool = !(*attachedBool);
			buttonState = MOUSE_HOVERED;
		}
		break;
	}
}

void Button::update(float dt)
{
	switch (buttonState)
	{
	case DEFAULT:
		default_update(dt);
		break;
	case MOUSE_HOVERED:
		hovered_update(dt);
		break;
	case MOUSE_DOWN:
		down_update(dt);
		break;
	}
}

//----------------------------------------------------------------------------------------------------//

MenuButton::MenuButton(TextureAttributes menuButtonData, bool* boolP, std::string txt)
	: Button(menuButtonData, boolP)
{
	text = txt;
	textData = TextureAttributes(TEXTURE_MULTIPURPOSE_PIXEL, graphics::SRC_NULL, { buttonData.dstRect.x, buttonData.dstRect.y, 0, 0 }, 0.0, NULL, SDL_FLIP_NONE, { 233, 167, 28, 255 }, true, buttonData.scale);
	children.push_back(std::make_shared<ConstantText>(text, &textData));
}

void MenuButton::default_update(float dt)
{
	buttonData.scale += (1 - buttonData.scale) * 20 * dt;
}

void MenuButton::hovered_update(float dt)
{
	buttonData.scale += (1.1 - buttonData.scale) * 20 * dt;
}

void MenuButton::down_update(float dt)
{
	buttonData.scale += (1.025 - buttonData.scale) * 20 * dt;
}

void MenuButton::update(float dt)
{
	Button::update(dt);
	textData.scale = 1.25 * buttonData.scale;
}