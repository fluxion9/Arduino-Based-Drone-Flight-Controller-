int upBtn = 9;
int downBtn = 10;
int rightBtn = 11;
int leftBtn = 12;
int yawBtn = 7;
int counterYawBtn = 8;
int AltitudeTrottlePin = A0;
int Altitude;
int motor1;
int motor2;
int motor3;
int motor4;
int maxSpeed = 254;
int maxAltitude = 230;
int Speed = maxSpeed - maxAltitude;

void setup() {
  // put your setup code here, to run once:
pinMode(upBtn, INPUT_PULLUP);
pinMode(downBtn, INPUT_PULLUP);
pinMode(rightBtn, INPUT_PULLUP);
pinMode(leftBtn, INPUT_PULLUP);
pinMode(counterYawBtn, INPUT_PULLUP);
pinMode(yawBtn, INPUT_PULLUP);
pinMode(AltitudeTrottlePin, INPUT);

}

void loop() {
  CalibrateAltitudeTrottle();
  checkControlButtons();
  reMapValues(0, 99);
  sendValueSerial(9600);
}

void CalibrateAltitudeTrottle()
{
  Altitude = analogRead(AltitudeTrottlePin);
  Altitude = map(Altitude, 0, 1023, 0, maxAltitude);
}

void checkControlButtons()
{
  int val1 = digitalRead(upBtn);
  int val2 = digitalRead(downBtn);
  int val3 = digitalRead(rightBtn);
  int val4 = digitalRead(leftBtn);
  int val5 = digitalRead(yawBtn);
  int val6 = digitalRead(counterYawBtn);
  val1 = !val1;
  val2 = !val2;
  val3 = !val3;
  val4 = !val4;
  val5 = !val5;
  val6 = !val6;
  if (val1)
  {
    moveForward();
  }
  else if (val2)
  {
    moveBackwards();
  }
  else if (val3)
  {
    moveRight();
  }
  else if (val4)
  {
    moveLeft();
  }
  else if (val5)
  {
    counterYaw();
  }
  else if (val6)
  {
    yaw();
  }
  else {
    Float();
  }
}
  void reMapValues(int Min, int Max)
  {
    motor1 = map(motor1, 0, maxSpeed, Min, Max);
    motor2 = map(motor2, 0, maxSpeed, Min, Max);
    motor3 = map(motor3, 0, maxSpeed, Min, Max);
    motor4 = map(motor4, 0, maxSpeed, Min, Max);
  }
  void sendValueSerial(int Baud)
  {
    Serial.begin(Baud);
    Serial.println(String(motor1) + String(motor2) + String(motor3) + String(motor4));
    delay(1);
    Serial.end();
  }
  void yaw()
  {
    motor1 = Altitude + Speed;
    motor2 = Altitude;
    motor3 = Altitude;
    motor4 = Altitude + Speed;
  }
  void counterYaw()
  {
    motor1 = Altitude;
    motor2 = Altitude + Speed;
    motor3 = Altitude + Speed;
    motor4 = Altitude;
  }
  void moveForward()
  {
    motor1 = Altitude;
    motor2 = Altitude;
    motor3 = Altitude + Speed;
    motor4 = Altitude + Speed;
  }
  void moveBackwards()
  {
    motor1 = Altitude + Speed;
    motor2 = Altitude + Speed;
    motor3 = Altitude;
    motor4 = Altitude;
  }
  void moveLeft()
  {
    motor1 = Altitude;
    motor2 = Altitude + Speed;
    motor3 = Altitude;
    motor4 = Altitude + Speed;
  }
  void moveRight()
  {
    motor1 = Altitude + Speed;
    motor2 = Altitude;
    motor3 = Altitude + Speed;
    motor4 = Altitude;
  }
  void Float()
  {
    motor1 = Altitude;
    motor2 = Altitude;
    motor3 = Altitude;
    motor4 = Altitude; 
  }
