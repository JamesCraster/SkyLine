//
//  SpriteController.h
//  StealthPlatformer
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

struct State
{
    sf::Vector2f displacement = sf::Vector2f(0,0);
    sf::Vector2f velocity = sf::Vector2f(0,0);
    sf::Vector2f acceleration = sf::Vector2f(0,0);
};

struct Derivative
{
    sf::Vector2f dx;
    sf::Vector2f dv;
};


class PhysicsController:public State{
private:
    State previous;
public:
    State interpolate(const State &previous, const State &current, float alpha)
    {
        State state;
        state.displacement.x = current.displacement.x*alpha + previous.displacement.x*(1-alpha);
        state.velocity.x = current.velocity.x*alpha + previous.velocity.x*(1-alpha);
        state.displacement.y = current.displacement.y*alpha + previous.displacement.y*(1-alpha);
        state.velocity.y = current.velocity.y*alpha + previous.velocity.y*(1-alpha);
        /*if(state.velocity.x >  720){
            state.velocity.x = 720;
        }
        if(state.velocity.x < -720){
            state.velocity.x = -720;
        }
        if(state.velocity.y > 1000){
            state.velocity.y = 1000;
        }
        if(state.velocity.y < -800){
            state.velocity.y = -800;
        }*/
        return state;
    }
    
    Derivative evaluate(const State &initial, float t)
    {
        Derivative output;
        output.dx = initial.velocity;
        output.dv = initial.acceleration;
        return output;
    }
    
    Derivative evaluate(const State &initial, float t, float dt, const Derivative &d)
    {
        State state;
        state.displacement.x = initial.displacement.x + d.dx.x*dt;
        state.displacement.y = initial.displacement.y + d.dx.y*dt;
        state.velocity.x = initial.velocity.x + d.dv.x*dt;
        state.velocity.y = initial.velocity.y + d.dv.y*dt;
        Derivative output;
        output.dx = state.velocity;
        output.dv = initial.acceleration;
        return output;
    }
    
    void integrate(State &state, float t, float dt)
    {
        Derivative a = evaluate(state, t);
        Derivative b = evaluate(state, t, dt*0.5f, a);
        Derivative c = evaluate(state, t, dt*0.5f, b);
        Derivative d = evaluate(state, t, dt, c);
        
        const sf::Vector2f dxdt = 1.0f/6.0f * (a.dx + 2.0f*(b.dx + c.dx) + d.dx);
        const sf::Vector2f dvdt = 1.0f/6.0f * (a.dv + 2.0f*(b.dv + c.dv) + d.dv);
        
        state.displacement = state.displacement + dxdt*dt;
        state.velocity = state.velocity + dvdt*dt;
        if(state.velocity.x >  720){
            state.velocity.x = 720;
        }
        if(state.velocity.x < -720){
            state.velocity.x = -720;
        }
        if(state.velocity.y > 1000){
            state.velocity.y = 1000;
        }
        if(state.velocity.y < -800){
            state.velocity.y = -800;
        }
    }
    void physicsUpdate(float t, float dt, std::vector<sf::RectangleShape*> tileVector){
        previous = *this;
        integrate(*this, t, dt);
    }
    void renderUpdate(float accumulatorDividedByDt){
        renderDisplacement = interpolate(previous, *this, accumulatorDividedByDt).displacement;
    }
public:
    sf::Vector2f force = sf::Vector2f(0,0);
    double  mass;
    sf::Sprite * parentSprite;
    sf::Vector2f renderDisplacement;
    
    
    OneBoxCollisionController tileCollisionController;
    
    PhysicsController(float passMass,float width, float height,sf::Vector2f passTopLeftCornerOffset):tileCollisionController(width,height, passTopLeftCornerOffset){
        mass = passMass;
    }
    
    sf::Vector2f update(float t, float timeElapsed, float accumulator, std::vector<sf::RectangleShape*> tileVector){
        sf::Vector2f originalPosition = displacement;
        sf::Vector2f position = displacement;
        previous = *this;
        
        acceleration = sf::Vector2f(force.x/mass,force.y/mass);
        velocity += acceleration * timeElapsed;
        
        if(velocity.x >  720){
            velocity.x = 720;
        }
        if(velocity.x < -720){
            velocity.x = -720;
        }
        if(velocity.y > 1000){
            velocity.y = 1000;
        }
        if(velocity.y < -800){
            velocity.y = -800;
        }
        this->displacement = previous.displacement;
        std::cout << velocity.x*timeElapsed << std::endl;
        int interval = 1;
        if(velocity.x > 0)
        {
            for(float x = 0; x < floor(velocity.x*timeElapsed);x+=interval)
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
            
            for(float x = 0; x > floor(velocity.x*timeElapsed)+1;x-=interval)
            {
                position.x -= interval;
                
                if(tileCollisionController.collisionTest(tileVector, position))
                {
                    position.x += interval;
                    break;
                }
                
            }
        }
        if(velocity.y > 0)
        {
            for(float x = 0; x < floor(velocity.y*timeElapsed);x+=interval)
            {
                position.y += interval;
                
                if(tileCollisionController.collisionTest(tileVector, position))
                {
                    position.y -= interval;
                    break;
                }
                
                
            }
        }else
        {
            
            for(float x = 0; x > floor(velocity.y*timeElapsed);x-=interval)
            {
                position.y -= interval;
                if(tileCollisionController.collisionTest(tileVector, position))
                {
                    position.y += interval;
                    break;
                }
                
            }
        }
        force.x = 0;
        force.y = 0;
        displacement += sf::Vector2f(position.x - originalPosition.x, position.y - originalPosition.y);
        return sf::Vector2f(position.x - originalPosition.x, position.y - originalPosition.y);
        
    }
};

class SpriteController{
public:
    sf::FloatRect boundingBox;
    sf::Sprite sprite;
    AnimationControllerVector animationControllerVector;
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
