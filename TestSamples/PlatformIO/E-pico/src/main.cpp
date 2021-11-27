#include <Arduino.h>
#include <U8g2lib.h>

U8G2_SH1107_128X80_F_HW_I2C u8g2(U8G2_R1, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 22, /* data=*/ 21);

int i = 0;

void setup() {
    // U8g2 setup
    u8g2.begin();
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0,10,"E-pico");
    u8g2.sendBuffer();

    // Serial
    Serial.begin(115200);

    // Test led
    pinMode(2, OUTPUT);
}

void loop() {
    // // Serial print test
    Serial.print("Hi, ");
    Serial.println(i++);

    // Test led
    digitalWrite(2, !digitalRead(2));

    delay(1000);
}
