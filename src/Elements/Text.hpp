#pragma once
#include "Element.hpp"

/*
 * FILE DESCRIPTION:
 * Includes declarations for the ConstantText and VariableText class and its methods.
 */

class ConstantText : public Element {

private:
    std::string text;
    TextureAttributes* attrPtr;

public:
    ConstantText(std::string _text, TextureAttributes* _attrPtr);
    ~ConstantText();

    void render();

};

class VariableText : public Element {

private:
    std::string* textPtr;
    TextureAttributes* attrPtr;

public:
    VariableText(std::string* _textPtr, TextureAttributes* _attrPtr);
    ~VariableText();

    void update(float dt);
    void render();

};