

//==========================================================================================================================================
//================== FastLED definitions
typedef uint8_t byte;
typedef int32_t boolean;
int i_dex = 0;
int j_dex = 0;
void setPixel(CRGB* leds, uint16_t len, int Pixel, byte red, byte green, byte blue) {
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
}
//======================================================================

void setAll(CRGB* leds, uint16_t len, byte red, byte green, byte blue) {
  for(int i = 0; i < len; i++ ) {
    setPixel(leds, len, i, red, green, blue);
  }
}             

// used by meteorrain
void fadeToBlack(CRGB* leds, uint16_t len, int ledNo, byte fadeValue) {
   leds[ledNo].fadeToBlackBy( fadeValue );
}


//======================================================================
void meteorRain(uint32_t t, CRGB* leds, uint16_t len,const struct CRGB& c1, const struct CRGB& c2, uint16_t meteorSize, uint16_t meteorTrailDecay, boolean meteorRandomDecay) {  
//   setAll(leds, len, 0,0,0);
  
//   for(int i = 0; i < len+len; i++) {
    i_dex ++;
    if(i_dex >= len){
        i_dex = 0;
    }
     j_dex ++;
    if(j_dex >= len){
        j_dex = 0;
    }
   
   
    // fade brightness all LEDs one step
    for(int j=0; j<len; j++) {
      if( (!meteorRandomDecay) || (random() * 10>2)) {
        fadeToBlack(leds, len, j, meteorTrailDecay );        
      }
    }
   
    // draw meteor
    for(int j = 0; j < meteorSize; j++) {
      if( ( i_dex-j <len) && (i_dex-j>=0) ) {
        setPixel(leds, len, i_dex-j, c1.r, c1.g, c1.b);
      }
    }

    for(int j=0; j<len; j++) {
      if( (!meteorRandomDecay) || (random() * 10>5)) {
        fadeToBlack(leds, len, j, meteorTrailDecay );        
      }
    }
   
    // draw meteor
    for(int j = 0; j < meteorSize; j++) {
      if( ( j_dex-j <len) && (j_dex-j>=0) ) {
        setPixel(leds, len, j_dex-j, c2.r, c2.g, c2.b);
      }
    }

//   }
}
void meteorRain(uint32_t t, CRGB* leds, uint16_t len)
{               
    // fill_solid( leds, len, CRGB(38, 231, 31));
 // meteorRain - Color (red, green, blue), meteor size, trail decay, random trail decay (true/false), speed delay
 meteorRain(t,leds,len, CRGB(175, 231, 248), CRGB(255, 130, 249), len/10, 1, false); 
                                               //  20 for testing 100 leds / 10 for 200 leds?
} 
//======================================================================

//*Animations End*

int gValue = 0;
void loop(uint32_t t, CRGB* leds, uint16_t len) {
    EVERY_N_MILLISECONDS( 1) {
        meteorRain(gValue,leds,len);
  }
  
}
void setup(CRGB* leds, uint16_t len) {
  gValue = 10;
  j_dex = len/3;
  fill_solid( leds, len, CRGB(253, 255, 255));
}
