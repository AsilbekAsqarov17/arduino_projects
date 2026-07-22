#include<LiquidCrystal.h>
int rs = 7;
int en = 8;
int d4 = 9;
int d5 = 10;
int d6 = 11;
int d7 = 12;
int dt = 5000;
int num1;
int num2;
char op;
float answer;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {

  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {

  lcd.setCursor(0, 0);
  lcd.print("Enter Num 1: ");
  
  while(Serial.available() == 0){
  
  }
  num1 = Serial.parseInt();
  lcd.print(num1);
  delay(2000);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Enter Num 2: ");
  
  while(Serial.available() == 0){
  
  }
  num2 = Serial.parseInt();
  lcd.print(num2);
  delay(2000);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Op + - / * : ");
  
  while(Serial.available() == 0){
  
  }
  op = Serial.read();
  lcd.print(op);
  delay(2000);

  switch(op){
    case '+':
      answer = num1 + num2;
      break;
    case '-':
      answer = num1 - num2;
      break;
    case '/':
    if(num2 != 0){
      answer = float(num1) / num2;
    }
      break;
    case '*':
      answer = num1 * num2;
      break;
    default:
      lcd.print("Wrong operator!!!");
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(num1);
  lcd.print(" ");
  lcd.print(op);
  lcd.print(" ");
  lcd.print(num2);
  lcd.print(" = ");
  lcd.print(answer);
  delay(dt);

  lcd.clear();

}
