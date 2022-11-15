#include "Text.hpp"

/*
 * FILE DESCRIPTION:
 * Includes definitions for the methods in the ConstantText and VariableText classes.
 */

//------------------------------------------------------------------------------------------------//
//CONSTANT TEXT METHOD DEFINITIONS:

ConstantText::ConstantText(std::string _text, TextureAttributes* _attrPtr)  {
    text = _text;
    attrPtr = _attrPtr;
    attrPtr->texture = graphics::create_string_texture(text, FONT_GAME, &attrPtr->dstRect.w, &attrPtr->dstRect.h);
}

ConstantText::~ConstantText() {
    graphics::destroy_string_texture(attrPtr->texture);
}

void ConstantText::render() {
    graphics::render_texture(*attrPtr);
}

//------------------------------------------------------------------------------------------------//
//VARIABLE TEXT METHOD DEFINITIONS:

VariableText::VariableText(std::string* _textPtr, TextureAttributes* _attrPtr) {
    textPtr = _textPtr;
    attrPtr = _attrPtr;
    attrPtr->texture = graphics::create_string_texture(*textPtr, FONT_GAME, &attrPtr->dstRect.w, &attrPtr->dstRect.h);
}

VariableText::~VariableText() {
    graphics::destroy_string_texture(attrPtr->texture);
}

void VariableText::update(float dt) {
    graphics::destroy_string_texture(attrPtr->texture);
    attrPtr->texture = graphics::create_string_texture(*textPtr, FONT_GAME, &attrPtr->dstRect.w, &attrPtr->dstRect.h); 
}

void VariableText::render() {
    graphics::render_texture(*attrPtr);
}