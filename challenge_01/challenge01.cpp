#include "MicroBit.h"

MicroBit uBit;

void onShake()
{

}

int main() { 
  uBit.init(); 
  uBit.messageBus.listen(MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_SHAKE, onShake);

}