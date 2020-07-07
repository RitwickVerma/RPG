#include "player.h"
#include "utils.h"

void Player::handleTileCollision(vector<Rectangle> &colliding)
{
    for (Rectangle &r : colliding)
    {
        sides::Side collisionSide = Sprite::getCollisionSide(r);
        if (collisionSide != sides::NONE)
        {
            switch (collisionSide)
            {
            case sides::LEFT:
                this->_sprite.x() = r.getRight() + 1 - abs(this->_sprite.getLeft() - this->_boundingBox.getLeft());
                this->_dx = 0;
                break;
            case sides::RIGHT:
                this->_sprite.x() = r.getLeft() - 1 - abs(this->_sprite.getLeft() - this->_boundingBox.getRight());
                this->_dx = 0;
                break;
            case sides::TOP:
                this->_sprite.y() = r.getBottom() + 1 - abs(this->_sprite.getTop() - this->_boundingBox.getTop());
                this->_dy = 0;
                break;
            case sides::BOTTOM:
                this->_sprite.y() = r.getTop() - 1 - abs(this->_sprite.getTop() - this->_boundingBox.getBottom());
                this->_dy = 0;
                this->_grounded = (this->_currentLevel->getGravity()) ? true : false;
                break;
            }
        }
    }
}

bool Player::handleLineCollision(vector<Line> &colliding, int elapsedTime)
{
    for (Line &line : colliding)
    {
        float shiftx = 0, shifty = 0, shift1 = 0, shift2 = 0;
        vector<bool> collidingSides = line.getCollidingSides(this->_boundingBox);
        int count = 0;
        for (bool sidecollide : collidingSides)
            if (sidecollide)
                count++;

        if (count == 1) // && (line.m == 0 || line.m == INT_MAX))
        {
            Line templine = line;
            float length = utils::distance(templine.p1, templine.p2);
            float del_x = (templine.p2.x - templine.p1.x) / length;
            float del_y = (templine.p2.y - templine.p1.y) / length;
            templine.p1.x -= 50 * del_x;
            templine.p1.y -= 50 * del_y;
            templine.p2.x += 50 * del_x;
            templine.p2.y += 50 * del_y;
            collidingSides = templine.getCollidingSides(this->_boundingBox);
        }

        for (int i = 0; i < collidingSides.size(); i++)
        {
            if (collidingSides[i] && collidingSides[(i + 1) % collidingSides.size()])
            {
                xyfpair corner;
                if (i == 0)
                {
                    corner = this->_boundingBox.getTopRight();
                }
                else if (i == 1)
                {
                    corner = this->_boundingBox.getBottomRight();
                }
                else if (i == 2)
                {
                    corner = this->_boundingBox.getBottomLeft();
                }
                else if (i == 3)
                {
                    corner = this->_boundingBox.getTopLeft();
                }

                float normal_m = -1 / line.m;
                float normal_b = corner.y - normal_m * corner.x;
                float new_x = (normal_b - line.b) / (line.m - normal_m);
                float new_y = normal_m * new_x + normal_b;
                shiftx = new_x - corner.x;
                shifty = new_y - corner.y;

                collidingSides[i] = collidingSides[(i + 1) % collidingSides.size()] = false;
                goto COLLISION_HANDLED;
            }
        }

        if (collidingSides[0] && collidingSides[2])
        {
            xyfpair point = ((this->_boundingBox.getLeft() <= line.p1.x && line.p1.x <= this->_boundingBox.getRight()) ? line.p1 : line.p2);
            if (line.pointsOnOppositeSide(this->_boundingBox.getTopLeft(), this->_boundingBox.getTopRight(), line.p1, line.p2))
            {
                if (this->_boundingBox.getRight() - point.x < point.x - this->_boundingBox.getLeft())
                    shift1 = point.x - this->_boundingBox.getRight();
                else
                    shift1 = point.x - this->_boundingBox.getLeft();
            }
            if (line.pointsOnOppositeSide(this->_boundingBox.getBottomLeft(), this->_boundingBox.getBottomRight(), line.p1, line.p2))
            {
                if (this->_boundingBox.getRight() - point.x < point.x - this->_boundingBox.getLeft())
                    shift2 = point.x - this->_boundingBox.getRight();
                else
                    shift2 = point.x - this->_boundingBox.getLeft();
            }
            shiftx = ((shift1 < 0 || shift2 < 0) ? min(shift1, shift2) : max(shift1, shift2));
        }
        else if (collidingSides[1] && collidingSides[3])
        {
            xyfpair point = ((this->_boundingBox.getTop() <= line.p1.y && line.p1.y <= this->_boundingBox.getBottom()) ? line.p1 : line.p2);
            if (line.pointsOnOppositeSide(this->_boundingBox.getTopLeft(), this->_boundingBox.getBottomLeft(), line.p1, line.p2))
            {
                if (this->_boundingBox.getBottom() - point.y < point.y - this->_boundingBox.getTop())
                    shift1 = point.y - this->_boundingBox.getBottom();
                else
                    shift1 = point.y - this->_boundingBox.getTop();
            }
            if (line.pointsOnOppositeSide(this->_boundingBox.getTopRight(), this->_boundingBox.getBottomRight(), line.p1, line.p2))
            {
                if (this->_boundingBox.getBottom() - point.y < point.y - this->_boundingBox.getTop())
                    shift2 = point.y - this->_boundingBox.getBottom();
                else
                    shift2 = point.y - this->_boundingBox.getTop();
            }
            shifty = ((shift1 < 0 || shift2 < 0) ? min(shift1, shift2) : max(shift1, shift2));
        }

    COLLISION_HANDLED:

        shiftx += ((shiftx == 0) ? 0 : ((shiftx > 0) ? 1 : -1));
        shifty += ((shifty == 0) ? 0 : ((shifty > 0) ? 1 : -1));
        this->_sprite.x() += shiftx;
        this->_sprite.y() += shifty;
        this->_dx = this->_dy = 0;
        this->updateBoundingBox();
    }
    return true;
}

void Player::handleDoorCollision(vector<Door> &colliding, Level &level, unordered_map<string, Level> *allMaps, Graphics &graphics)
{
    for (auto &d : colliding)
    {
        if (!this->_interact)
            continue;

        graphics.fadeTo();
        string sourceLevel = level.getMapName();

        level = allMaps->at(d.getDestination());

        Door door = Door();
        for (Door &d2 : level.getDoors())
            if (d2.getDestination() == sourceLevel)
                door = d2;

        string side = door.getSpawnSide();
        xyipair spawn_point = level.getPlayerSpawnPoint();

        if (side[0] == 't')
            spawn_point = xyipair(door.getLeft(), door.getTop() - 30 - this->_sprite.h());
        if (side[0] == 'b')
            spawn_point = xyipair(door.getLeft(), door.getBottom() + 30 - this->_sprite.h());
        if (side[0] == 'l')
            spawn_point = xyipair(door.getLeft() - 30 - this->_sprite.w(), door.getTop());
        if (side[0] == 'r')
            spawn_point = xyipair(door.getRight() + 30 - this->_sprite.w(), door.getTop());

        this->_sprite.x() = spawn_point.x;
        this->_sprite.y() = spawn_point.y;

        this->_currentLevel = &level;
        this->updateBoundingBox();
        this->_camera->setCenter(this->getBoundingBox().getCenter());
    }
}