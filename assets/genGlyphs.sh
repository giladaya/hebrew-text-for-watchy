#!/bin/bash

# Generate bitmap glyphs from given font for supplied char code range
# Make sure the TTF file is in the same library
#
# To manually generate single glyphs use this command:
# convert -background none -fill black -font FrankRuhlLibre-Regular.ttf -pointsize 50 label:"ת" -colorspace gray -depth 1 154.png
fontFile=FrankRuhlLibre-Bold.ttf
fontSize=44

# First latin
for i in $(seq 32 127); 
  do convert -background white -fill black -font $fontFile -pointsize $fontSize label:"$(printf \\$(printf '%03o' $[$i]))" -colorspace gray -depth 1 ${i}.png
done;

# Now Hebrew
convert -background white -fill black -font $fontFile -pointsize $fontSize label:"א" -colorspace gray -depth 1 128.png
convert -background white -fill black -font $fontFile -pointsize $fontSize label:"ב" -colorspace gray -depth 1 129.png
convert -background white -fill black -font $fontFile -pointsize $fontSize label:"ג" -colorspace gray -depth 1 130.png
convert -background white -fill black -font $fontFile -pointsize $fontSize label:"ד" -colorspace gray -depth 1 131.png
convert -background white -fill black -font $fontFile -pointsize $fontSize label:"ה" -colorspace gray -depth 1 132.png
convert -background white -fill black -font $fontFile -pointsize $fontSize label:"ו" -colorspace gray -depth 1 133.png
convert -background white -fill black -font $fontFile -pointsize $fontSize label:"ז" -colorspace gray -depth 1 134.png
convert -background white -fill black -font $fontFile -pointsize $fontSize label:"ח" -colorspace gray -depth 1 135.png
convert -background white -fill black -font $fontFile -pointsize $fontSize label:"ט" -colorspace gray -depth 1 136.png
convert -background white -fill black -font $fontFile -pointsize $fontSize label:"י" -colorspace gray -depth 1 137.png
convert -background white -fill black -font $fontFile -pointsize $fontSize label:"ך" -colorspace gray -depth 1 138.png
convert -background white -fill black -font $fontFile -pointsize $fontSize label:"כ" -colorspace gray -depth 1 139.png
convert -background white -fill black -font $fontFile -pointsize $fontSize label:"ל" -colorspace gray -depth 1 140.png
convert -background white -fill black -font $fontFile -pointsize $fontSize label:"ם" -colorspace gray -depth 1 141.png
convert -background white -fill black -font $fontFile -pointsize $fontSize label:"מ" -colorspace gray -depth 1 142.png
convert -background white -fill black -font $fontFile -pointsize $fontSize label:"ן" -colorspace gray -depth 1 143.png
convert -background white -fill black -font $fontFile -pointsize $fontSize label:"נ" -colorspace gray -depth 1 144.png
convert -background white -fill black -font $fontFile -pointsize $fontSize label:"ס" -colorspace gray -depth 1 145.png
convert -background white -fill black -font $fontFile -pointsize $fontSize label:"ע" -colorspace gray -depth 1 146.png
convert -background white -fill black -font $fontFile -pointsize $fontSize label:"ף" -colorspace gray -depth 1 147.png
convert -background white -fill black -font $fontFile -pointsize $fontSize label:"פ" -colorspace gray -depth 1 148.png
convert -background white -fill black -font $fontFile -pointsize $fontSize label:"ץ" -colorspace gray -depth 1 149.png
convert -background white -fill black -font $fontFile -pointsize $fontSize label:"צ" -colorspace gray -depth 1 150.png
convert -background white -fill black -font $fontFile -pointsize $fontSize label:"ק" -colorspace gray -depth 1 151.png
convert -background white -fill black -font $fontFile -pointsize $fontSize label:"ר" -colorspace gray -depth 1 152.png
convert -background white -fill black -font $fontFile -pointsize $fontSize label:"ש" -colorspace gray -depth 1 153.png
convert -background white -fill black -font $fontFile -pointsize $fontSize label:"ת" -colorspace gray -depth 1 154.png