//
//  LevelLoader.cpp
//  StealthPlatformer
//
//  Created by James Vaughan Craster on 04/09/2016.
//  Copyright (c) 2016 James Vaughan Craster. All rights reserved.
//

#include "LevelLoader.h"



std::vector<sf::RectangleShape*> loadLevelFromString(std::string levelString,int levelWidth, int levelHeight,sf::Vector2f tileSize, std::vector<Spike*>& spikeVector){
    std::vector<std::vector<int>> levelVector (levelWidth/tileSize.x,std::vector<int> (levelHeight/tileSize.y,0));
    
    int y = 0;
    int xPos = 0;
    for(int a = 0; a < levelString.length()-1; a++){
        
        
        if(levelString[a] == 'n'){
            y+= 1;
            xPos = 0;
            continue;
        }
        if(levelString[a] != ',')
        {
            if(levelString[a+1] != ',' && levelString[a+1] != 'n')
            {
                levelVector[xPos][y] = std::stoi(levelString.substr(a,2));
                xPos += 1;
                a += 1;
                
            }else
            {
                levelVector[xPos][y] = std::stoi(levelString.substr(a,1));
                xPos += 1;
                
                
            }
            
        }
        
        
    }
    std::vector<sf::RectangleShape*> tileVector;
    std::vector<sf::RectangleShape*> entranceVector;
    for (int x = 0; x < levelVector.size(); x++) {
        for(int y = 0; y < levelVector[x].size(); y++){
            if(levelVector[x][y] == 1){
                tileVector.push_back(new sf::RectangleShape);
                tileVector[tileVector.size()-1]->setPosition(x *tileSize.x, y*tileSize.y);
                tileVector[tileVector.size()-1]->setFillColor(sf::Color(0,0,0,0));
                tileVector[tileVector.size()-1]->setOutlineColor(sf::Color(24,118,118));
                tileVector[tileVector.size()-1]->setOutlineThickness(1);
                tileVector[tileVector.size()-1]->setSize(sf::Vector2f(tileSize.x-1, tileSize.y-1));
            }
            if(levelVector[x][y] == 10){
                spikeVector.push_back(new Spike(sf::Vector2f(x * tileSize.x,y * tileSize.y), sf::Vector2f(1,24),sf::Vector2f(tileSize.x,tileSize.x-24), sf::Vector2f(tileSize.x/2,tileSize.y/2)));
                
            }
            if(levelVector[x][y] == 11){
                spikeVector.push_back(new Spike(sf::Vector2f(x * tileSize.x,y * tileSize.y), sf::Vector2f(1,24),sf::Vector2f(tileSize.x-1,tileSize.x-24), sf::Vector2f(tileSize.x/2,tileSize.y/2)));
                spikeVector[spikeVector.size()-1]->rotate(90);
                
            }
            if(levelVector[x][y] == 12){
                spikeVector.push_back(new Spike(sf::Vector2f(x * tileSize.x,y * tileSize.y), sf::Vector2f(1,24),sf::Vector2f(tileSize.x-1,tileSize.x-24), sf::Vector2f(tileSize.x/2,tileSize.y/2)));
                spikeVector[spikeVector.size()-1]->rotate(180);
                
            }
            if(levelVector[x][y] == 13){
                spikeVector.push_back(new Spike(sf::Vector2f(x * tileSize.x,y * tileSize.y), sf::Vector2f(1,24),sf::Vector2f(tileSize.x-1,tileSize.x-24), sf::Vector2f(tileSize.x/2,tileSize.y/2)));
                spikeVector[spikeVector.size()-1]->rotate(270);
                
            }
        }
    }
    return tileVector;
    
    
}