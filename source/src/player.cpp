#include "player.h"
#include "graphics.h"
#include "utils.h"

namespace o
{
    const float WALK_SPEED = 0.2f;
    const float GRAVITY = 0.002f;
    const float GRAVITY_CAP = 0.8f;
    const string CHARACTER_SPRITE = "player.png";
    int _w=64;
    int _h=64;
}

Player::Player(){}

Player::Player(Graphics &graphics, xyipair spawnPoint, Rectangle *camera) :
    AnimatedSprite(graphics, o::CHARACTER_SPRITE, 0, 0, o::_w, o::_h, spawnPoint.x, spawnPoint.y, 75)
{
    this->_dx=0;
    this->_dy=0;
    this->_camera=camera;
    this->_grounded=false;
    this->setupAnimation();
    this->_facing=SOUTH;
    
    this->_camera->setCenter(this->_sprite.getCenter());
}

void Player::setupAnimation()
{    
    this->addAnimation(1, 0, o::_h*8, "idle_north", o::_w, o::_h, xyipair(0,0));
    this->addAnimation(1, 0, o::_h*10, "idle_south", o::_w, o::_h, xyipair(0,0));
    this->addAnimation(1, 0, o::_h*11, "idle_east", o::_w, o::_h, xyipair(0,0));
    this->addAnimation(1, 0, o::_h*9, "idle_west", o::_w, o::_h, xyipair(0,0));

    this->addAnimation(9, 0, o::_h*8, "walk_north", o::_w, o::_h, xyipair(0,0));
    this->addAnimation(9, 0, o::_h*10, "walk_south", o::_w, o::_h, xyipair(0,0));
    this->addAnimation(9, 0, o::_h*11, "walk_east", o::_w, o::_h, xyipair(0,0));
    this->addAnimation(9, 0, o::_h*9, "walk_west", o::_w, o::_h, xyipair(0,0));
}

void Player::animationDone(string animation)
{}

void Player::updateBoundingBox()
{
    this->_boundingBox = Rectangle(this->_sprite.x+16, this->_sprite.y+52, o::_w-32, 12);
}

void Player::setCurrentLevel(Level *level)
{
    this->_currentLevel = level;
}

Level * Player::getCurrentLevel()
{
    return this->_currentLevel;
}

void Player::moveNorth()
{
    this->_dx = 0;
    this->_dy = -o::WALK_SPEED;
    this->playAnimation("walk_north");
    this->_facing = NORTH;
}

void Player::moveSouth()
{
    this->_dx = 0;
    this->_dy = o::WALK_SPEED;
    this->playAnimation("walk_south");
    this->_facing = SOUTH;
}

void Player::moveEast()
{
    this->_dx = o::WALK_SPEED;
    this->_dy = 0;
    this->playAnimation("walk_east");
    this->_facing = EAST;
}

void Player::moveWest()
{
    this->_dx = -o::WALK_SPEED;
    this->_dy = 0;
    this->playAnimation("walk_west");
    this->_facing = WEST;
}

void Player::stopMoving()
{
    this->_dx = 0;
    this->_dy = 0;
    switch(this->_facing)
    {
        case NORTH:
            this->playAnimation("idle_north");
            break;
        case SOUTH:
            this->playAnimation("idle_south");
            break;
        case EAST:
            this->playAnimation("idle_east");
            break;
        case WEST:
            this->playAnimation("idle_west");
            break;
    }

}


void Player::undoMove(float elapsedTime)
{
    this->_sprite.x -= this->_dx * elapsedTime;
    this->_sprite.y -= this->_dy * elapsedTime;
    this->updateBoundingBox();
}

void Player::makeMove(float elapsedTime)
{
    this->_sprite.x += this->_dx * elapsedTime;
    this->_sprite.y += this->_dy * elapsedTime;
    this->updateBoundingBox();
}

void Player::handleTileCollision(vector<Rectangle> &colliding)
{
    for( Rectangle &r : colliding)
    {
        sides::Side collisionSide = Sprite::getCollisionSide(r);
        if(collisionSide != sides::NONE)
        {
            switch(collisionSide)
            {
                case sides::LEFT:
                    this->_sprite.x=r.getRight() + 1 - abs(this->_sprite.getLeft() - this->_boundingBox.getLeft());
                    this->_dx=0;
                    break;
                case sides::RIGHT:
                    this->_sprite.x=r.getLeft() - 1 - abs(this->_sprite.getLeft() - this->_boundingBox.getRight());
                    this->_dx=0;
                    break;
                case sides::TOP:
                    this->_sprite.y=r.getBottom() + 1 - abs(this->_sprite.getTop() - this->_boundingBox.getTop());
                    this->_dy=0;
                    break;
                case sides::BOTTOM:
                    this->_sprite.y=r.getTop() - 1 - abs(this->_sprite.getTop() - this->_boundingBox.getBottom());
                    this->_dy=0;
                    this->_grounded = (this->_currentLevel->hasGravity()) ? true : false;
                    break;
            }
        }
    } 
}

bool Player::handleLineCollision(vector<Line> &colliding, int elapsedTime)
{
    for( Line &line : colliding)
    {
        float shiftx=0, shifty=0, shift1 = 0, shift2 = 0;
        vector<bool> collidingSides = line.getCollidingSides(this->_boundingBox);
        int count=0;
        for(bool sidecollide : collidingSides)
            if(sidecollide)
                count++;
        
        if(count==1)// && (line.m == 0 || line.m == INT_MAX))
        {
            Line templine = line;
            float length = utils::distance(templine.p1, templine.p2);
            float del_x = (templine.p2.x - templine.p1.x)/length;
            float del_y = (templine.p2.y - templine.p1.y)/length;
            templine.p1.x -= 50*del_x;
            templine.p1.y -= 50*del_y;
            templine.p2.x += 50*del_x;
            templine.p2.y += 50*del_y;
            collidingSides = templine.getCollidingSides(this->_boundingBox);
        }

        for(int i=0; i<collidingSides.size(); i++)
        {
            if(collidingSides[i] && collidingSides[(i+1)%collidingSides.size()])
            {
                xyfpair corner;
                if(i==0) { corner = this->_boundingBox.getTopRight(); }
                else if(i==1) { corner = this->_boundingBox.getBottomRight(); }
                else if(i==2) { corner = this->_boundingBox.getBottomLeft(); }
                else if(i==3) { corner = this->_boundingBox.getTopLeft(); }

                float normal_m = -1/line.m;
                float normal_b = corner.y - normal_m * corner.x;
                float new_x = (normal_b - line.b)/(line.m - normal_m);
                float new_y = normal_m * new_x + normal_b;
                shiftx = new_x - corner.x;
                shifty = new_y - corner.y;

                collidingSides[i] = collidingSides[(i+1)%collidingSides.size()] = false;
                goto COLLISION_HANDLED;
            }
        }

        if(collidingSides[0] && collidingSides[2])
        {
            xyfpair point = ((this->_boundingBox.getLeft() <= line.p1.x && line.p1.x <= this->_boundingBox.getRight())? line.p1 : line.p2);
            if(line.pointsOnOppositeSide(this->_boundingBox.getTopLeft(), this->_boundingBox.getTopRight(), line.p1, line.p2))
            {
                if(this->_boundingBox.getRight() - point.x < point.x - this->_boundingBox.getLeft())
                    shift1 = point.x - this->_boundingBox.getRight();
                else
                    shift1 = point.x - this->_boundingBox.getLeft();
            }
            if(line.pointsOnOppositeSide(this->_boundingBox.getBottomLeft(), this->_boundingBox.getBottomRight(), line.p1, line.p2))
            {
                if(this->_boundingBox.getRight() - point.x < point.x - this->_boundingBox.getLeft())
                    shift2 = point.x - this->_boundingBox.getRight();
                else
                    shift2 = point.x - this->_boundingBox.getLeft();
            }
            shiftx = ((shift1<0 || shift2<0)? min(shift1, shift2): max(shift1, shift2));
        }
        else if(collidingSides[1] && collidingSides[3])
        {
            xyfpair point = ((this->_boundingBox.getTop() <= line.p1.y && line.p1.y <= this->_boundingBox.getBottom())? line.p1 : line.p2);
            if(line.pointsOnOppositeSide(this->_boundingBox.getTopLeft(), this->_boundingBox.getBottomLeft(), line.p1, line.p2))
            {
                if(this->_boundingBox.getBottom() - point.y < point.y - this->_boundingBox.getTop())
                    shift1 = point.y - this->_boundingBox.getBottom();
                else
                    shift1 = point.y - this->_boundingBox.getTop();

            }
            if(line.pointsOnOppositeSide(this->_boundingBox.getTopRight(), this->_boundingBox.getBottomRight(), line.p1, line.p2))
            {
                if(this->_boundingBox.getBottom() - point.y < point.y - this->_boundingBox.getTop())
                    shift2 = point.y - this->_boundingBox.getBottom();
                else
                    shift2 = point.y - this->_boundingBox.getTop();
                
            }
            shifty = ((shift1<0 || shift2<0)? min(shift1, shift2): max(shift1, shift2));
        }

        COLLISION_HANDLED:

        shiftx += ((shiftx == 0)?0:((shiftx>0)?1:-1)); 
        shifty += ((shifty == 0)?0:((shifty>0)?1:-1)); 
        this->_sprite.x += shiftx;
        this->_sprite.y += shifty;
        this->_dx = this->_dy = 0;
        this->updateBoundingBox();
    }
    return true;
}

void Player::update(float elapsedTime)
{
    AnimatedSprite::update(elapsedTime);

    // Apply Gravity
    if(this->_dy <= o::GRAVITY_CAP && this->_currentLevel->hasGravity())
        this->_dy += o::GRAVITY * elapsedTime; 

    // Move player by changing x, y by velocity dx, dy
    this->makeMove(elapsedTime);

    // Check if the player is within camera after change. If not, move player back.
    // if(!this->_sprite.containedWithin(*this->_camera))
    // {
    //     this->undoMove(elapsedTime);
    //     this->stopMoving();
    // }


}

void Player::draw(Graphics &graphics)
{
    // AnimatedSprite::draw(graphics, this->_sprite.x-this->_camera->getLeft(), this->_sprite.y-this->_camera->getTop());
    AnimatedSprite::draw(graphics, this->_sprite.x, this->_sprite.y);
    
}