#include <SoftwareSerial.h>
#include <DHT.h>
#include <LiquidCrystal.h>

#define LCD_RS 6
#define LCD_EN 7
#define LCD_D4 A3
#define LCD_D5 A2
#define LCD_D6 A1
#define LCD_D7 A0
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
///FIELD SWITCHES///////
#define SWITCH1 10
#define SWITCH2 12
#define SWITCH3 13
///PADDY SWITCHES///////
#define SWITCH4 5
#define SWITCH5 4
#define SWITCH6 3

#define RELAY_C 9

const int soilMoisturePin = A4;
#define DHTPIN 8
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);


// Function prototype
void sendMessage(const char *message);

SoftwareSerial gsmSerial(11, 2);
void setup() {
  Serial.begin(9600);
  gsmSerial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);  // Initialize the LCD
  ///FIELD SWITCHES///////
  pinMode(SWITCH1, INPUT_PULLUP);
  pinMode(SWITCH2, INPUT_PULLUP);
  pinMode(SWITCH3, INPUT_PULLUP);
  ///PADDY SWITCHES///////
  pinMode(SWITCH4, INPUT_PULLUP);
  pinMode(SWITCH5, INPUT_PULLUP);
  pinMode(SWITCH6, INPUT_PULLUP);

  pinMode(RELAY_C, OUTPUT);
  pinMode(soilMoisturePin, INPUT);

  digitalWrite(RELAY_C, HIGH);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SMART FARMING");
  lcd.setCursor(0, 1);
  lcd.print("USING IOT");
  delay(2000);
}

void loop() {
  int soilMoistureValue = analogRead(soilMoisturePin);


  // Check if the sensor is detecting any moisture
  if (soilMoistureValue < 100) {  // Adjust the threshold as needed
    soilMoistureValue = 0;        // Set moisture value to 0 if sensor detects no moisture
  } else {
    // Map the moisture value to a percentage scale
    soilMoistureValue = map(soilMoistureValue, 100, 1023, 100, 0);  // Adjust the range as needed
  }






  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();


  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SELECT FIELD");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.setCursor(0, 1);
  lcd.print(" Humid: ");
  lcd.print(humidity);
  lcd.print(" %");
  delay(1000);

  lcd.clear();

  if (temperature > 20) {

    if (digitalRead(SWITCH1) == 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("PADDY FIELD");
      delay(1000);

      if (digitalRead(SWITCH4) == 0) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("PADDY Sowing");

        lcd.setCursor(0, 1);
        lcd.print("Soil:");
        lcd.print(soilMoistureValue);
        lcd.print("%");
        delay(1000);

        if (soilMoistureValue < 55) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Soil:");
          lcd.print(soilMoistureValue);
          lcd.print("%");
          delay(1000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("LOW WATER LEVEL");
          lcd.setCursor(0, 1);
          lcd.print("PUMP ON");
          delay(1000);
          digitalWrite(RELAY_C, LOW);
          sendMessage("PUMP ON FOR WATERING THE PADDY FIELD IN SOWING LEVEL  ");
        }
        if (soilMoistureValue > 55) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Soil:");
          lcd.print(soilMoistureValue);
          lcd.print("%");
          delay(1000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("HIGH WATER LEVEL");
          lcd.setCursor(0, 1);
          lcd.print("PUMP OFF");
          delay(1000);
          digitalWrite(RELAY_C, HIGH);
          sendMessage("PUMP OFF FOR WATERING THE PADDY FIELD IN SOWING LEVEL ");
        }
      }

      if (digitalRead(SWITCH5) == 0) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("PADDY MANURAING");

        lcd.setCursor(0, 1);
        lcd.print("Soil:");
        lcd.print(soilMoistureValue);
        lcd.print("%");
        delay(1000);

        if (soilMoistureValue < 50) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Soil:");
          lcd.print(soilMoistureValue);
          lcd.print("%");
          delay(1000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("LOW WATER LEVEL");
          lcd.setCursor(0, 1);
          lcd.print("PUMP ON");
          delay(1000);
          digitalWrite(RELAY_C, LOW);
          sendMessage("PUMP ON FOR WATERING THE THE PADDY FIELD IN MANURING STAGE  ");
        }
        if (soilMoistureValue > 50) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Soil:");
          lcd.print(soilMoistureValue);
          lcd.print("%");
          delay(1000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("HIGH WATER LEVEL");
          lcd.setCursor(0, 1);
          lcd.print("PUMP OFF");
          delay(1000);
          digitalWrite(RELAY_C, HIGH);
          sendMessage("PUMP OFF FOR WATERING THE PADDY FIELD IN MANURING STAGE ");
        }
      }
      if (digitalRead(SWITCH6) == 0) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("PADDY HARVESTING");

        lcd.setCursor(0, 1);
        lcd.print("Soil:");
        lcd.print(soilMoistureValue);
        lcd.print("%");
        delay(1000);


        if (soilMoistureValue < 30) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Soil:");
          lcd.print(soilMoistureValue);
          lcd.print("%");
          delay(1000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("LOW WATER LEVEL");
          lcd.setCursor(0, 1);
          lcd.print("PUMP ON");
          delay(1000);
          digitalWrite(RELAY_C, LOW);
          sendMessage("PUMP ON FOR WATERING THE PADDY FIELD IN HARVESTING LEVEL  ");
        }
        if (soilMoistureValue > 30) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Soil:");
          lcd.print(soilMoistureValue);
          lcd.print("%");
          delay(1000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("HIGH WATER LEVEL");
          lcd.setCursor(0, 1);
          lcd.print("PUMP OFF");
          delay(1000);
          digitalWrite(RELAY_C, HIGH);
          sendMessage("PUMP OFF FOR WATERING THE PADDY FIELD IN HARVESTING LEVEL ");
        }
      }
    }
    if (digitalRead(SWITCH1) == 1) {
      digitalWrite(RELAY_C, HIGH);
    }



    if (digitalRead(SWITCH2) == 0) {

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("WHEAT FIELD");
      lcd.setCursor(0, 1);
      lcd.print("Soil:");
      lcd.print(soilMoistureValue);
      lcd.print("%");
      delay(1000);
      if (soilMoistureValue < 55) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Soil:");
        lcd.print(soilMoistureValue);
        lcd.print("%");
        delay(1000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("LOW WATER LEVEL");
        lcd.setCursor(0, 1);
        lcd.print("PUMP ON");
        delay(1000);
        digitalWrite(RELAY_C, LOW);
        sendMessage("PUMP ON FOR WATERING THE WHEAT FIELD");
      }
      //  else if (soilMoistureValue > 55) {
      if (soilMoistureValue > 55) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Soil:");
        lcd.print(soilMoistureValue);
        lcd.print("%");
        delay(1000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("HIGH WATER LEVEL");
        lcd.setCursor(0, 1);
        lcd.print("PUMP OFF");
        delay(1000);
        digitalWrite(RELAY_C, HIGH);
        sendMessage("PUMP OFF FOR WATERING THE WHEAT FIELD");
      }
    }

    if (digitalRead(SWITCH3) == 0) {

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("KHARIF FIELD");
      lcd.setCursor(0, 1);
      lcd.print("Soil:");
      lcd.print(soilMoistureValue);
      lcd.print("%");
      delay(1000);
      if (soilMoistureValue < 30) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Soil:");
        lcd.print(soilMoistureValue);
        lcd.print("%");
        delay(1000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("LOW WATER LEVEL");
        lcd.setCursor(0, 1);
        lcd.print("PUMP ON");
        delay(1000);

        digitalWrite(RELAY_C, LOW);
        sendMessage("PUMP ON FOR WATERING THE KHARIF FIELD");
      }
      if (soilMoistureValue > 30) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Soil:");
        lcd.print(soilMoistureValue);
        lcd.print("%");
        delay(1000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("HIGH WATER LEVEL");
        lcd.setCursor(0, 1);
        lcd.print("PUMP OFF");
        delay(1000);
        digitalWrite(RELAY_C, HIGH);
        sendMessage("PUMP OFF FOR WATERING THE KHARIF FIELD");
      }
    }

  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CLIMATE WAS COOL");
    delay(1000);
  }



  String uno = "a" + String(temperature) + "b" + String(humidity) + "c" + String(soilMoistureValue) + "d" + String(digitalRead(RELAY_C)) + "e";
  Serial.println(uno);
}

void sendMessage(const char *message) {
  gsmSerial.println("AT+CMGF=1");
  delay(1000);
  gsmSerial.print("AT+CMGS=\"7386394143\"\r");
  delay(1000);
  gsmSerial.print(message);
  delay(1000);
  gsmSerial.write(26);
  delay(1000);
}
