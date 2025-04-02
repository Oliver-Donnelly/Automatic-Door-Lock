#include <Servo.h>
#include <RTC.h>
#include<IRremote.h>

Servo myServo;
IRrecv IR (11);
int locked = 0;
int unlocked = 62;
int latestIR;

void ws(int i){
  int angle = map(i, 0, 255, 0, 270); // Map 0-255 to 0-270 degrees
  myServo.write(angle);
  delay(10);
}

void lock(){
  ws(locked);
}

void unlock(){
  ws(unlocked);
}
void toggleLock(){
  if(myServo.read() == locked){
    unlock();
  }
  else if (myServo.read() == unlocked){
    lock();
  } else{
    myServo.write(0);
  }
}

void setup() {
  myServo.attach(3);
  Serial.begin(9600);
  IR.enableIRIn();
  Serial.begin(9600);
}

void loop() {
  
 if(IR.decode()){
  latestIR = IR.decodedIRData.decodedRawData;
  if(latestIR == 6156 || latestIR == 4108){
  toggleLock();
}
  Serial.println(latestIR);
  
  delay(100);
  IR.resume();
}

}
