#include "textbox.h"
#include "graphics.h"

TextBox::TextBox() {}

TextBox::TextBox(Graphics &graphics) : _graphics(&graphics)
{
    this->_text = "";
    this->_showTillTime = 0;
    this->_showTextBox = false;
    this->_textFrame = Sprite(graphics, "text-frame.png", 0, 0, 736, 192, 416, 514);
    this->_portraitFrame = Sprite(graphics, "portrait-frame.png", 0, 0, 256, 256, 128, 450);
    // this->_portrait = Sprite(graphics, ".png", 600, 186, 9, 12, 134, 56);
    this->_connector = Sprite(graphics, "connector.png", 0, 0, 288, 256, 128, 450);
}

void TextBox::show(bool show)
{
    // if (this->_text == "")
    //     show = false;
    // this->_showTextBox = show;
}

TextBox &TextBox::showForTime(float time)
{
    if (this->_showTillTime <= 0)
        this->_showTillTime = time;
    return *this;
}

TextBox &TextBox::setText(string message)
{
    if (this->_text == message)
        return *this;
    this->_text = message;
    this->_textTexture = this->_graphics->getTextureFromSurface(this->_graphics->getSurfaceFromText(TextType::SIGNPOST, message, this->_textFrame.getW() - 60));
    return *this;
}

void TextBox::update(float elapsedTime)
{
    this->_showTillTime -= elapsedTime;
    if (this->_showTillTime <= 0)
    {
        this->_showTextBox = false;
        this->_showTillTime = 0;
    }
    else
        this->_showTextBox = true;
}

void TextBox::draw(Graphics &graphics)
{
    if (!this->_showTextBox)
        return;

    if (this->_portrait.isEmpty())
    {
        this->_textFrame.setX(global::SCREEN_WIDTH / 2 - this->_textFrame.getW() / 2);
        this->_textFrame.draw(graphics, this->_textFrame.getX(), this->_textFrame.getY());
    }
    else
    {
        this->_textFrame.draw(graphics, this->_textFrame.getX(), this->_textFrame.getY());
        this->_portraitFrame.draw(graphics, this->_portraitFrame.getX(), this->_portraitFrame.getY());
        // this->_textFrame.draw(graphics, this->_textFrame.getX(), this->_textFrame.getY());
        this->_connector.draw(graphics, this->_connector.getX(), this->_connector.getY());
    }

    int textW, textH;
    SDL_QueryTexture(this->_textTexture, NULL, NULL, &textW, &textH);
    SDL_Rect destText = {this->_textFrame.getX() + 30, this->_textFrame.getY() + 30, textW, textH};
    graphics.blitSurface(this->_textTexture, NULL, &destText);
}
