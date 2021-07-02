#include <Watchy.h> //include the Watchy library
#include <Fonts/FreeSerifBold9pt7b.h>
#include "HebSerif_Norm50pt7b.h"

#define TWELVE_HOURS true
#define MAX_CHARS 20
#define MARGIN_X 8

#define ALEPH 128
#define BET 129
#define GIMEL 130
#define DALET 131
#define HEH 132
#define VAV 133

class WatchFace : public Watchy { //inherit and extend Watchy class
  public:
    void drawWatchFace() { //override this method to customize how the watch face looks
      uint16_t lines = 0;

      //const char *units [11] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};
      const char *units [11] = {"xpt", ",jt", "ohh,a", "auka", "gcrt", "anj", "aa", "gca", "vbuna", "ga,", "rag"};
      //const char *tens [10] = {"zero", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
      const char *tens [10] = {"xpt", "rag", "ohrag", "ohauka", "ohgcrt", "ohahnj", "ohaha", "ohgca", "ohbuna", "ohga,"};
      //const char *unitsMinutes [11] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};
      const char *unitsMinutes [11] = {"xpt", ",jt", "h,a", "auka", "gcrt", "anj", "aa", "gca", "vbuna", "ga,", "rag"};

      // Full refresh every 10 minutes
      if (currentTime.Minute % 10 == 1) {
        //showWatchFace(false);
      }

      char hrLine1[MAX_CHARS] = "";
      char hrLine2[MAX_CHARS] = "";
      char mnLine1[MAX_CHARS] = "";
      char mnLine2[MAX_CHARS] = "";

      // HOURS
      if (currentTime.Hour == 0) {
        strcpy(hrLine1, ",umj"); // Midnight
      } else {
        uint8_t normHour;
        if (TWELVE_HOURS && currentTime.Hour > 12) {
          normHour = currentTime.Hour % 12;
        } else {
          normHour = currentTime.Hour;
        }
        
        if (normHour < 11) {
          strcpy(hrLine1, units[normHour]);
        } else if (normHour < 20) {
          strcpy(hrLine1, units[normHour - 10]);
          strcpy(hrLine2, "vrag"); //teen
        } else {
          strcpy(hrLine1, tens[normHour / 10]);
          if (normHour % 10 > 0) {
            strcpy(hrLine2, units[normHour % 10]);
            strcat(hrLine2, "u"); // and
          }
        }
      }

      // MINUTES
      // special cases
      if (currentTime.Minute == 0) {
        strcpy(mnLine1, "euhsc"); // exactly
      } else if (currentTime.Minute == 1) {
        strcpy(mnLine1, "vesu"); // and a minute
      } else if (currentTime.Minute == 15 && currentTime.Hour % 3 == 0) {
        strcpy(mnLine1, "gcru"); // and a quarter
      } else if (currentTime.Minute == 30 && currentTime.Hour % 2 == 0) {
        strcpy(mnLine1, "hmju"); // and a half
      
      // Other cases
      } else if (currentTime.Minute < 11) {
        strcpy(mnLine1, unitsMinutes[currentTime.Minute]);
        strcat(mnLine1, "u"); // and
        strcpy(mnLine2, ",ues"); // minutes
      } else if (currentTime.Minute < 20) {
        strcpy(mnLine1, units[currentTime.Minute - 10]);
        strcat(mnLine1, "u");
        strcpy(mnLine2, "vrag"); //teen
      } else {
        if (currentTime.Minute % 10 > 0) {
          strcpy(mnLine1, tens[currentTime.Minute / 10]);
          strcpy(mnLine2, units[currentTime.Minute % 10]);
          strcat(mnLine2, "u"); // and
        } else {
          strcpy(mnLine1, tens[currentTime.Minute / 10]);
          strcat(mnLine1, "u"); // and
          strcpy(mnLine2, ",ues"); // minutes
        }
      }

      //drawbg
      display.fillScreen(GxEPD_WHITE);

      display.setTextColor(GxEPD_BLACK);
      display.setTextWrap(false);

      // Tests
      //display.drawBitmap(175, 150, epd_bitmap_aleph, 25, 50, GxEPD_BLACK); //test image
      //display.setFont(&epd_bitmap_Font);
      //display.setCursor(8, 200-5);
      //display.print("ruthk");

      //drawtime
      int16_t  x1, y1;
      uint16_t w, h;

      display.getTextBounds(hrLine1, 0, 0, &x1, &y1, &w, &h);

      // HOURS
      lines += 1;
      // display.setFont(&NunitoSans_Bold28pt7b);
      display.setFont(&epd_bitmap_Font);

      display.getTextBounds(hrLine1, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(display.width() - MARGIN_X - w, lines * 47 - 5);
      display.print(hrLine1);

      if (strlen(hrLine2) > 0) {
        lines += 1;
        display.getTextBounds(hrLine2, 0, 0, &x1, &y1, &w, &h);
        display.setCursor(display.width() - MARGIN_X - w, lines * 47 - 5);
        display.print(hrLine2);
      }

      // MINUTES
      lines += 1;
      //display.setFont(&frankRuhl_Font);
      display.setFont(&epd_bitmap_Font);

      display.getTextBounds(mnLine1, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(display.width() - MARGIN_X - w, lines * 47 - 5);
      display.print(mnLine1);
      if (strlen(mnLine2) > 0) {
        lines += 1;
        display.getTextBounds(mnLine2, 0, 0, &x1, &y1, &w, &h);
        display.setCursor(display.width() - MARGIN_X - w, lines * 47 - 5);
        display.print(mnLine2);
      }

      // VOLTAGE
      int vBatRounded = (int)(100 * getBatteryVoltage());
      display.setFont(&FreeSerifBold9pt7b);
      display.setCursor(4, display.height() - 4);
      display.print(vBatRounded);
    }
};

WatchFace m; //instantiate your watchface

void setup() {
  m.init(); //call init in setup
}

void loop() {
  // this should never run, Watchy deep sleeps after init();
}
