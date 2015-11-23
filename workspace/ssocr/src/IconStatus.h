#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "Config.h"
#include "Filter.h"
#include "BMPHeader.h"

unsigned char getIconStatus(unsigned char arr[][MAX_HEIGHT],Rect r);
unsigned char calcThresholdIcon(unsigned char arr[][MAX_HEIGHT],Rect r);