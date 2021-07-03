# Hebrew Text for Watchy
A bit hacky implementation of RTL Hebrew text watchface for [Watchy](https://watchy.sqfmi.com/).

![Photo1](photo1.jpg)

## Creating new fonts
1. Download a ttf file
2. Place it in fontUtils
3. Update file name and desired size in `genGlyphs.sh`
4. All glyph image files will be created
5. Open `font-creator.html` in a web browser
6. Load all glyphs, adjust codes range, adjust `Identifier/Prefix`
7. Click `Generate code`
8. Copy generated code nto a new `*.h` file
9. Import the new file into the sketch and use normally
