// Pin untuk mengontrol driver motor                     //  You need to include Servo.h as it is used by the HB-25 Library
#include <HB25MotorControl.h>

// Variabel untuk menyimpan data dari Python
int pwm_left = 0;
int pwm_right = 0;
int direction_left = 0;
int direction_right = 0;
int A,B;

// Constants
const int rencoderPinA = 19;    // Right Encoder pin A connected to digital pin 2
const int rencoderPinB = 18;    // Right Encoder pin B connected to digital pin 3
const int lencoderPinA = 3;    // Left Encoder pin A connected to digital pin 20
const int lencoderPinB = 2;    // Left Encoder pin B connected to digital pin 21
const byte controlPinL = 6;     // driver left motor connected to PWM Pin 6
const byte controlPinR = 7;     // driver right motor connected to PWM Pin 7
HB25MotorControl motorControlL(controlPinL);
HB25MotorControl motorControlR(controlPinR);

// Variables
volatile long rencoderCount = 0;  // Current encoder count
volatile int rencoderState = 0;   // Current encoder state
int previousState_rencoder = 0;   // Previous Right encoder state
volatile long lencoderCount = 0;  // Current Left encoder count
volatile int lencoderState = 0;   // Current Left encoder state
int previousState_lencoder = 0;   // Previous Left encoder state
// Interrupt service routine for encoder pin A
void encoderISR_rencoder()
{
  // Read the state of encoder pin B
  int pinBState = digitalRead(rencoderPinB);

  // Update the encoder count based on the direction
  if (pinBState == HIGH)
    rencoderCount++;
  else
    rencoderCount--;
}
void encoderISR_lencoder()
{
  // Read the state of lencoder pin B
  int pinBState = digitalRead(lencoderPinB);

  // Update the encoder count based on the direction
  if (pinBState == HIGH)
    lencoderCount++;
  else
    lencoderCount--;
}
void setup()
{
  motorControlL.begin();
  motorControlR.begin();

  // Inisialisasi Serial
  Serial.begin(57600);

  // Initialize encoder pins as inputs
  pinMode (rencoderPinA, INPUT_PULLUP);
  pinMode (rencoderPinB, INPUT_PULLUP);
  pinMode (lencoderPinA, INPUT_PULLUP);
  pinMode (lencoderPinB, INPUT_PULLUP);

  // Enable internal pull-up resistors for the encoder pins
  digitalWrite(rencoderPinA, HIGH);
  digitalWrite(rencoderPinB, HIGH);

  // Attach the interrupt for encoder pin A
  attachInterrupt(digitalPinToInterrupt(rencoderPinA), encoderISR_rencoder, RISING);
  attachInterrupt(digitalPinToInterrupt(lencoderPinA), encoderISR_lencoder, RISING);

  // Start serial communication
  Serial.begin(9600);
}

void loop()
{
  Serial.println(lencoderCount);
  Serial.println(rencoderCount);

//A=digitalRead(rencoderPinA);
//B=digitalRead(rencoderPinB);
  delay(500);
//  Serial.println(A);
//  Serial.println(B);
  // Jika ada data yang diterima dari Python
  // if (Serial.available()) {

  // Membaca data dari Serial
  //String input = Serial.readStringUntil('\n');
  //input.trim();

  // Memisahkan data menjadi PWM kiri, arah kiri, PWM kanan, dan arah kanan
  //int separator1 = input.indexOf(',');
  ///int separator2 = input.indexOf(',', separator1 + 1);
  // int separator3 = input.indexOf(',', separator2 + 1);

  //pwm_left = input.substring(0, separator1).toInt();
  //direction_left = input.substring(separator1 + 1, separator2).toInt();
  //pwm_right = input.substring(separator2 + 1, separator3).toInt();
  //direction_right = input.substring(separator3 + 1).toInt();


  // Mengontrol motor
  //motorControlL.moveAtSpeed(pwm_left);
 // motorControlR.moveAtSpeed(pwm_right);
   motorControlL.moveAtSpeed(-400);
   motorControlR.moveAtSpeed(200);
}
