//
//  AnimationController.h
//  Platformer1
//
//  Created by James Vaughan Craster on 29/08/2016.
//  Copyright (c) 2016 James Vaughan Craster. All rights reserved.
//

#ifndef __Platformer1__AnimationController__
#define __Platformer1__AnimationController__

#include <stdio.h>
#include <iostream>
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
//Changes the texture of a sf::Sprite to animate it.
class AnimationController{
private:
    std::vector <float> frameDurations;
    std::vector <sf::Texture*> frameTextures;
    sf::Sprite * parentSprite;
    sf::Clock interFrameTransitionClock;
    int currentFrame;
    float animationSpeed;
    
public:
    bool active;
    AnimationController(std::vector <float> passFrameDurations, std::vector <sf::Texture*> passFrameTextures, sf::Sprite * passSprite);
    //to be called each frame
    void update();
    void setCurrentFrame(int passCurrentFrame);
    int getCurrentFrame();
    void setAnimationSpeed(float passAnimationSpeed);
    float getAnimationSpeed();
};


#endif /* defined(__Platformer1__AnimationController__) */
