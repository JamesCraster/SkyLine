//
//  AnimationController.cpp
//  StealthPlatformer
//
//  Created by James Vaughan Craster on 29/08/2016.
//  Copyright (c) 2016 James Vaughan Craster. All rights reserved.
//

#include "AnimationController.h"

    
AnimationController::AnimationController(std::vector <float> passFrameDurations, std::vector <sf::Texture*> passFrameTextures, sf::Sprite * passSprite)
    {
        interFrameTransitionClock.restart();
        frameDurations = passFrameDurations;
        frameTextures = passFrameTextures;
        active = 0;
        parentSprite = passSprite;
        animationSpeed = 1;
        currentFrame = 0;
        
    }
    //to be called each frame
    void AnimationController::update()
    {
        //if in use
        if (active)
        {
            //Check if animation transition necessary
            if(interFrameTransitionClock.getElapsedTime().asSeconds() > frameDurations[currentFrame%frameDurations.size()]/animationSpeed)
            {
                //perform transition
                currentFrame += 1;
                if(currentFrame % frameDurations.size() == 0)
                {
                    currentFrame = 0;
                }
                parentSprite->setTexture(*frameTextures[currentFrame%frameDurations.size()]);
                interFrameTransitionClock.restart();
                update();
                return;
            }
        }
    }
    void AnimationController::setCurrentFrame(int passCurrentFrame)
    {
        currentFrame = passCurrentFrame % frameDurations.size();
        interFrameTransitionClock.restart();
        parentSprite->setTexture(*frameTextures[currentFrame%frameDurations.size()]);
    }
    int AnimationController::getCurrentFrame()
    {
        return currentFrame % frameDurations.size();
        
    }
    void AnimationController::setAnimationSpeed(float passAnimationSpeed){
        animationSpeed = passAnimationSpeed;
    }
    float AnimationController::getAnimationSpeed(){
        return animationSpeed;
    }