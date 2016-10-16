//
//  LevelGenerator.h
//  Platformer2
//
//  Created by James Vaughan Craster on 09/10/2016.
//  Copyright (c) 2016 James Vaughan Craster. All rights reserved.
//

#ifndef __Platformer2__LevelGenerator__
#define __Platformer2__LevelGenerator__

#include <stdio.h>
#include <cmath>
#include <vector>
#include <random>
#include <iostream>
#include <ctime> // Needed for the true randomization
#include <cstdlib>
#endif /* defined(__Platformer2__LevelGenerator__) */

int quota(int blockCount, bool condition, int lessThanOrEqual, int greaterThanOrEqual);

int probability(std::vector<int> blockTypes, std::vector<float> probabilityVector);

std::vector<float> assignProbabilities(std::vector<int> blockTypes, std::vector<int> blockTypeFrequencies, std::vector<float> probabilityVector, std::vector<bool> conditionVector,std::vector<int> lessThanOrEqualVector, std::vector<int> greaterThanOrEqualVector);

bool inVector(std::vector<int> alreadyCovered, int integer);

void generator(std::vector<std::vector<int>> & levelVector, int code, std::vector<int> blockTypes, std::vector<float> probabilityVector, std::vector<bool> conditionVector,std::vector<int> lessThanOrEqualVector, std::vector<int> greaterThanOrEqualVector);

