//
//  LevelGenerator.cpp
//  StealthPlatformer
//
//  Created by James Vaughan Craster on 09/10/2016.
//  Copyright (c) 2016 James Vaughan Craster. All rights reserved.
//

#include "LevelGenerator.h"

int quota(int blockCount, bool condition = 1, int lessThanOrEqual = 0, int greaterThanOrEqual = INFINITY){
    if(condition){
        if(blockCount < lessThanOrEqual && blockCount >= greaterThanOrEqual){
            return 0;
        }else if(blockCount == lessThanOrEqual){
            return -1;
        }else if(blockCount < greaterThanOrEqual){
            return 1;
        }
    }
    return 0;
}

int probability(std::vector<float> probabilityVector){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0, 1);
    float randomValue = dis(gen);
    float probability = 0;
    //std::cout << randomValue << std::endl;
    for(int i = 0; i < probabilityVector.size(); i++){
        probability += probabilityVector[i];
        if(randomValue <= probability){
            //std::cout << blockTypes[i] << std::endl;
            return i;
        }
        
    }
}

std::vector<float> assignProbabilities(std::vector<int> blockTypes, std::vector<int> blockTypeFrequencies, std::vector<float> probabilityVector, std::vector<bool> conditionVector,std::vector<int> lessThanOrEqualVector, std::vector<int> greaterThanOrEqualVector){
    //perform every quota function on its blockType
    for(int i = 0; i < blockTypes.size(); i++){
        int quotaValue = quota(blockTypeFrequencies[i], conditionVector[i], lessThanOrEqualVector[i], greaterThanOrEqualVector[i]);
        //no difference to be made
        if(quotaValue == 0){
            continue;
        }
        //for every block type - are there too few? If so, increase the probability of choice to 1 (and make others zero)
        if(quotaValue == 1){
            for(int x = 0; x < probabilityVector.size(); x++){
                if(x != i){
                    probabilityVector[x] = 0;
                }else{
                    probabilityVector[x] = 1;
                }
            }
        }
        //are there enough so that any more would fail the quota? decrease probability of choice to 0, and spread result amongst other probabilities
        if(quotaValue == -1){
            float probabilityValue = probabilityVector[i];
            probabilityVector[i] = 0;
            
            float counter = 0;
            for(int x = 0; x < probabilityVector.size(); x++){
                counter += probabilityVector[x];
            }
            for(int y = 0; y < probabilityVector.size(); y++){
                probabilityVector[y] += (float(probabilityValue)/counter) * probabilityVector[y];
            }
            
            
        }
    }
    return probabilityVector;
}
bool inVector(std::vector<int> alreadyCovered, int integer){
    for(int i = 0; i < alreadyCovered.size(); i++){
        if(alreadyCovered[i] == integer){
            return 1;
        }
    }
}
//consider generator function struct


void generator(std::vector<std::vector<int>> & levelVector, int code, std::vector<int> blockTypes, std::vector<float> probabilityVector, std::vector<bool> conditionVector,std::vector<int> lessThanOrEqualVector, std::vector<int> greaterThanOrEqualVector){

    std::vector<int> blockTypeFrequencies;
    for(int i = 0; i < blockTypes.size(); i++){
        blockTypeFrequencies.push_back(0);
    }
    
    std::vector<std::pair<int,int>> coordinateVector;
    for (int x = 0; x < levelVector.size(); x++) {
        for(int y = 0; y < levelVector[0].size(); y++){
            if(levelVector[x][y] == code){
                coordinateVector.push_back(std::make_pair(x,y));
            }
        }
    }
    int initialSize = coordinateVector.size();
    for(int i = 0; i < initialSize; i++){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(0,coordinateVector.size()-1);
        int randomValue = dis(gen);
       // std::cout << randomValue << std::endl;
        
        std::vector<float> assignedProbabilityVector = assignProbabilities(blockTypes, blockTypeFrequencies, probabilityVector, conditionVector, lessThanOrEqualVector, greaterThanOrEqualVector);
        int blockIndex = probability(assignedProbabilityVector);
        blockTypeFrequencies[blockIndex] += 1;
        levelVector[coordinateVector[randomValue].first][coordinateVector[randomValue].second] = blockTypes[blockIndex];
        coordinateVector.erase(coordinateVector.begin() + randomValue);
        
    }
    
    
   
   
    /*
    
    std::vector<int> alreadyCovered;
    srand(time(0));
    for(int i = 0; i < numberOfCalls; i++){
        int randomValue = rand()%numberOfCalls;
        while (inVector(alreadyCovered,randomValue)) {
            randomValue = rand()%numberOfCalls;
            
        }
        std::vector<float> assignedProbabilityVector = assignProbabilities(blockTypes, blockTypeFrequencies, probabilityVector, conditionVector, lessThanOrEqualVector, greaterThanOrEqualVector);
        int blockIndex = probability(assignedProbabilityVector);
        std::cout << blockIndex << std::endl;
        blockTypeFrequencies[blockIndex-1] += 1;
        resultingBlockTypes[randomValue+1] = blockTypes[blockIndex-1];
        
        alreadyCovered.push_back(randomValue);
    }
    
    int counter = 0;
    for (int x = 0; x < levelVector.size(); x++) {
        for(int y = 0; y < levelVector[0].size(); y++){
            if(levelVector[x][y] == code){
                counter += 1;
                levelVector[x][y] = resultingBlockTypes[counter];
            }
        }
    }*/
}

 std::vector<std::vector<int>> generateLevelVector(std::vector<std::vector<int>> levelVector){
     //consider some generator function vector...
     //call a generator
     //fill in result vector with resultingBlock types...
     //and et cetera et cetera.
     //assign result vector
     std::vector<std::vector<int>> resultVector;
    
    
    
}

