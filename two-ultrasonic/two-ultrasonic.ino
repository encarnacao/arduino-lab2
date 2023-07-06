//End: 0x27
#include <Wire.h> // Biblioteca utilizada para fazer a comunicação com o I2C
#include <LiquidCrystal_I2C.h> // Biblioteca utilizada para fazer a comunicação com o display 20x4 

#define col 16 // Serve para definir o numero de colunas do display utilizado
#define lin  2 // Serve para definir o numero de linhas do display utilizado
#define ende  0x27 // Serve para definir o endereço do display.

const int trigPin_y = 9;
const int echoPin_y = 10;
const int trigPin_x = 11;
const int echoPin_x = 12;

// defines variables
double distance_x, distance_y;
double initial_distance_x, initial_distance_y;

LiquidCrystal_I2C lcd(ende,col,lin); // Chamada da funcação LiquidCrystal para ser usada com o I2C

void measureDistance(double *distance, double initialDistance, int trigger, int echo, char axis, bool firstMeasure);

void setup() //Incia o display
{  
  pinMode(trigPin_x, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin_x, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin_y, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin_y, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Dist_x: "); 
  lcd.setCursor(0,1);
  lcd.print("Dist_y:");
  measureDistance(&initial_distance_x,initial_distance_x,trigPin_x,echoPin_x,'x',true);
  measureDistance(&initial_distance_y,initial_distance_y,trigPin_y,echoPin_y,'y',true);
}

void displayDistance(int line, double distance){
  lcd.setCursor(7, line);
  char s[11];
  lcd.print("       ");
  lcd.setCursor(7, line);
  sprintf(s,"%d", (int)distance);
  lcd.print(s);
  lcd.setCursor(14,line);
  lcd.print("cm");
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
  char s[13];
  
  sprintf(s,"Distance_%c:", axis);
  Serial.print(s);
  Serial.print(*distance);
  Serial.println();
}


void loop() {
  measureDistance(&distance_x,initial_distance_x,trigPin_x,echoPin_x,'x',false);
  measureDistance(&distance_y,initial_distance_y,trigPin_y,echoPin_y,'y',false);
  displayDistance(0,distance_x);
  displayDistance(1,distance_y);
  delay(300);
}