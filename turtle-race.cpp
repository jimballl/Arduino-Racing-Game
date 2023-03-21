// The Dishonored Turtles
// "Turtle Race!"
/*
This Circuit contains:
1) LCD (digital pins 8 - 13)
2) RGB LED (digital pins 3, 5 and 6)
3) 4 buttons (analog pins A1, A2, A3, and A4)
4) Buzzer (digital pin 4)

*/
#include <LiquidCrystal.h>

LiquidCrystal lcd(13,12,11,10,9,8);
// Which pins are connected to the lcd

int RedPin = 3;
int GreenPin = 5;
int BluePin = 6;
// Pins for the rgb

int Gas = A1;
int Brake = A2;
int Honk = A3;
//int Right = A4;
// Pins for the buttons

int potentPin = A5;

int buzz = 2;
// Pin for the buzzer

int seed;
// seed for the random variable

int turn = 0;
// Value of instruction to be selected

bool start = true;
// boolean for the initial if statement
bool turnMade = true;
// boolean for to check if a turn was made

int Speed = 0;
// Variable for speed

int turnSpeed=0;
//variable for minimum turning speed

int distance = 0;
// variable for distance traveled

void setup() {
  pinMode (RedPin, OUTPUT);
  pinMode (GreenPin, OUTPUT);
  pinMode (BluePin, OUTPUT);
  // Sets the appropriet pins for the RGB as output

  pinMode (Gas, INPUT_PULLUP);
  pinMode (Brake, INPUT_PULLUP);
  pinMode (Honk, INPUT_PULLUP);
  // Sets the appropriet pins for the buttons as output
  
  seed = analogRead(A0);
  // Stores the value of the unused pin

  randomSeed(seed);
  // Sets the value of the random seed to the unused pin

  lcd.begin(16,2);
  // Tells the LCD library the dimensions of the LCD
  lcd.clear();
  // Clears the LCD

  lcd.setCursor(0,0);
  lcd.print("Press the Gas"); 
  lcd.setCursor(0,1);
  lcd.print("button to begin");

  delay(1000);
}

void loop() {
  if (digitalRead(Gas) == LOW && start == true){
    //This if statement starts the program

    start = false;

    distance = 0;
    Speed = 0;
    
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("3");
    tone(buzz, 220, 800);
    delay(1000);
    lcd.setCursor(8,0);
    lcd.print("2");
    tone(buzz, 220, 800);
    delay(1000);
    lcd.setCursor(12,0);
    lcd.print("1");
    tone(buzz, 220, 800);
    delay(1000);
    lcd.setCursor(6,1);
    lcd.print("START");
    tone(buzz, 440, 800);
    green();
    delay(1000);
    turnOff();
    lcd.clear();
    // Displays the countdown and start message before the race
    
  }  
  if (start == false){
    while (distance < 700){
      turn = random(1, 4);
      // Selects a random number to be chosen

      lcd.clear();
      
      lcd.setCursor(0,0);
      lcd.print("Speed: ");
      lcd.setCursor(7,0);
      lcd.print(Speed);      
      
      between();
      
      // Function for the time between turns

      if (turn == 1){
        TurnLeft();
        // Function for turning left
      }
      else if (turn == 2){
        TurnRight();
        // Function for turning right
      }
      else {
          Honking();
          //feature for honking
          } //end else statement
      
    }

    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("Race Complete!");
    delay(1000);
    // Displays the "Race Complete!" message
  }
}

int between(){
  for(int i = 0; i < 10; i++){
    if(digitalRead(Gas) == LOW){
      Speed = Speed + 5;
      distance = distance + Speed;
      }
    else if (digitalRead(Brake) == LOW){
      Speed = Speed - 5;
      distance = distance + Speed;
      }
    
    lcd.setCursor(0,0);
    lcd.print("Speed: ");
    lcd.setCursor(7,0);
    lcd.print(Speed);
    
     if(digitalRead(Honk) == LOW){
           tone(buzz, 220, 800);
    }

    delay(500);
  }  
}
// Delay 500 and 0 < i < 14 so it can run for 7 seconds

int Sbetween(){
  for(int i = 0; i < 4; i++){
    if(digitalRead(Gas) == LOW){
      Speed = Speed + 5;
      distance = distance + Speed;
      }
    else if (digitalRead(Brake) == LOW){
      Speed = Speed - 5;
      distance = distance + Speed;
      }
    
    lcd.setCursor(0,0);
    lcd.print("Speed: ");
    lcd.setCursor(7,0);
    lcd.print(Speed);
    
    delay(500);
  }  
}

void TurnLeft(){
  turnSpeed = (random(15, 46));
  while((turnSpeed % 5) != 0)
       { //generates a new random number between 15 and 45 until we know that it is divisible by 5
       turnSpeed = (random(15, 46));
       }  
  lcd.setCursor(0,1);
  lcd.print("Slow down to ");
lcd.setCursor(13,1);
lcd.print(turnSpeed);

  between();

  if (Speed > turnSpeed){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Speed: ");
    Speed = 0;
    lcd.setCursor(7,0);
    lcd.print(Speed);
    lcd.setCursor(0,1);
    lcd.print("Crash!");
  tone(buzz, 220, 1200);
    delay(5000);

    turnOff();

    Speed = 0;

    turnMade = false;
    }
  else if (Speed <= turnSpeed){
    yellow();
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Speed: ");
    lcd.setCursor(7,0);
    lcd.print(Speed);
    lcd.setCursor(0,1);
    lcd.print("Turn Left");
    
    delay(2000);      
    }
    
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Speed: ");
  lcd.setCursor(7,0);
  lcd.print(Speed);

  Sbetween();

  if (analogRead(potentPin) > 923 && turnMade == true){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Speed: ");
    lcd.setCursor(7,0);
    lcd.print(Speed);
    lcd.setCursor(0,1);
    lcd.print("Turn Made!");
    if(digitalRead(Honk) == LOW){
           tone(buzz, 220, 800);
    }

    turnOff();
    
    delay(2000);
  }
  else if (analogRead(potentPin) < 923 && turnMade == true){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Speed: ");
    Speed = 0;
    lcd.setCursor(7,0);
    lcd.print(Speed);
    lcd.setCursor(0,1);
    lcd.print("Crash!");
    tone(buzz, 220, 1200);
    delay(5000);

    turnOff();

    Speed = 0;
  }

  turnMade = true;
}

void TurnRight(){
    lcd.setCursor(0,1);
    turnSpeed = (random(15, 46));
  while((turnSpeed % 5) != 0)
       { //generates a new random number between 15 and 45 until we know that it is divisible by 5
       turnSpeed = (random(15, 46));
       }  
  lcd.setCursor(0,1);
  lcd.print("Slow down to ");
lcd.setCursor(13,1);
lcd.print(turnSpeed);
  between();

  if (Speed > turnSpeed){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Speed: ");
    Speed = 0;
    lcd.setCursor(7,0);
    lcd.print(Speed);
    lcd.setCursor(0,1);
    lcd.print("Crash!");
   tone(buzz, 220, 1200);
    delay(5000);

    turnOff();

    Speed = 0;

    turnMade = false;
    }
  else if (Speed <= turnSpeed){
    blue();
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Speed: ");
    lcd.setCursor(7,0);
    lcd.print(Speed);
    lcd.setCursor(0,1);
    lcd.print("Turn Right");
    delay(2000);      
    }
    
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Speed: ");
  lcd.setCursor(7,0);
  lcd.print(Speed);

  Sbetween();

  if (analogRead(potentPin) < 100 && turnMade == true){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Speed: ");
    lcd.setCursor(7,0);
    lcd.print(Speed);
    lcd.setCursor(0,1);
    lcd.print("Turn Made!");

    turnOff();
    
    delay(2000);
  }
  else if (analogRead(potentPin) > 100 && turnMade == true){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Speed: ");
    Speed = 0;
    lcd.setCursor(7,0);
    lcd.print(Speed);
    lcd.setCursor(0,1);
    lcd.print("Crash!");
    tone(buzz, 220, 1200);
    delay(5000);
    turnOff();

    Speed = 0;
  }

  turnMade = true;
}
void Honking(){
  turnSpeed = (random(15, 46));
  while((turnSpeed % 5) != 0)
       { //generates a new random number between 15 and 45 until we know that it is divisible by 5
       turnSpeed = (random(15, 46));
       }  
  lcd.setCursor(0,1);
  lcd.print("Slow down to ");
lcd.setCursor(13,1);
lcd.print(turnSpeed);

  between();

  if (Speed > turnSpeed){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Speed: ");
    Speed = 0;
    lcd.setCursor(7,0);
    lcd.print(Speed);
    lcd.setCursor(0,1);
    lcd.print("Crash!");
  tone(buzz, 220, 1200);
    delay(5000);

    turnOff();

    Speed = 0;

    turnMade = false;
    }
  else if (Speed <= turnSpeed){
    yellow();
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Speed: ");
    lcd.setCursor(7,0);
    lcd.print(Speed);
    lcd.setCursor(0,1);
    lcd.print("Honk!");
    
    delay(2000);      
    }
    
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Speed: ");
  lcd.setCursor(7,0);
  lcd.print(Speed);

  Sbetween();

  if (digitalRead(Honk) == LOW && turnMade == true){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Speed: ");
    lcd.setCursor(7,0);
    lcd.print(Speed);
    lcd.setCursor(0,1);
    lcd.print("Turn Made!");

    turnOff();
    
    delay(2000);
  }
  else if (digitalRead(Honk) == LOW  && turnMade == true){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Speed: ");
    Speed = 0;
    lcd.setCursor(7,0);
    lcd.print(Speed);
    lcd.setCursor(0,1);
    lcd.print("Crash!");
    tone(buzz, 220, 1200);
    delay(5000);

    turnOff();

    Speed = 0;
  }

  turnMade = true;
}

void yellow () {

  //set the LED pins to values that make yellow
  analogWrite(RedPin, 100);
  analogWrite(GreenPin, 100);
  analogWrite(BluePin, 0);
}
void green () {

  //set the LED pins to values that make green
  analogWrite(RedPin, 0);
  analogWrite(GreenPin, 100);
  analogWrite(BluePin, 0);
}
void red () {

  //set the LED pins to values that make red
  analogWrite(RedPin, 100);
  analogWrite(GreenPin, 0);
  analogWrite(BluePin, 0);
}
void blue () {

  //set the LED pins to values that make blue
  analogWrite(RedPin, 0);
  analogWrite(GreenPin, 0);
  analogWrite(BluePin, 100);
}
void turnOff () {

  //set all three LED pins to 0 or OFF
  analogWrite(RedPin, 0);
  analogWrite(GreenPin, 0);
  analogWrite(BluePin, 0);
}
