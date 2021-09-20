/*===================================================
* Ayas Nasih - S1600655
* IoT - Challenge 3
* Radio Datagram Transmitter (Reciever Device)
=====================================================*/
#include "MicroBit.h"
#include "icons.h"

// Init device
MicroBit uBit;

// Data received event handler
void onData(MicroBitEvent e) {
    ManagedString rData = uBit.radio.datagram.recv();
    if (rData == "1") {
        uBit.display.print(mImage_heart);
    }
    else if (rData == "2") {
        uBit.display.print(mImage_duck);
    }
    else if (rData == "3") {
        uBit.display.print(mImage_smiley);
    }
    uBit.sleep(500);
    uBit.display.clear();
}

int main() {
    uBit.init();

    uBit.radio.setGroup(10); // Ensure both devices are in the same group
    uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onData); // Attach event handler

    uBit.radio.enable(); 

    while (1) {
        uBit.sleep(1000);
    }
}