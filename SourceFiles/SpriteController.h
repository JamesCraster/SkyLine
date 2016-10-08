//
//  SpriteController.h
//  Platformer2
//
//  Created by James Vaughan Craster on 07/10/2016.
//  Copyright (c) 2016 James Vaughan Craster. All rights reserved.
//

#ifndef __Platformer2__SpriteController__
#define __Platformer2__SpriteController__

#include <stdio.h>
#include <cmath>
#include "AnimationController.h"
class OneBoxCollisionController{
public:
    float width;
    float height;
    bool northContact;
    bool southContact;
    bool eastContact;
    bool westContact;
    
    sf::Vector2f topLeftCornerOffset;
    OneBoxCollisionController(float passWidth,float passHeight, sf::Vector2f passTopLeftCornerOffset){
        width = passWidth;
        height = passHeight;
        northContact = 0;
        southContact = 0;
        eastContact = 0;
        westContact = 0;
        topLeftCornerOffset = passTopLeftCornerOffset;
    }
    OneBoxCollisionController(){};
    void stationaryCollisionTest(std::vector<sf::RectangleShape *> &tileVector, sf::Vector2f position, int displacement){
        southContact = collisionTest(tileVector, sf::Vector2f(position.x,position.y + displacement));
        northContact = collisionTest(tileVector, sf::Vector2f(position.x,position.y - displacement));
        eastContact = collisionTest(tileVector, sf::Vector2f(position.x + displacement,position.y));
        westContact = collisionTest(tileVector, sf::Vector2f(position.x - displacement,position.y));
    }
    bool collisionTest(std::vector<sf::RectangleShape *> &tileVector, sf::Vector2f position){
        //move box to top left corner
        position.x -= topLeftCornerOffset.x;
        position.y -= topLeftCornerOffset.y;
        sf::FloatRect centerBox (position.x,position.y, width, height);
        for(int x = 0;  x < tileVector.size(); x++)
        {
            if(centerBox.intersects(tileVector[x]->getGlobalBounds()))
            {
                return 1;
            }
        }
        return 0;
    }
};

class PhysicsController{
public:
    double xAcceleration, yAcceleration;
    double xForce, yForce;
    double xVelocity,yVelocity;
    double  mass;
    sf::Sprite * parentSprite;
    
    
    OneBoxCollisionController tileCollisionController;
    
    PhysicsController(float passMass,float width, float height,sf::Vector2f passTopLeftCornerOffset):tileCollisionController(width,height, passTopLeftCornerOffset){
        mass = passMass;
    }
    
    sf::Vector2f update(float timeElapsed,sf::Vector2f position, std::vector<sf::RectangleShape*> tileVector){
        sf::Vector2f originalPosition = position;
        xAcceleration = xForce/mass;
        yAcceleration = yForce/mass;
        
        xVelocity +=  xAcceleration * timeElapsed;
        yVelocity +=  yAcceleration * timeElapsed;
        float interval = 1;
        if(xVelocity > 0)
        {
            for(float x = 0; x < floor(xVelocity*timeElapsed);x+=interval)
            {
                
                position.x += interval;
                if(tileCollisionController.collisionTest(tileVector, position))
                {
                    
                    position.x -= interval;
                    break;
                }
            }
        }else
        {
            
            for(float x = 0; x > floor(xVelocity*timeElapsed)+1;x-=interval)
            {
                position.x -= interval;
                
                if(tileCollisionController.collisionTest(tileVector, position))
                {
                    position.x += interval;
                    break;
                }
                
            }
        }
        if(yVelocity > 0)
        {
            for(float x = 0; x < floor(yVelocity*timeElapsed);x+=interval)
            {
                position.y += interval;
                // std::cout << tileCollisionController.collisionTest(tileVector, position) << std::endl;
                if(tileCollisionController.collisionTest(tileVector, position))
                {
                    position.y -= interval;
                    break;
                }
                
                
            }
        }else
        {
            
            for(float x = 0; x > floor(yVelocity*timeElapsed);x-=interval)
            {
                position.y -= interval;
                if(tileCollisionController.collisionTest(tileVector, position))
                {
                    position.y += interval;
                    break;
                }
                
            }
        }
        xForce = 0;
        yForce = 0;
        return sf::Vector2f(position.x - originalPosition.x, position.y - originalPosition.y);
        
    }
};

class SpriteController{
public:
    sf::FloatRect boundingBox;
    sf::Sprite sprite;
    std::vector<AnimationController> animationControllerVector;
    sf::Vector2f boundingBoxOffset;
    
    SpriteController(std::vector<AnimationController> passAnimationControllerVector, sf::Vector2f passBoundingBoxOffset,sf::Vector2f boundingBoxDimensions)
    {
        boundingBox.height = boundingBoxDimensions.y;
        boundingBox.width = boundingBoxDimensions.x;
        boundingBoxOffset = passBoundingBoxOffset;
        
    }
    SpriteController(sf::Vector2f passBoundingBoxOffset,sf::Vector2f boundingBoxDimensions){
        boundingBox.height = boundingBoxDimensions.y;
        boundingBox.width = boundingBoxDimensions.x;
        boundingBoxOffset = passBoundingBoxOffset;
        
    }
    void positionBoundingBox(sf::Vector2f position){
        boundingBox.top = position.y + boundingBoxOffset.y;
        boundingBox.left = position.x + boundingBoxOffset.x;
    }
};


#endif /* defined(__Platformer2__SpriteController__) */
