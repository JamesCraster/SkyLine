//
//  LevelLoader.cpp
//  StealthPlatformer
//
//  Created by James Vaughan Craster on 04/09/2016.
//  Copyright (c) 2016 James Vaughan Craster. All rights reserved.
//

#include "LevelLoader.h"
std::vector<std::vector<int>> convertChunkVectorToLevelVector(std::vector<Chunk> chunkVector){
    std::vector<std::vector<int>> chunkVectorVector;
    for(int i = 0; i < chunkVector.size(); i++){
        chunkVectorVector.insert(chunkVectorVector.end(), chunkVector[i].chunkVector.begin(), chunkVector[i].chunkVector.end());
    }
    return chunkVectorVector;
}
void loadLevelFromLevelVector(std::vector<std::vector<int>> levelVector, sf::Vector2f tileSize, std::vector<Spike*> & spikeVector, std::vector<sf::RectangleShape*> & tileVector){
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
    
}

std::vector<std::vector<int>> loadLevelVectorFromString(std::string levelString,int levelWidth, int levelHeight,sf::Vector2f tileSize){
    std::vector<std::vector<int>> levelVector (levelWidth/tileSize.x,std::vector<int> (levelHeight/tileSize.y,0));
    
    int y = 0;
    int xPos = 0;
    if(levelString.length() != 0){
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
    }
    
    return levelVector;
    
}
std::vector<std::vector<int>> loadLevelFromString(std::string levelString,int levelWidth, int levelHeight,sf::Vector2f tileSize, std::vector<Spike*>& spikeVector,std::vector<sf::RectangleShape*> &tileVector){
    std::vector<std::vector<int>> levelVector = loadLevelVectorFromString(levelString, levelWidth, levelHeight, tileSize);
    std::vector<sf::RectangleShape*> entranceVector;
    loadLevelFromLevelVector(levelVector, tileSize, spikeVector, tileVector);
    
    return levelVector;
    
    
}
std::vector<std::vector<int>> loadLevelFromChunkChain(ChunkChain chunkChain, sf::Vector2f tileSize, std::vector<Spike*> &spikeVector, std::vector<sf::RectangleShape*>& tileVector){
    for(int i = 0; i < tileVector.size(); i++){
        delete tileVector[i];
    }
    spikeVector =  std::vector<Spike*>();
    tileVector = std::vector<sf::RectangleShape*>();
    auto levelVector = chunkChain.levelVector;
    for (int x = 0; x < levelVector.size(); x++) {
        for(int y = 0; y < levelVector[x].size(); y++){
            if(levelVector[x][y] == 1){
                tileVector.push_back(new sf::RectangleShape);
                tileVector[tileVector.size()-1]->setPosition(x *tileSize.x + chunkChain.position.x, y*tileSize.y+ chunkChain.position.y);
                tileVector[tileVector.size()-1]->setFillColor(sf::Color(0,0,0,0));
                tileVector[tileVector.size()-1]->setOutlineColor(sf::Color(24,118,118));
                tileVector[tileVector.size()-1]->setOutlineThickness(1);
                tileVector[tileVector.size()-1]->setSize(sf::Vector2f(tileSize.x-1, tileSize.y-1));
            }
            if(levelVector[x][y] == 10){
                spikeVector.push_back(new Spike(sf::Vector2f(x * tileSize.x,y * tileSize.y)+ chunkChain.position, sf::Vector2f(1,24),sf::Vector2f(tileSize.x,tileSize.x-24), sf::Vector2f(tileSize.x/2,tileSize.y/2)));
                
            }
            if(levelVector[x][y] == 11){
                spikeVector.push_back(new Spike(sf::Vector2f(x * tileSize.x,y * tileSize.y) + chunkChain.position, sf::Vector2f(1,24),sf::Vector2f(tileSize.x-1,tileSize.x-24), sf::Vector2f(tileSize.x/2,tileSize.y/2)));
                spikeVector[spikeVector.size()-1]->rotate(90);
                
            }
            if(levelVector[x][y] == 12){
                spikeVector.push_back(new Spike(sf::Vector2f(x * tileSize.x,y * tileSize.y)+ chunkChain.position, sf::Vector2f(1,24),sf::Vector2f(tileSize.x-1,tileSize.x-24), sf::Vector2f(tileSize.x/2,tileSize.y/2)));
                spikeVector[spikeVector.size()-1]->rotate(180);
                
            }
            if(levelVector[x][y] == 13){
                spikeVector.push_back(new Spike(sf::Vector2f(x * tileSize.x,y * tileSize.y)+ chunkChain.position, sf::Vector2f(1,24),sf::Vector2f(tileSize.x-1,tileSize.x-24), sf::Vector2f(tileSize.x/2,tileSize.y/2)));
                spikeVector[spikeVector.size()-1]->rotate(270);
                
            }
        }
    }
    return levelVector;
}
void drawFloorSpriteFromLevelVector(std::vector<std::vector<int>> levelVector, sf::Texture floorTexture, sf::Texture floorTextureRotated, sf::RenderWindow & window){
    for(int x = 0; x < levelVector.size(); x++){
        for(int y = 0; y < levelVector[x].size(); y++){
            if(levelVector[x][y] == 1){
                if(x-1 >= 0){
                    if(levelVector[x-1][y] != 1){
                        sf::Sprite floorSprite;
                        floorSprite.setTexture(floorTexture);
                        floorSprite.setOrigin(16,16);
                        floorSprite.setTextureRect(sf::IntRect(0,0,2, floorTexture.getSize().y));
                        floorSprite.setPosition(x*32, y*32);
                        floorSprite.setRotation(0);
                        floorSprite.move(16, 16);
                        window.draw(floorSprite);
                        
                    }
                    if(y+1 < levelVector[x].size() && y-1 >= 0){
                        if(levelVector[x-1][y+1] == 1){
                            if(levelVector[x-1][y] == 0 && levelVector[x][y+1] == 1){
                                sf::Sprite floorSprite;
                                floorSprite.setTexture(floorTexture);
                                floorSprite.setTextureRect(sf::IntRect(0,0,2,2));
                                floorSprite.setPosition(x*32, y*32 + 32);
                                window.draw(floorSprite);
                            }
                            if(levelVector[x][y+1] == 0 && levelVector[x-1][y] == 1){
                                sf::Sprite floorSprite;
                                floorSprite.setTexture(floorTexture);
                                floorSprite.setTextureRect(sf::IntRect(0,0,2,2));
                                floorSprite.setPosition(x*32, y*32 + 30);
                                window.draw(floorSprite);
                            }
                        }
                        if(levelVector[x-1][y-1] == 1){
                            if(levelVector[x-1][y] == 0 && levelVector[x][y-1] == 1){
                                sf::Sprite floorSprite;
                                floorSprite.setTexture(floorTexture);
                                floorSprite.setTextureRect(sf::IntRect(0,0,2,2));
                                floorSprite.setPosition(x*32, y*32 -2);
                                window.draw(floorSprite);
                            }
                            if(levelVector[x-1][y] == 0 && levelVector[x-1][y] == 1){
                                sf::Sprite floorSprite;
                                floorSprite.setTexture(floorTexture);
                                floorSprite.setTextureRect(sf::IntRect(0,0,2,2));
                                floorSprite.setPosition(x*32, y*32 -2);
                                window.draw(floorSprite);
                                
                            }
                        }
                        
                    }
                }
                if(x+1 < levelVector.size()){
                    if(levelVector[x+1][y] != 1){
                        sf::Sprite floorSprite;
                        floorSprite.setTexture(floorTexture);
                        floorSprite.setOrigin(16,16);
                        floorSprite.setTextureRect(sf::IntRect(0,0,2, floorTexture.getSize().y));
                        floorSprite.setPosition(x*32, y*32);
                        floorSprite.setRotation(180);
                        floorSprite.move(16, 16);
                        window.draw(floorSprite);
                        
                    }
                    if(y+1 < levelVector[x].size() && y-1 >= 0){
                        if(levelVector[x+1][y+1] == 1){
                            if(levelVector[x+1][y] == 0 && levelVector[x][y+1] == 1){
                                sf::Sprite floorSprite;
                                floorSprite.setTexture(floorTexture);
                                floorSprite.setTextureRect(sf::IntRect(0,0,2,2));
                                floorSprite.setPosition(x*32 + 30, y*32 + 32);
                                window.draw(floorSprite);
                            }
                            if(levelVector[x][y+1] == 0 && levelVector[x+1][y] == 1){
                                sf::Sprite floorSprite;
                                floorSprite.setTexture(floorTexture);
                                floorSprite.setTextureRect(sf::IntRect(0,0,2,2));
                                floorSprite.setPosition(x*32 + 32, y*32 + 30);
                                window.draw(floorSprite);
                                
                            }
                        }
                        if(levelVector[x+1][y-1] == 1){
                            if(levelVector[x+1][y] == 0 && levelVector[x][y-1] == 1){
                                sf::Sprite floorSprite;
                                floorSprite.setTexture(floorTexture);
                                floorSprite.setTextureRect(sf::IntRect(0,0,2,2));
                                floorSprite.setPosition(x*32 + 30, y*32 -2);
                                window.draw(floorSprite);
                            }
                            if(levelVector[x][y-1] == 0 && levelVector[x+1][y] == 1){
                                sf::Sprite floorSprite;
                                floorSprite.setTexture(floorTexture);
                                floorSprite.setTextureRect(sf::IntRect(0,0,2,2));
                                floorSprite.setPosition(x*32 + 32, y*32 -2);
                                window.draw(floorSprite);
                                
                            }
                        }
                        
                    }
                    
                }
                if(y-1 > 0){
                    if(levelVector[x][y-1] != 1){
                        sf::Sprite floorSprite;
                        floorSprite.setTexture(floorTexture);
                        floorSprite.setOrigin(16,16);
                        floorSprite.setPosition(x*32 + 16, y*32 + 16);
                        floorSprite.setRotation(90);
                        window.draw(floorSprite);
                        
                    }
                }
                if(y+1 < levelVector[x].size()){
                    if(levelVector[x][y+1] != 1){
                        sf::Sprite floorSprite;
                        floorSprite.setTexture(floorTextureRotated);
                        floorSprite.setPosition(x*32,y*32 + 32-6);
                        window.draw(floorSprite);
                        
                    }
                }
                
            }
            
        }
        
        
    }
    
}