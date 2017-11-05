/**The MIT License (MIT)

Copyright (c) 2016 by Daniel Eichhorn

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

See more at http://blog.squix.ch
*/

/* Customizations by Neptune (NeptuneEng on Twitter, Neptune2 on Github)
 *  
 *  Added Wifi Splash screen and credit to Squix78
 *  Modified progress bar to a thicker and symmetrical shape
 *  Replaced TimeClient with built-in lwip sntp client (no need for external ntp client l
 *  Added Setting examples for Ho Chi Minh city
  *  Selectable NTP servers for each locale
  *  Added AM/PM or 24-hour option for each locale
 *  Changed to 7-segment Clock font from http://www.keshikan.net/fonts-e.html
 *  Added Forecast screen for days 4-6 (requires 1.1.3 or later version of esp8266_Weather_Station library)
 *  Fixed bug preventing display.flipScreenVertically() from working
 *  Slight adjustment to overlay
 */

// >>> Uncomment one of the following 2 lines to define which OLED display interface type you are using
//#define spiOLED
#define i2cOLED

#ifdef spiOLED
#include "SSD1306Spi.h"
#endif
#ifdef i2cOLED
#include "SSD1306Wire.h"
#endif
#include "OLEDDisplayUi.h"

// Please read http://blog.squix.org/weatherstation-getting-code-adapting-it
// for setup instructions

#define HOSTNAME "ESP8266-OTA-"

// Setup
const int UPDATE_INTERVAL_SECS = 600; // Update every 10 minutes

#ifdef spiOLED
// Pin definitions for SPI OLED
#define OLED_CS D8    // Chip select
#define OLED_DC D2    // Data/Command
#define OLED_RESET D0 // RESET  - If you get an error on this line, either change Tools->Board to the board you are using or change "D0" to the appropriate pin number for your board.
#endif

#ifdef i2cOLED
// Pin definitions for I2C OLED
const int I2C_DISPLAY_ADDRESS = 0x3C;
const int SDA_PIN = D2;
const int SDC_PIN = D3;
#endif

// -----------------------------------
// Example Locales (uncomment only 1)
#define HoChiMinh
//------------------------------------

#ifdef HoChiMinh
//DST rules for Central European Time Zone
#define UTC_OFFSET +7
// Uncomment for 24 Hour style clock
#define STYLE_24HR

#define NTP_SERVERS "0.asia.pool.ntp.org", "1.asia.pool.ntp.org", "2.asia.pool.ntp.org"

// Wunderground Settings
const boolean IS_METRIC = true;
const String WUNDERGRROUND_API_KEY = "82b6ec05f3c3d959";
const String WUNDERGRROUND_LANGUAGE = "VN";
const String WUNDERGROUND_COUNTRY = "VN";
const String WUNDERGROUND_CITY = "Xom%20Nha%20Chay";
#endif

#ifdef spiOLED
SSD1306Spi display(OLED_RESET, OLED_DC, OLED_CS); // SPI OLED
#endif
#ifdef i2cOLED
SSD1306Wire display(I2C_DISPLAY_ADDRESS, SDA_PIN, SDC_PIN); // I2C OLED
#endif

OLEDDisplayUi ui(&display);

/***************************
 * End Settings
 **************************/
