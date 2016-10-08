//
//  Camera.cpp
//  StealthPlatformer
//
//  Created by James Vaughan Craster on 07/10/2016.
//  Copyright (c) 2016 James Vaughan Craster. All rights reserved.
//

#include "Camera.h"
float lerp (float a, float b, float t) { return a + t * (b - a); }


void positionView(sf::View & playerView, sf::Vector2f position, float cameraTime){
    if(position.x > playerView.getSize().x * 0.5)
    {
        playerView.setCenter(int(lerp(playerView.getCenter().x, position.x,pow(0.09,cameraTime))), int(playerView.getCenter().y));
    }else
    {
        playerView.setCenter(int(lerp(playerView.getCenter().x,playerView.getSize().x * 0.5,pow(0.05,cameraTime))), int(playerView.getCenter().y));
    }
    if(position.y > playerView.getSize().y * 0.5)
    {
        playerView.setCenter(int(playerView.getCenter().x),int(lerp(playerView.getCenter().y, position.y,/*pow(0.005,cameraTime.asSeconds()))*/0.1)));
    }else
    {
        playerView.setCenter(int(playerView.getCenter().x), int(lerp(playerView.getCenter().y,playerView.getSize().y * 0.5,pow(0.05,cameraTime))));
    }
}
