//#include "nkpins.h"
#include "MicroBit.h"

MicroBit uBit;

int p1_result = -1;
int p2_result = -1;
bool game_over = false;

void show_winner() {
    
    //p1 and p2 got same result
    if(p1_result == p2_result) {
        uBit.display.scroll("DRAW");
        game_over = true;
    }
    
     //p1 is rock and p2 is paper
    if(p1_result == 0 && p2_result == 1) {
        uBit.display.scroll("P2 WINS");
    }
    
    //p1 is rock and p2 is scissors
    if(p1_result == 0 && p2_result > 1) {
        uBit.display.scroll("P1 WINS");
    }
    
        
    //p1 is paper and p2 is rock
    if(p1_result == 1 && p2_result == 0) {
        uBit.display.scroll("P1 WINS");
    }
    
    //p1 is paper and p2 is scissors
    if(p1_result == 1 && p2_result > 1) {
        uBit.display.scroll("P2 WINS");
    }
    
    //p1 is scissors and p2 is rock
    if(p1_result > 1 && p2_result == 0) {
        uBit.display.scroll("P2 WINS");
    }
    
    //p1 is scissors and p2 is paper
    if(p1_result > 1 && p2_result == 1) {
        uBit.display.scroll("P1 WINS");
    }
    
    
    
}

void 
onShake(MicroBitEvent) {
    if(p1_result != -1 && p2_result != -1) {
        show_winner();
        return;
    }
    int rand = uBit.random(3);
    switch(rand) {
      case 0:
        // rock
        uBit.display.scroll("ROCK");
        break;
      case 1:
         // paper
        uBit.display.scroll("PAPER");
        break;
      default:
        // scissors
        uBit.display.scroll("SCISSORS");
    }
    
    if(p1_result == -1) {
        p1_result = rand;
        uBit.display.scroll("P2 TURN");
        return;
    }
    
    if(p1_result != -1 && p2_result == -1) {
        p2_result = rand;
        show_winner();
    }
} 



int main() { 
  uBit.init(); 
  
  uBit.display.scroll("P1 TURN");

  uBit.messageBus.listen(MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_SHAKE, onShake);
  
        while(1)
        uBit.sleep(100);

}

