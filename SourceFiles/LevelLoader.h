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
#include "Entities.h"
std::vector<std::vector<int>> loadLevelVectorFromString(std::string levelString,int levelWidth, int levelHeight,sf::Vector2f tileSize);
//ensure each chunk is given correct position! (last Chunk.position + last Chunk.position + Chunk.size.x)
class Chunk{
public:
    std::vector<std::vector<int>> chunkVector;
    const sf::Vector2f position;
    sf::Vector2f size;
    Chunk(std::vector<std::vector<int>> chunkVector, sf::Vector2f position):position(position),chunkVector(chunkVector){
        if(chunkVector.size() > 0 && chunkVector[0].size() > 0){
        this->size = sf::Vector2f(chunkVector.size() *32, chunkVector[0].size() *32);
        }else{
            this->size = sf::Vector2f(0,0);
        }
    }
};
std::vector<std::vector<int>> convertChunkVectorToLevelVector(std::vector<Chunk> chunkVector);

class ChunkChain{
public:
    std::vector<Chunk> chunkChain;
    sf::Vector2f position = sf::Vector2f(0,0);
    std::vector<std::vector<int>> levelVector;
    int readPosition = 0;
    void convertChunkChainToLevelVector(){
        levelVector = convertChunkVectorToLevelVector(chunkChain);
    }
    void appendChunk(Chunk chunk){
        chunkChain.push_back(chunk);
        convertChunkChainToLevelVector();
        if(chunkChain.size() > 0){
            position = chunkChain[0].position;
        }
    }
    void removeChunk(){
        if(chunkChain.size() > 0){
            readPosition += 1;
            for(int x = 0; x < chunkChain[readPosition-1].chunkVector.size(); x++){
                for(int y = 0; y < chunkChain[readPosition-1].chunkVector[x].size(); y++){
                    chunkChain[readPosition-1].chunkVector[x][y] = 0;
                }
            }
            convertChunkChainToLevelVector();
        }
    }
};

void loadLevelFromLevelVector(std::vector<std::vector<int>> levelVector, sf::Vector2f tileSize, std::vector<Spike*> & spikeVector, std::vector<sf::RectangleShape*> & tileVector);

std::vector<std::vector<int>> loadLevelFromChunkChain(ChunkChain chunkChain, sf::Vector2f tileSize, std::vector<Spike*> &spikeVector, std::vector<sf::RectangleShape*>& tileVector);

void drawFloorSpriteFromLevelVector(std::vector<std::vector<int>> levelVector, sf::Texture floorTexture, sf::Texture floorTextureRotated, sf::RenderWindow & window);

#endif /* defined(__Platformer2__LevelLoader__) */
