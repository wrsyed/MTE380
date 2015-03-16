#include <VirtualWire.h>
#include <Ultrasonic.h>

Ultrasonic Front_Ultrasonic(22,23);
Ultrasonic Left_Ultrasonic(24,25);
Ultrasonic Right_Ultrasonic(26,27);
Ultrasonic Back_Ultrasonic(28,29);

int Front_Distance;
int Left_Distance;
int Right_Distance;
int Back_Distance;
char *controller;
void setup() {
  pinMode(13,OUTPUT);
  vw_set_ptt_inverted(true); //
  vw_set_tx_pin(12);
  vw_setup(4000);// speed of data transfer Kbps
  Serial.begin(9600);
}

void loop()
{
 findplatform();
 //turn90();
 findlegomanandstop();
 //pickup();
 sendreversesignal();
}

void findplatform(){
   Right_Distance=Right_Ultrasonic.Ranging(CM);
   while(Right_Distance>200){
        sendforwardsignal();
        Right_Distance=Right_Ultrasonic.Ranging(CM);
        delay(300);
   }
}

void findlegomanandstop(){
  Front_Distance=Front_Ultrasonic.Ranging(CM);
  while(Front_Distance>3){
      //drive forward
       Front_Distance=Front_Ultrasonic.Ranging(CM);
       delay(300);
  }
 // stop_motors();
}

sendforwardsignal(){
   controller="1";
   vw_send((uint8_t *)controller, strlen(controller));
   vw_wait_tx(); // Wait until the whole message is gone
   digitalWrite(13,1);
   delay(300); 
}

sendreversesignal(){
   controller="2";
   vw_send((uint8_t *)controller, strlen(controller));
   vw_wait_tx(); // Wait until the whole message is gone
   digitalWrite(13,1);
   delay(300); 
}
