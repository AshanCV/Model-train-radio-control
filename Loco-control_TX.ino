/* nrf24 RC controller for locomotive - Transmeter
    9.04.2020
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>


int data[5];
int Speed; int way; int light; int sp;


RF24 radio(9, 10); //CE, CSN //MSOI-11, MISO-12, CLK-13

const byte password[6] = "00011"; //*enter a security code //

void setup() {
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);

  Serial.begin(9600);
 Wire.begin();

  radio.begin();
  radio.openWritingPipe(password);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();


}

void loop() {

  int F = analogRead(A0);
  int B = analogRead(A1);

  sp = 0;
  for (int i = 0; i < 10; i++) {
    sp = sp + analogRead(A2);
  }
  Speed = sp / 10;

  int L1 = digitalRead(6);
  int L2 = digitalRead(7);
  int H = digitalRead(5);


  if (F > 1020 && B < 1020) {
    way = 1;                            //forword
  } else if (B > 1020 && F < 1020) {
    way = 2;                            //backword
  } else {
    way = 0;                            //stop
  }

 /* if (L1 == 1) {
    L1 = 1;
  } else {
    L1 = 0;
  }
  
  if (L2 == 1) {
    L2 = 1;
  } else {
    L2 = 0;
  }
*/
  data[0] = map(Speed, 0, 1024, 255, 30);
  data[1] = way; // 1-forword, 2-backword, 0-stop
  data[2] = L1;
  data[3] = L2;
  data[4] = H;


  radio.write(data, sizeof(data));

  Serial.print(data[0]);
  Serial.print("    ");
  Serial.print(data[1]);
  Serial.print("    ");
  Serial.print(data[2]);
  Serial.print("    ");
  Serial.print(data[3]);
  Serial.print("    ");
  Serial.println(data[4]);

  delay(10);

}
