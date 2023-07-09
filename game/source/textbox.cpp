#include "textbox.h"
#include "graphics.h"

TextBox::TextBox() {}

TextBox::TextBox(Graphics &graphics)
{
    this->_textFrame = Sprite(graphics, "text-frame.png", 0, 0, 736, 256, 416, 450);
    this->_portraitFrame = Sprite(graphics, "portrait-frame.png", 0, 0, 256, 256, 128, 450);
    // this->_portrait = Sprite(graphics, ".png", 600, 186, 9, 12, 134, 56);
    this->_connector = Sprite(graphics, "connector.png", 0, 0, 288, 256, 128, 450);
}

void TextBox::update(float elapsedTime) {}

void TextBox::draw(Graphics &graphics)
{
    if (this->_portrait.isEmpty())
        this->_textFrame.draw(graphics, global::SCREEN_WIDTH / 2 - this->_textFrame.getW() / 2, this->_textFrame.getY());
    else
    {
        this->_textFrame.draw(graphics, this->_textFrame.getX(), this->_textFrame.getY());
        this->_portraitFrame.draw(graphics, this->_portraitFrame.getX(), this->_portraitFrame.getY());
        // this->_textFrame.draw(graphics, this->_textFrame.getX(), this->_textFrame.getY());
        this->_connector.draw(graphics, this->_connector.getX(), this->_connector.getY());
    }
}
