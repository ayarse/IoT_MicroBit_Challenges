/*===================================================
* Ayas Nasih - S1600655
* IoT - Challenge 3
* Radio Datagram Transmitter (Sender Device)
=====================================================*/

#include "MicroBit.h"
#include "icons.h"

// Init device
MicroBit uBit;

// Init buttons
MicroBitButton buttonB(MICROBIT_PIN_BUTTON_B, MICROBIT_ID_BUTTON_B);
MicroBitButton buttonA(MICROBIT_PIN_BUTTON_A, MICROBIT_ID_BUTTON_A);

void send() {
    if (uBit.buttonA.isPressed()) {
        uBit.radio.datagram.send("1");
        uBit.display.print(mImage_heart);
    }
    
    else if (uBit.buttonB.isPressed()) {
        uBit.radio.datagram.send("2");
        uBit.display.print(mImage_duck);
    }
    else {
        uBit.radio.datagram.send("3");
        uBit.display.print(mImage_smiley);
    }
    uBit.sleep(500);
    uBit.display.clear();
}
    
int main() {
    uBit.init();
    
    uBit.radio.setGroup(10); // Ensure both devices are in the same group
    uBit.radio.enable();

    while(1) {
        send(); 
    }
}