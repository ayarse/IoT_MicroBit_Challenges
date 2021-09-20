// Microbit Icons
#include "MicroBit.h"

const uint8_t img_heart[]{
    0,1,0,1,0,
    1,1,1,1,1,
    1,1,1,1,1,
    0,1,1,1,0,
    0,0,1,0,0,
};

const uint8_t img_duck[]{
    0,1,1,0,0,
    1,1,1,0,0,
    0,1,1,1,1,
    0,1,1,1,0,
    0,0,0,0,0,
};
const uint8_t img_smiley[]{
    0,0,0,0,0,
    0,1,0,1,0,
    0,0,0,0,0,
    1,0,0,0,1,
    0,1,1,1,0,
};

const uint8_t img_blank[]{
    1,1,1,1,1,
    1,1,1,1,1,
    1,1,1,1,1,
    1,1,1,1,1,
    1,1,1,1,1,
};

MicroBitImage mImage_heart(5,5,img_heart); 
MicroBitImage mImage_duck(5,5,img_duck);
MicroBitImage mImage_smiley(5,5,img_smiley);
MicroBitImage mImage_blank(5,5,img_blank);