#pragma once
#include <SDL.h>

//all the constants used in our snake project are here

const int ScreenSize = 768;
const int ConstantSize = 32;
//dividing width of screen by constantSize in order to get  snake block size
const int SnakeBlock = ScreenSize / ConstantSize;

const int noOfFrames = 15;
const int runClipRate = 1000 / noOfFrames;
