#include "lcd.h"

LiquidCrystal_I2C lcd(33,16,2);

void lcd_init(){
    Wire.begin(11, 12);     // SDA = 11, SCL = 12
    lcd.begin();
}

void lcd_display(){
    //Display line 1:  Temp: 50C
    lcd.setCursor(0,0);
    lcd.print("Temp: ");
    lcd.print(glob_temperature);
    lcd.print("C");

    //Display line 2:  Humid: 50%
    lcd.setCursor(0,1);
    lcd.print("Humid: ");
    lcd.print(glob_humidity);
    lcd.print("%");
}

void lcd_task(void *parameters){
    lcd_init();
    lcd_display();

    while(1){
        lcd_display();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

