//
//  LevelLoader.h
//  StealthPlatformer
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
class Spike{
public:
    sf::Vector2f position,leftCornerOffset,dimensions, rotationalCenter;
    sf::FloatRect collisionBox;
    sf::Sprite spikeSprite;
    sf::RectangleShape rect;
    
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
std::vector<sf::RectangleShape*> loadLevelFromString(std::string levelString,int levelWidth, int levelHeight,sf::Vector2f tileSize, std::vector<Spike*> & spikeVector);

#endif /* defined(__Platformer2__LevelLoader__) */
