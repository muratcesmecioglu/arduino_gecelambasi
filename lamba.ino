//Include https://github.com/mathertel/OneButton library

#include <EEPROM.h>
#include <OneButton.h>

#define PIN_INPUT 2
#define PIN_LED 13
#define PIN_PWM 3

int parlaklik = 0;
bool ayarModu = false;

OneButton button(PIN_INPUT, true, true);

void setup() {
  //Serial.begin(9600);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_PWM, OUTPUT);
  button.attachLongPressStart(longpress_action);
  button.attachClick(click_action);
  button.setPressTicks(2000);
  parlaklik = EEPROM.read(0);
  //Serial.println("Baslangic parlakligi: " + String(parlaklik) );
  fadeIn(parlaklik);
}

void loop() {
  button.tick();
  delay(10);
}

void longpress_action()
{
  ayarModu = !ayarModu;
  if (ayarModu) {
    digitalWrite(PIN_LED, HIGH);

    analogWrite(PIN_PWM, 0);
    delay(30);
    analogWrite(PIN_PWM, parlaklik);
    delay(30);
    analogWrite(PIN_PWM, 0);
    delay(30);
    analogWrite(PIN_PWM, parlaklik);
    delay(30);
    
    //Serial.println("Ayar modu GIRIS");
  } else {
    EEPROM.update(0, parlaklik);
    digitalWrite(PIN_LED, LOW);

    analogWrite(PIN_PWM, 0);
    delay(30);
    analogWrite(PIN_PWM, parlaklik);
    delay(30);
    analogWrite(PIN_PWM, 0);
    delay(30);
    analogWrite(PIN_PWM, parlaklik);
    delay(30);
    
    //Serial.println("Ayar modu CIKIS");
    //Serial.println("Parlaklik Ayarlandi: " + String(parlaklik) );
  }
} // longpress_action

void click_action()
{
  if (ayarModu) {
    if (parlaklik + 15 > 255) {
      parlaklik = 0;
    }
    parlaklik = parlaklik + 15;
    analogWrite(PIN_PWM, parlaklik);
    //Serial.println("parlaklik = " + String(parlaklik));
  }
} //click_action

void fadeIn(int hedef)
{
  for (int i = 0 ; i <= hedef; i += 5) {
    analogWrite(PIN_PWM, i);
    delay(30);
  }
} //fadeIn
