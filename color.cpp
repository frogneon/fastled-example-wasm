void loop(uint32_t t, CRGB* leds, uint16_t len) {
  EVERY_N_MILLISECONDS( 20) {
    fill_solid( leds, len, CRGB(ledEntry.color[0]));
  }
}
void setup(CRGB* leds, uint16_t len) {
  fill_solid( leds, len, CRGB(38, 231, 31));
}