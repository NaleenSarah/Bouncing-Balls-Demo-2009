#pragma once

#include <gl/glut.h>// OpenGL toolkit
#include <math.h>//mathematics library

#include <time.h>
#include <intrin.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#include "vector"
#include "particle.h"


#define nWidth 100
#define MAX_Balls 2000
int Num_Balls = 50;
float ColourB = 255 / Num_Balls;

int position[3];
float speedX = 2, speedY = 3;
int nColor = 255, nColor2 = 30;

float nFPS;
 
float durationN = 0.0016f;
