#include <Watchy.h> //include the Watchy library
#include "HebSerif_Norm50pt7b.h"

#define MAX_CHARS 20
#define MARGIN_X 8

class WatchFace : public Watchy { //inherit and extend Watchy class
  public:
    void drawWatchFace() { //override this method to customize how the watch face looks
      uint16_t lines = 0;
      //const char *lows [11] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};
      const char *lows [11] = {"xpt", ",jt", "h,a", "auka", "gcrt", "anj", "aa", "gca", "vbuna", "ga,", "rag"};
      //const char *teensone [11] = {"","ten", "eleven", "twelve", "thir", "four", "fif", "six", "seven", "eight", "nine"};
      const char *teensone [11] = {"", "rag", ",jt", "ohh,a", "auka", "gcrt", "anj", "aa", "gca", "vbuna", "ga,"};
      //const char *teenstwo [11] = {"", "","", "teen", "teen", "teen", "teen", "teen", "teen", "teen", "teen"};
      const char *teenstwo [11] = {"", "vrag", "vrag", "vrag", "vrag", "vrag", "vrag", "vrag", "vrag", "vrag", "vrag"};
      //const char *tens [10] = {"zero", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
      const char *tens [10] = {"xpt", "rag", "ohrag", "ohauka", "ohgcrt", "ohahnj", "ohaha", "ohgca", "ohbuna", "ohga,"};

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
        strcpy(hrLine1, ",umj");
      } else if (currentTime.Hour < 10) {
        strcpy(hrLine1, lows[currentTime.Hour]);
      } else if (currentTime.Hour < 20) {
        strcpy(hrLine1, teensone[currentTime.Hour - 9]);
        if (currentTime.Hour > 10) {
          strcpy(hrLine2, teenstwo[currentTime.Hour % 10]);
        }
      } else {
        strcpy(hrLine1, tens[currentTime.Hour / 10]);
        if (currentTime.Hour % 10 > 0) {
          strcpy(hrLine2, lows[currentTime.Hour % 10]);
          strcat(hrLine2, "u");
        }
      }

      // MINUTES
      if (currentTime.Minute == 0) {
        strcpy(mnLine1, "euhsc"); // exactly
      } else if (currentTime.Minute == 1) {
        strcpy(mnLine1, "vesu"); // and a minute
      } else if (currentTime.Minute <= 10) {
        strcpy(mnLine1, lows[currentTime.Minute]);
        strcat(mnLine1, "u");
        strcpy(mnLine2, ",ues"); // minutes
      } else if (currentTime.Minute < 20) {
        strcpy(mnLine1, teensone[currentTime.Minute - 9]);
        strcat(mnLine1, "u");
        strcpy(mnLine2, teenstwo[currentTime.Minute % 10]);
      } else {
        if (currentTime.Minute % 10 > 0) {
          strcpy(mnLine1, tens[currentTime.Minute / 10]);
          strcpy(mnLine2, teensone[currentTime.Minute % 10 + 1]);
          strcat(mnLine2, "u");
        } else {
          strcpy(mnLine1, tens[currentTime.Minute / 10]);
          strcat(mnLine1, "u");
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
      //display.setFont(&NunitoSans_Light28pt7b);
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
    }
};

WatchFace m; //instantiate your watchface

void setup() {
  m.init(); //call init in setup
}

void loop() {
  // this should never run, Watchy deep sleeps after init();
}
