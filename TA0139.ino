

#include <Wire.h>

/*
  L289N Connection:
  ENA = 5V
  ENB = 5V
  IN1 = 5
  IN2 = 6
  IN3 = 10
  IN4 = 11

  LCD1602
  SCL = SCL
  SDA = SDA

  Servo
  Signal = 9
  + = 5V
  - = GND

  Ultrasonic sensor
  Trig = 12
  Echo = 13

  IR control
  Signal = 2
**********************************************************/
/***********************Motor Pin Definition*************************/
int MotorRight1 = 5; //IN1 PWM enabled
int MotorRight2 = 6; //IN2 PWM enabled
int MotorLeft1 = 10; //IN3 PWM enabled
int MotorLeft2 = 11; //IN4 PWM enabled
int counter = 0;

/*************************Init Ultrasonic sensor******************************/
int inputPin = 13 ; // Echo
int outputPin = 12; // Trig
int Fspeedd = 0; // Forward dis
int Rspeedd = 0; // Right dis
int Lspeedd = 0; // Left dis
int directionn = 0; // Define 4 direction flag
int Fgo = 8; // Forward
int Rgo = 6; // Right
int Lgo = 4; // Left
int Bgo = 2; // Back
/******************Bluetooth Init****************************************/
unsigned char Bluetooth_val;
void Bluetooth_Control()
{
  while (Bluetooth_val != 'E') // as long as it is not exit then
  {
    if (Serial.available()) //这一句是用来判断串口是否接收到数据的标志位。
    {
      Bluetooth_val = Serial.read(); //读取（蓝牙）串口数据，并把值赋给val;
      switch (Bluetooth_val)
      {
        case '8': advance(5); Serial.print("\n Car GO "); //UP
          break;
        case '2': back(2);   Serial.print("\n Car back "); //back
          break;
        case '4': left(5);   Serial.print("\n Car Left"); //Left
          break;
        case '6': right(5);   Serial.print("\n Car Right "); //Right
          break;
        case '5': stopp(1);   Serial.print("\n Car stop "); //stop
          break;
        default: stopp(1);
          break;
      }
    }
  }
  stopp(1);
}
/******************Initializition ****************************************/
void setup()
{
  Serial.begin(9600);
  pinMode(MotorRight1, OUTPUT);  // 5 (PWM)
  pinMode(MotorRight2, OUTPUT);  // 6 (PWM)
  pinMode(MotorLeft1,  OUTPUT);  // 10 (PWM)
  pinMode(MotorLeft2,  OUTPUT);  // 11 (PWM)
}
//******************************************************************(Void)
void advance(int a) //Forward
{
  digitalWrite(MotorRight1, LOW);
  digitalWrite(MotorRight2, HIGH);
  digitalWrite(MotorLeft1, LOW);
  digitalWrite(MotorLeft2, HIGH);
  delay(a * 100);
}
void right(int b) //right turn one wheel control
{
  digitalWrite(MotorLeft1, LOW);
  digitalWrite(MotorLeft2, HIGH);
  digitalWrite(MotorRight1, LOW);
  digitalWrite(MotorRight2, LOW);
  delay(b * 100);
}
void left(int c) //Left turn one wheel control
{
  digitalWrite(MotorRight1, LOW);
  digitalWrite(MotorRight2, HIGH);
  digitalWrite(MotorLeft1, LOW);
  digitalWrite(MotorLeft2, LOW);
  delay(c * 100);
}

void stopp(int f) //stop
{
  digitalWrite(MotorRight1, LOW);
  digitalWrite(MotorRight2, LOW);
  digitalWrite(MotorLeft1, LOW);
  digitalWrite(MotorLeft2, LOW);
  delay(f * 100);
}
void back(int g) //Back
{
  digitalWrite(MotorRight1, HIGH);
  digitalWrite(MotorRight2, LOW);
  digitalWrite(MotorLeft1, HIGH);
  digitalWrite(MotorLeft2, LOW);;
  delay(g * 100);
}
//******************************************************************************(LOOP)
void loop()
{
  if (Serial.available()) //If bluetooth successfully receive data
  {
    Bluetooth_val = Serial.read();// start to read the first char
    if (Bluetooth_val == 'w') Bluetooth_Control(); // if read in 'w' then start control
  }
}
