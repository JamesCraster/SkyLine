//
//  LevelLoader.cpp
//  Platformer2
//
//  Created by James Vaughan Craster on 04/09/2016.
//  Copyright (c) 2016 James Vaughan Craster. All rights reserved.
//

#include "LevelLoader.h"



std::vector<sf::RectangleShape*> loadLevelFromString(std::string levelString,int levelWidth, int levelHeight,sf::Vector2f tileSize){
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
                
                
            }else
            {
                levelVector[xPos][y] = std::stoi(levelString.substr(a,1));
                
                xPos += 1;
                
                
            }
            
        }
        
        
    }
    std::vector<sf::RectangleShape*> tileVector;
    for (int x = 0; x < levelVector.size(); x++) {
        for(int y = 0; y < levelVector[x].size(); y++){
            if(levelVector[x][y]){
                tileVector.push_back(new sf::RectangleShape);
                tileVector[tileVector.size()-1]->setPosition(x *tileSize.x, y*tileSize.y);
                tileVector[tileVector.size()-1]->setFillColor(sf::Color(0,0,0));
                tileVector[tileVector.size()-1]->setOutlineColor(sf::Color(24,118,118));
                tileVector[tileVector.size()-1]->setOutlineThickness(1);
                tileVector[tileVector.size()-1]->setSize(sf::Vector2f(tileSize.x, tileSize.y));
            }
        }
    }
    
    return tileVector;
    
    
}