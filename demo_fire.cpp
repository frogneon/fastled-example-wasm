/* sinelon
 *
 * By: Mark Kriegsman
 *
 * Modified by: Andrew Tuline
 *
 * Date: February 2015
 *
 * This uses the built in beat in FastLED to move a dot back and forth. In this case, it uses two beats added together for more randomness.
 *
 */


#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif 

// Fixed definitions cannot change on the fly.
#define LED_DT 12                                             // Data pin to connect to the strip.
#define LED_CK 11                                             // Clock pin for WS2801 or APA102.
#define COLOR_ORDER BGR                                       // It's GRB for WS2812 and BGR for APA102.
#define LED_TYPE APA102                                       // Using APA102, WS2812, WS2801. Don't forget to modify LEDS.addLeds to suit.

// Global variables can be changed on the fly.
uint8_t max_bright = 128;                                      // Overall brightness definition. It can be changed on the fly.

CRGBPalette16 currentPalette;
CRGBPalette16 targetPalette;
TBlendType    currentBlending;                                // NOBLEND or LINEARBLEND


// Define variables used by the sequences.
uint8_t thisbeat =  23;                                       // Beats per minute for first part of dot.
uint8_t thatbeat =  28;                                       // Combined the above with this one.
uint8_t thisfade =   32;                                       // How quickly does it fade? Lower = slower fade rate.
uint8_t  thissat = 255;                                       // The saturation, where 255 = brilliant colours.
uint8_t  thisbri = 255;                                       // Brightness of a sequence.
int        myhue =   0;

int    thisdelay = 5;


void sinelon(CRGB* leds, uint16_t len) {                                              // a colored dot sweeping back and forth, with fading trails
  int NUM_LEDS = len;
  fadeToBlackBy( leds, NUM_LEDS, thisfade);
  int pos1 = beatsin16(thisbeat,0,NUM_LEDS);
  int pos2 = beatsin16(thatbeat,0,NUM_LEDS);

  leds[(pos1+pos2)/2] += ColorFromPalette(currentPalette, myhue++, thisbri, currentBlending);

} // sinelon()


void sinelon_loop (CRGB* leds, uint16_t len) {

  EVERY_N_MILLISECONDS(100) {
    uint8_t maxChanges = 24; 
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);   // AWESOME palette blending capability.
  }

  EVERY_N_SECONDS(5) {                                        // Change the target palette to a random one every 5 seconds.
    static uint8_t baseC = random8();                         // You can use this as a baseline colour if you want similar hues in the next line.
    targetPalette = CRGBPalette16(CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 192, random8(128,255)), CHSV(random8(), 255, random8(128,255)));
  }

  EVERY_N_MILLISECONDS(thisdelay) {                           // FastLED based non-blocking delay to update/display the sequence.
    sinelon(leds, len);                                                // Call our sequence.
  }


} // sinelon_loop()

int gValue = 0;
void loop(uint32_t t, CRGB* leds, uint16_t len) {
  sinelon_loop(leds, len);
}
void setup(CRGB* leds, uint16_t len) {
  gValue = 10;
  fill_solid( leds, len, CRGB(38, 231, 31));
}
