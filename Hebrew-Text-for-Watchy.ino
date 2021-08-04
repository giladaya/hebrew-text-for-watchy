#include <Watchy.h> //include the Watchy library
#include <Fonts/FreeSerifBold9pt7b.h>
//#include "FrankRuhlLibre_Regular40pt8b.h"
//#include "FrankRuhlLibre_Bold40pt8b.h"
#include "Assistant_Regular40pt8b.h"
#include "Assistant_Bold40pt8b.h"
#include "HebrewAsciiCodes.h"

#define TWELVE_HOURS true
#define MAX_CHARS 20
#define MARGIN_X 8
#define MARGIN_TOP 6
#define Y_ADVANCE 45
#define MARK_CHANCE 3

// sync once every 6 hours
#define NTP_SYNC_INTERVAL 6 * 60
RTC_DATA_ATTR int ntpSyncCounter = 0;

#define MARKS_COUNT 7
char *marks [MARKS_COUNT] = {"!", "?", ".", "...", ":", ",", "-"};
char * getRandomMark (int maxIdx = MARKS_COUNT) {
  if (random(MARK_CHANCE) == 0) {
    return marks[random(min(maxIdx, MARKS_COUNT))];
  }
  return "";
}

void addMark(char * line1, char * line2, int maxIdx = 999) {
  if (strlen(line2) == 0) {
    char temp[MAX_CHARS];
    strcpy(temp, getRandomMark(maxIdx));
    strcat(temp, line1);
    strcpy(line1, temp);
  } else {
    char temp[MAX_CHARS];
    strcpy(temp, getRandomMark(maxIdx));
    strcat(temp, line2);
    strcpy(line2, temp);
  }
}

class WatchFace : public Watchy { //inherit and extend Watchy class
  public:
    void drawWatchFace() { //override this method to customize how the watch face looks
      uint16_t lines = 0;

      // words
      char zero[] = {SAMEKH, PE, ALEPH, 0};
      char one[] = {TAV, HET, ALEPH, 0};
      char two[] = {MEM_FIN, YOD, YOD, TAV, SHIN, 0};
      char three[] = {SHIN, VAV, LAMED, SHIN, 0};
      char four[] = {AYIN, BET, RESH, ALEPH, 0};
      char five[] = {SHIN, MEM, HET, 0};
      char six[] = {SHIN, SHIN, 0};
      char seven[] = {AYIN, BET, SHIN, 0};
      char eight[] = {HEH, NUN, VAV, MEM, SHIN, 0};
      char nine[] = {AYIN, SHIN, TAV, 0};
      char ten[] = {RESH, SHIN, AYIN, 0};
      char twenty[] = {MEM_FIN, YOD, RESH, SHIN, AYIN, 0};
      char thirty[] = {MEM_FIN, YOD, SHIN, VAV, LAMED, SHIN, 0};
      char forty[] = {MEM_FIN, YOD, AYIN, BET, RESH, ALEPH, 0};
      char fifty[] = {MEM_FIN, YOD, SHIN, YOD, MEM, HET, 0};
      char sixty[] = {MEM_FIN, YOD, SHIN, YOD, SHIN, 0};
      char seventy[] = {MEM_FIN, YOD, AYIN, BET, SHIN, 0};
      char eighty[] = {MEM_FIN, YOD, NUN, VAV, MEM, SHIN, 0};
      char ninety[] = {MEM_FIN, YOD, AYIN, SHIN, TAV, 0};
      char twoOf[] = {YOD, TAV, SHIN, 0};
      char teen[] = {HEH, RESH, SHIN, AYIN, 0};
      char plus[] = {VAV, 0};
      char midnight[] = {TAV, VAV, TSADI, HET, 0};
      char minutes[] = {TAV, VAV, QOF, DALET, 0};

      char aMinute[] = {HEH, QOF, DALET, VAV, 0};
      char quarter[] = {AYIN, BET, RESH, VAV, 0};
      char half[] = {YOD, TSADI, HET, VAV, 0};
      char exactly[] = {QOF, VAV, YOD, DALET, BET, 0};

      // word arrays
      const char *units [11] = {zero, one, two, three, four, five, six, seven, eight, nine, ten};
      const char *tens [10] = {zero, ten, twenty, thirty, forty, fifty, sixty, seventy, eighty, ninety};
      const char *unitsMinutes [11] = {zero, one, twoOf, three, four, five, six, seven, eight, nine, ten};

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
        strcpy(hrLine1, midnight); // Midnight
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
          strcpy(hrLine2, teen); //teen
        } else {
          strcpy(hrLine1, tens[normHour / 10]);
          if (normHour % 10 > 0) {
            strcpy(hrLine2, units[normHour % 10]);
            strcat(hrLine2, plus); // and
          }
        }
      }
      addMark(hrLine1, hrLine2);

      // MINUTES
      // special cases
      if (currentTime.Minute == 0) {
        strcpy(mnLine1, exactly); // exactly
      } else if (currentTime.Minute == 1) {
        strcpy(mnLine1, aMinute); // and a minute
      } else if (currentTime.Minute == 15 && currentTime.Hour % 3 == 0) {
        strcpy(mnLine1, quarter); // and a quarter
      } else if (currentTime.Minute == 30 && currentTime.Hour % 2 == 0) {
        strcpy(mnLine1, half); // and a half

        // Other cases
      } else if (currentTime.Minute < 11) {
        strcpy(mnLine1, unitsMinutes[currentTime.Minute]);
        strcat(mnLine1, plus); // and
        strcpy(mnLine2, minutes); // minutes
      } else if (currentTime.Minute < 20) {
        strcpy(mnLine1, units[currentTime.Minute - 10]);
        strcat(mnLine1, plus);
        strcpy(mnLine2, teen); //teen
      } else {
        if (currentTime.Minute % 10 > 0) {
          strcpy(mnLine1, tens[currentTime.Minute / 10]);
          strcpy(mnLine2, units[currentTime.Minute % 10]);
          strcat(mnLine2, plus); // and
        } else {
          strcpy(mnLine1, tens[currentTime.Minute / 10]);
          strcat(mnLine1, plus); // and
          strcpy(mnLine2, minutes); // minutes
        }
      }
      addMark(mnLine1, mnLine2, 5);

      //drawbg
      display.fillScreen(GxEPD_WHITE);

      display.setTextColor(GxEPD_BLACK);
      display.setTextWrap(false);

      // Tests
      //display.drawBitmap(175, 150, epd_bitmap_aleph, 25, 50, GxEPD_BLACK); //test image
      //display.setFont(&frankRuhl_Font);
      //display.setCursor(100, 200 - 5);
      //display.print("~abaruthk");
      //char str[20] = {129, 'A', 'C', 67, 0, 0};
      //display.print(str);

      //drawtime
      int16_t  x1, y1;
      uint16_t w, h;

      display.getTextBounds(hrLine1, 0, 0, &x1, &y1, &w, &h);

      // HOURS
      lines += 1;
      //display.setFont(&FrankRuhlLibre_Regular40pt8b);
      display.setFont(&Assistant_Regular40pt_Font);

      display.getTextBounds(hrLine1, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(display.width() - MARGIN_X - w, lines * Y_ADVANCE + MARGIN_TOP);
      display.print(hrLine1);

      if (strlen(hrLine2) > 0) {
        lines += 1;
        display.getTextBounds(hrLine2, 0, 0, &x1, &y1, &w, &h);
        display.setCursor(display.width() - MARGIN_X - w, lines * Y_ADVANCE + MARGIN_TOP);
        display.print(hrLine2);
      }

      // MINUTES
      lines += 1;
      //display.setFont(&FrankRuhlLibre_Bold40pt8b);
      display.setFont(&Assistant_Bold40pt_Font);

      display.getTextBounds(mnLine1, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(display.width() - MARGIN_X - w, lines * Y_ADVANCE + MARGIN_TOP);
      display.print(mnLine1);
      if (strlen(mnLine2) > 0) {
        lines += 1;
        display.getTextBounds(mnLine2, 0, 0, &x1, &y1, &w, &h);
        display.setCursor(display.width() - MARGIN_X - w, lines * Y_ADVANCE + MARGIN_TOP);
        display.print(mnLine2);
      }

      // VOLTAGE
      int vBatRounded = (int)(100 * getBatteryVoltage());
      display.setFont(&FreeSerifBold9pt7b);
      display.setCursor(4, display.height() - 4);
      display.print(vBatRounded);

      // NTP_SYNC
      if (ntpSyncCounter >= NTP_SYNC_INTERVAL) {
        syncNTP();
        ntpSyncCounter = 0;
      } else {
        ntpSyncCounter++;
      }
    }
};

WatchFace m; //instantiate your watchface

void setup() {
  m.init(); //call init in setup
  randomSeed(m.getBatteryVoltage());
}

void loop() {
  // this should never run, Watchy deep sleeps after init();
}
