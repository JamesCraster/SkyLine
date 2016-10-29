//
//  Entities.h
//  StealthPlatformer
//
//  Created by James Vaughan Craster on 07/10/2016.
//  Copyright (c) 2016 James Vaughan Craster. All rights reserved.
//

#ifndef __Platformer2__Entities__
#define __Platformer2__Entities__

#include <stdio.h>
#include "SpriteController.h"
#include <cmath>
class Player: public SpriteController{
public:
    bool isJumping;
    int direction;
    float gravity;
    PhysicsController physicsController;
    int health;
    sf::Clock immuneClock;
    bool notBeenHit = 1;
    sf::Clock blinkClock;
    bool alive = 1;
    
    
    Player(std::vector<AnimationController> passAnimationControllerVector,float mass,float width,float height,sf::Vector2f passTopLeftCornerOffset,sf::Vector2f boundingBoxOffset,sf::Vector2f boundingBoxDimensions,float passGravity, int passHealth):SpriteController(passAnimationControllerVector, boundingBoxOffset,boundingBoxDimensions),physicsController(mass,width,height,passTopLeftCornerOffset){
        isJumping = 0;
        direction = 0;
        gravity = passGravity;
        health = passHealth;
    }
    void testTileCollisions(std::vector<sf::RectangleShape*> tileVector){
        physicsController.tileCollisionController.stationaryCollisionTest(tileVector, sprite.getPosition(),2);
        if(physicsController.tileCollisionController.northContact && physicsController.velocity.y < 0)
        {
            physicsController.velocity.y  = 0;
        }
        if(physicsController.tileCollisionController.southContact && physicsController.velocity.y  > 0)
        {
            physicsController.velocity.y  = 0;
        }
        if(physicsController.tileCollisionController.eastContact && physicsController.velocity.x > 0)
        {
            physicsController.velocity.x = 0;
        }
        if(physicsController.tileCollisionController.westContact && physicsController.velocity.x < 0)
        {
            physicsController.velocity.x = 0;
        }
    }
    void update(float t, float dt, float accumulator, std::vector<sf::RectangleShape*> tileVector,bool mostRecentlyPressed){
        physicsController.update(t,dt,accumulator, tileVector);
        this->positionBoundingBox(physicsController.displacement);
        testTileCollisions(tileVector);
    }
    void damage(int passDamage){
        if(immuneClock.getElapsedTime().asSeconds() > 3 || notBeenHit){
        health -= passDamage;
        if(health <= 0){
            die();
        }else{
            immuneClock.restart();
            blinkClock.restart();
            notBeenHit = 0;
        }
        }
        }
    void die(){
        health = 0;
        alive = 0;
        
        
    }
    void draw(sf::RenderWindow & window){
        this->animationControllerVector.update();
        if(immuneClock.getElapsedTime().asSeconds() < 3 && !notBeenHit){
            if(!(int(blinkClock.getElapsedTime().asSeconds() /0.1) % 5 == 0)){
                window.draw(sprite);
            }
        }else{
            window.draw(sprite);
        }
        
    }
};
class Enemy:public SpriteController{
public:
    OneBoxCollisionController oneBoxCollisionController;
    Enemy(std::vector<AnimationController> passAnimationControllerVector,float mass,float width,float height,sf::Vector2f passTopLeftCornerOffset,sf::Vector2f boundingBoxOffset,sf::Vector2f boundingBoxDimensions,float passGravity):SpriteController(passAnimationControllerVector, boundingBoxOffset,boundingBoxDimensions),oneBoxCollisionController(width,height, passTopLeftCornerOffset){
    }
    
    void move(sf::Vector2f motion, std::vector<sf::RectangleShape*> tileVector){
        float interval = 1;
        sf::Vector2f position = sprite.getPosition();
        sf::Vector2f originalPosition = position;
        
        if(motion.x > 0)
        {
            for(float x = 0; x < floor(motion.x);x+=interval)
            {
                
                position.x += interval;
                if(oneBoxCollisionController.collisionTest(tileVector, position))
                {
                    
                    position.x -= interval;
                    break;
                }
            }
        }else
        {
            
            for(float x = 0; x > floor(motion.x)+1;x-=interval)
            {
                position.x -= interval;
                
                if(oneBoxCollisionController.collisionTest(tileVector, position))
                {
                    position.x += interval;
                    break;
                }
                
            }
        }
        if(motion.y > 0)
        {
            for(float x = 0; x < floor(motion.y);x+=interval)
            {
                position.y += interval;
                if(oneBoxCollisionController.collisionTest(tileVector, position))
                {
                    position.y -= interval;
                    break;
                }
                
                
            }
        }else
        {
            
            for(float x = 0; x > floor(motion.y);x-=interval)
            {
                position.y -= interval;
                if(oneBoxCollisionController.collisionTest(tileVector, position))
                {
                    position.y += interval;
                    break;
                }
                
            }
        }
        sprite.move(position.x - originalPosition.x, position.y - originalPosition.y);
    }
    void update(std::vector<sf::RectangleShape*> tileVector){
        oneBoxCollisionController.stationaryCollisionTest(tileVector, sprite.getPosition(), 2);
        if(oneBoxCollisionController.southContact == 0){
            move(sf::Vector2f(0,4),tileVector);
        }
        
        
    }
    
};
//integrate it with spriteController (and do so for future ones...)
class Spike{
public:
    sf::Vector2f position,leftCornerOffset,dimensions, rotationalCenter;
    sf::FloatRect collisionBox;
    sf::Sprite spikeSprite;
    
private:
    sf::RectangleShape rect;
    AnimationControllerVector animationControllerVector;
    
public:
    Spike(sf::Vector2f position, sf::Vector2f leftCornerOffset, sf::Vector2f dimensions, sf::Vector2f rotationalCenter){
        this->position = position;
        this->leftCornerOffset = leftCornerOffset;
        this->dimensions = dimensions;
        this->rotationalCenter = rotationalCenter;
        collisionBox.left = position.x + leftCornerOffset.x;
        collisionBox.top = position.y + leftCornerOffset.y;
        collisionBox.height = dimensions.y;
        collisionBox.width = dimensions.x;
        spikeSprite.setPosition(position.x, position.y);
        spikeSprite.setOrigin(rotationalCenter);
        spikeSprite.move(rotationalCenter);
        rect.setSize(sf::Vector2f(collisionBox.width,collisionBox.height));
        rect.setPosition(sf::Vector2f(sf::Vector2f(collisionBox.left,collisionBox.top)));
        rect.setOrigin(rotationalCenter.x - leftCornerOffset.x,rotationalCenter.y - leftCornerOffset.y);
        rect.move(rotationalCenter.x - leftCornerOffset.x,rotationalCenter.y - leftCornerOffset.y);
    }
    void rotate(float degrees){
        
        rect.rotate(degrees);
        collisionBox = rect.getGlobalBounds();
        spikeSprite.rotate(degrees);
        
    }
};



#endif /* defined(__Platformer2__Entities__) */
