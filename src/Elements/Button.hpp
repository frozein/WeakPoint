#pragma once
#include "Elements/Element.hpp"

#include "Elements/Text.hpp"
#include "Elements/Texture.hpp"

/*
 * FILE DESCRIPTION:
 * Includes declarations for the Button class and its functions.
 */

enum ClickState : unsigned char {
	DEFAULT,
	MOUSE_HOVERED,
	MOUSE_DOWN
};

class Button : public Element {

public:
	//--- button info ---//
	ClickState buttonState;
	TextureAttributes buttonData;
	SDL_Rect hitbox;
	bool* attachedBool;

	Button() = default;
	Button(TextureAttributes data, bool* boolP);

	virtual void default_update(float dt);
	virtual void hovered_update(float dt);
	virtual void down_update(float dt);

	virtual void handle_input(SDL_Event e);
	virtual void update(float dt);
};

//----------------------------------------------------------------------------------------------------//

class MenuButton : public Button {

public:
	//--- text info ---//
	std::string text;
	TextureAttributes textData;

	MenuButton(TextureAttributes menuButtonData, bool* boolP, std::string txt);

	void default_update(float dt);
	void hovered_update(float dt);
	void down_update(float dt);

	virtual void update(float dt);
};