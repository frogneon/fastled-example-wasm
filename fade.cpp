static CRGBPalette16 fadein_currentPalette = PartyColors_p;
static CRGBPalette16 targetPalette;
static TBlendType    fadein_currentBlending = LINEARBLEND;                  // NOBLEND or LINEARBLEND
int speed = 10;
void my_loop(uint32_t t, CRGB* leds, uint16_t len) {
    EVERY_N_MILLISECONDS( t) {
        EVERY_N_MILLISECONDS(100 * speed) {                                                 // FastLED based non-blocking FIXED delay.
        uint8_t maxChanges = 24;
        nblendPaletteTowardPalette(fadein_currentPalette, targetPalette, maxChanges);    // AWESOME palette blending capability.
        }

        EVERY_N_SECONDS(5 * speed) {                                                        // Change the target palette to a random one every 5 seconds.
        uint8_t baseC = random8(255);                                             // Use the built-in random number generator as we are re-initializing the FastLED one.
        targetPalette = CRGBPalette32(CHSV(baseC+random8(0,32), 255, random8(128, 255)), CHSV(baseC+random8(0,32), 255, random8(128, 255)), CHSV(baseC+random8(0,32), 192, random8(128, 255)), CHSV(baseC+random8(0,32), 255, random8(128, 255)));
        }
        random16_set_seed(535);                                                           // The randomizer needs to be re-set each time through the loop in order for the 'random' numbers to be the same each time through.

        for (int i = 0; i<len; i++) {
            uint8_t fader = sin8(millis()/random8(10,20));                                  // The random number for each 'i' will be the same every time.
            leds[i] = ColorFromPalette(fadein_currentPalette, i*20, fader, fadein_currentBlending);       // Now, let's run it through the palette lookup.
        }

        random16_set_seed(millis());
        // pacifica_loop(t, leds, len);
    }
}

int gValue = 0;
void loop(uint32_t t, CRGB* leds, uint16_t len) {
  EVERY_N_MILLISECONDS( 20) {
    my_loop(gValue, leds, len);
  }
}
void setup(CRGB* leds, uint16_t len) {
  gValue = 10;
  fill_solid( leds, len, CRGB(38, 231, 31));
}
