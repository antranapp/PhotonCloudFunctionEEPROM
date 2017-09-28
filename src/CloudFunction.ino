#include "Grove_LCD_RGB_Backlight.h"

int configureTime(String time);

struct ConfigurationTime {
    int hour;
    int minute;
};

ConfigurationTime configurationTime;

rgb_lcd lcd;

const int colorR = 100;
const int colorG = 100;
const int colorB = 100;

void setup()
{
    Particle.function("time", configureTime);

    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);

    // Set up background backlight color
    lcd.setRGB(colorR, colorG, colorB);

    lcd.clear();

    EEPROM.get(0, configurationTime);

    lcd.setCursor(0,0);
    lcd.print(configurationTime.hour);

    lcd.setCursor(0,1);
    lcd.print(configurationTime.minute);
}

void loop()
{
    // this loops forever
}

int configureTime(String time)
{
    // Declare the variables of the parts of the String
    String hourString, minuteString;
    int hour, minute;
    int delimeterPosition = time.indexOf(",");

    if (delimeterPosition >= 0) {

        hourString = time.substring(0, delimeterPosition);
        minuteString = time.substring(delimeterPosition+1);
        hour = hourString.toInt();
        minute = minuteString.toInt();
        configurationTime = { hour, minute };

        EEPROM.put(0, configurationTime);

        lcd.setCursor(0,0);
        lcd.print(configurationTime.hour);

        lcd.setCursor(0,1);
        lcd.print(configurationTime.minute);

        return 1;
    }
    return -1;
}
