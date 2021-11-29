int upBtn;
int downBtn;
int leftBtn;
int rightBtn;
int altitude;
int altitudeTrottle = 0;
int xCoordsTrottle = 1;
int yCoordsTrottle = 2;
int motor1;
int motor2;
int motor3;
int motor4;
void setup() {
  
}

void loop() {
  checkAltitudeTrottle(altitudeTrottle);
  check_xcoordsTrottle(xCoordsTrottle);
  check_ycoordsTrottle(yCoordsTrottle);
  assignValues();
  sendValueSerial(9600);
}
void checkAltitudeTrottle(int altitudeTrottlePin)
{
  altitude = map(analogRead(altitudeTrottlePin), 0, 1023, 0, 9);
}
void check_ycoordsTrottle(int ycoordsTrottlePin)
{
  int yTrottleVal = analogRead(ycoordsTrottlePin);
  upBtn = map(yTrottleVal, 512, 1023, 0, 3);
  upBtn = constrain(upBtn, 0, 3);
  downBtn = map(yTrottleVal, 512, 0, 0, 3);
  downBtn = constrain(downBtn, 0, 3);
}
void check_xcoordsTrottle(int xcoordsTrottlePin)
{
  int xTrottleVal = analogRead(xcoordsTrottlePin);
  leftBtn = map(xTrottleVal, 512, 0, 0, 3);
  leftBtn = constrain(leftBtn, 0, 3);
  rightBtn = map(xTrottleVal, 512, 1023, 0, 3);
  rightBtn = constrain(rightBtn, 0, 3);
}
void assignValues()
{
  motor1 = altitude - upBtn;
  motor2 = altitude - downBtn;
  motor3 = altitude - leftBtn;
  motor4 = altitude - rightBtn;
}
void sendValueSerial(int Baud)
{
  Serial.begin(Baud);
  Serial.println(String(motor1) + String(motor2) + String(motor3) + String(motor4));
  delay(1);
  Serial.end();
}
