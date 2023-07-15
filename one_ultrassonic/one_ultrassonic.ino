//End: 0x27
#include <Wire.h> // Biblioteca utilizada para fazer a comunicação com o I2C
#include <LiquidCrystal_I2C.h> // Biblioteca utilizada para fazer a comunicação com o display 20x4 

#define col 16 // Serve para definir o numero de colunas do display utilizado
#define lin  2 // Serve para definir o numero de linhas do display utilizado
#define ende  0x27 // Serve para definir o endereço do display.

const int trigPin_y = 9;
const int echoPin_y = 10;
int input = 0;
char userInput;

// defines variables
double distance_y;
double initial_distance_y;

LiquidCrystal_I2C lcd(ende,col,lin); // Chamada da funcação LiquidCrystal para ser usada com o I2C

void measureDistance(double *distance, double initialDistance, int trigger, int echo, char axis, bool firstMeasure);
void resetLcd();

void setup() //Incia o display
{  
  pinMode(trigPin_y, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin_y, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  resetLcd();
  measureDistance(&initial_distance_y,initial_distance_y,trigPin_y,echoPin_y,'y',true);
}


void measureDistance(double *distance, double initialDistance, int trigger, int echo, char axis, bool firstMeasure){
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echo, HIGH);
  // Calculating the distance
  if(firstMeasure){
    * distance = duration * 0.0343 / 2;
  } else {
    * distance = duration * 0.0343 / 2 - initialDistance;
  }
  // Prints the distance on the Serial Monitor
  Serial.println(*distance);
}

void resetLcd(){
  lcd.setCursor(0,0);
  lcd.print("Waiting for");
  lcd.setCursor(0,1);
  lcd.print("Serial Input");
  input = 0;
}

void loop() {
  if(Serial.available()> 0){
    userInput = Serial.read();               // read user input
      if(userInput == 'g'){  
          if(input == 0){
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Measuring");
            input = 1;
          }
          lcd.setCursor(0,1);
          lcd.print(millis()/1000);
          measureDistance(&distance_y,initial_distance_y,trigPin_y,echoPin_y,'y',false);
    }  
    if(userInput == 'f'){
      if(input == 1){
        resetLcd();
      }
    } 
  }
}