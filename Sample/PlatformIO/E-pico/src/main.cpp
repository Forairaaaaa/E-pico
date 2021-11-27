#include <Arduino.h>
#include <U8g2lib.h>


U8G2_SH1107_128X80_F_HW_I2C u8g2(U8G2_R1, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 22, /* data=*/ 21);


void led( void *pvParameters );
void oled( void *pvParameters );

void setup() {

    // Serial
    Serial.begin(115200);
    Serial.println("E-pico");

    // OLED task create
    xTaskCreatePinnedToCore(oled, "oledTask", 2048, NULL, 3, NULL, 0);
    // Test led task create
    xTaskCreatePinnedToCore(led, "ledTask", 1024, NULL, 0, NULL, 0);
}


void loop() {
}


// led Task
void led( void *pvParameters ) {
    // led setup
    ledcSetup(0, 12000, 8);
    ledcAttachPin(2, 0);

    for(;;) {
        // Forward
        for(int i = 0; i<255; i++) {
            ledcWrite(0, i); 
            delay(5);
        }
        delay(300);
        // Backward
        for(int i = 255; i>0; i--) {
            ledcWrite(0, i); 
            delay(5);
        }
    }
}


// OLED Task
void oled( void *pvParameters ) {
    char buffer[100];
    int i = 1;

    // U8g2 setup
    u8g2.begin();
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB24_tr);
    u8g2.drawStr(10,47,"E-pico");
    u8g2.sendBuffer();
    delay(1500);

    for(;;) {
        // Update OLED
        u8g2.clearBuffer();

        u8g2.setFont(u8g2_font_ncenB08_tr);
        u8g2.drawStr(0,8,"E-pico:");
        u8g2.drawStr(0,22,"OLED display test");

        sprintf(buffer, "%d", i++);
        u8g2.setFont(u8g2_font_ncenB24_tr);
        u8g2.drawStr(0,67,buffer);

        u8g2.sendBuffer();
        delay(10);
    }
}
