//
//  Camera.h
//  StealthPlatformer
//
//  Created by James Vaughan Craster on 07/10/2016.
//  Copyright (c) 2016 James Vaughan Craster. All rights reserved.
//

#ifndef __Platformer2__Camera__
#define __Platformer2__Camera__

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

float lerp (float a, float b, float t);
void positionView(sf::View & playerView, sf::Vector2f position, float cameraTime);


#endif /* defined(__Platformer2__Camera__) */
