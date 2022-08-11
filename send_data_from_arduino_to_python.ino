#include <SoftwareSerial.h>
#include <SimpleTimer.h>
#include <Button.h>

SoftwareSerial btSerial(13,12);
SimpleTimer timer;

int relayPin=3;
Button btn(7);
bool mq_state = false;




const int xpin = A0;
const int ypin = A1;
const int zpin = A2;
const int bend_sensor = A3;
const int pressure_sensor = A4;
const int MQ_sensor = A5;

void change_MQ135_mode(){
  mq_state = !mq_state;
}


void check() {
  
//  if(mq_state == true){
    int prev_result = mq135AnalogRead(MQ_sensor);
    int result = map(prev_result, 0, 1023, 0, 9999);
//    Serial.print("mq135 : ");
    Serial.println(result);
//    mySerial.print(result);
//  }

  // bend meter
//  int bend_value = analogRead(bend_sensor);

  // xyz accelerometer
//  int x = analogRead(xpin);
//  delay(1);
//  int y = analogRead(ypin);
//  delay(1);
//  int z = analogRead(zpin);

  // pressure meter
//  int pressure_value = analogRead(pressure_sensor);
//  int result = 123;       // 임시
//  char buffer[24];
//  sprintf(buffer, "%d,%d,%d,%d,%d", bend_value, x, y, z, pressure_value);
//
//  btSerial.write(buffer);
//  btSerial.write(" \r");
//  Serial.print(buffer);
//  Serial.println();

// 테스트
//  Serial.print("Bend : ");
//  Serial.print(bend_value);
//  Serial.print("\t");
//  Serial.print("x, y, z : ");
//  Serial.print(" x: ");
//  Serial.print(x);
//  Serial.print(" y:");
//  Serial.print(y);
//  Serial.print(" z:");
//  Serial.print(z);
//  Serial.print("\t");
//  Serial.print(" pressure: ");
//  Serial.print(pressure_value);
}



void setup(){
  btn.setCallback(change_MQ135_mode);
  pinMode(relayPin, OUTPUT);
  timer.setInterval(100, check);
  Serial.begin(9600);
  Serial.println();       // 이 줄 절대 지우지말 것   그냥 있는거 아님!!! or 개행으로 뛰던
//  mySerial.begin(9600);
//  btSerial.begin(9600);
}

void loop() {
  timer.run();
  btn.check();
  digitalWrite(relayPin, mq_state);
//  if(Serial.available()) {
//    btSerial.write(Serial.read());
//  }
//  if(btSerial.available()){
//    Serial.write(btSerial.read());
//  }
}

int mq135AnalogRead(int pin) {
  float value = 0;
  for (int x = 0; x < 10; x++) {
    value += analogRead(pin);
    delay(20);
  }

  value = value / 10;
  return value;
}
