
#include <IRremote.h>
 
// Define switch pin

 
// Define a variable for the button state

 
// Create IR Send Object
IRsend irsend(4);
 
void setup()
{


}
 
void loop() {
  

  

  irsend.sendNEC(0xFEA857, 32); // TV power code

      
    // Add a small delay before repeating
    delay(200);
 
} 
