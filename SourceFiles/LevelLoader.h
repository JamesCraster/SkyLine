//
//  LevelLoader.h
//  Platformer2
//
//  Created by James Vaughan Craster on 04/09/2016.
//  Copyright (c) 2016 James Vaughan Craster. All rights reserved.
//

#ifndef __Platformer2__LevelLoader__
#define __Platformer2__LevelLoader__

#include <stdio.h>
#include <iostream>
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
std::vector<sf::RectangleShape*> loadLevelFromString(std::string levelString,int levelWidth, int levelHeight,sf::Vector2f tileSize);

#endif /* defined(__Platformer2__LevelLoader__) */
