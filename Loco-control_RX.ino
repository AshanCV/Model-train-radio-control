/* nrf24 RC controller for locomotive - Receiver
    9.04.2020
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>





#define en 3//conneced pin num//
#define F 2//conneced pin num//
#define B 4//conneced pin num//
#define L1 7//conneced pin num//
#define L2 8//conneced pin num//
#define H 6//conneced pin num//



int data[5];


RF24 radio(9, 10);  //CE, CSN

const byte password[6] = "00011"; //*enter a security code




void setup() {
  pinMode(en, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(H, OUTPUT);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, password);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();



}
boolean button1 = false;
boolean button2 = false;


void loop() {

  while (radio.available()) {

    radio.read(data, sizeof(data));

    Serial.print(data[0]);
    Serial.print("    ");
    Serial.print(data[1]);
    Serial.print("    ");
    Serial.print(data[2]);
    Serial.print("    ");
    Serial.print(data[3]);
    Serial.print("    ");
    Serial.println(data[4]);


    if (data[2] == 1) {
      button1 = true;
    } else {
      if (button1) {
        light1();
        button1 = false;
      }
    }

    if (data[3] == 1) {
      button2 = true;
    } else {
      if (button2) {
        light2();
        button2 = false;
      }
    }

    if (data[4] == 1) {
      digitalWrite(H,HIGH);
    } else if (data[4] == 0) {
    digitalWrite(H,LOW);
    }



    if (data[1] == 0) {
      analogWrite(en, 0);
      digitalWrite(F, LOW);            //stop
      digitalWrite(B, LOW);
      Serial.println("data recv- stop");

    } else if (data[1] == 1) {
      analogWrite(en, data[0]);
      digitalWrite(F, HIGH);           //forword
      digitalWrite(B, LOW);
      Serial.println("data recv- forw");

    } else if (data[1] == 2) {
      analogWrite(en, data[0]);
      digitalWrite(B, HIGH);           //backword
      digitalWrite(F, LOW);
      Serial.println("data recv- bacck");

    }

  }

  analogWrite(en, 0);
  digitalWrite(F, LOW);            //stop
  digitalWrite(B, LOW);
  Serial.println("no data recv- stop");
}


void light1() {
  if (digitalRead(7) == HIGH) {
    digitalWrite(7, LOW);
  } else {
    digitalWrite(7, HIGH);
  }
}

void light2() {
  if (digitalRead(8) == HIGH) {
    digitalWrite(8, LOW);
  } else {
    digitalWrite(8, HIGH);
  }
}
/****
void hornstart() {


  tone1.play(NOTE_C4);
  tone2.play(NOTE_E4);
  // tone3.play(NOTE_A4);

  /*  if(T-millis()>1000/440){
      T=millis();
     digitalWrite(11,!digitalRead(11));
    }*/
/*****
  horn = true;
}


void hornstop() {

  if (horn) {
    tone1.play(NOTE_C3, 200);
   tone2.play(NOTE_E3, 200);

    delay(200);
    tone1.stop();
    tone2.stop();
    //  tone3.stop();

    horn = false;
  } else {
    tone1.stop();
    tone2.stop();
    //  tone3.stop();
  }
}*****/
