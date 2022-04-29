

//==========================================================================================================================================
//================== FastLED definitions
//config for the length of text, max is 10
int segments[10] = {201,153,101,100,0,0,0,0,0,0};
int segCount = 4;

int gValue = 0;
int gCount = 0;
int iIndex[10] = {0,0,0,0,0,0,0,0,0,0};
int jIndex[10] = {0,0,0,0,0,0,0,0,0,0};

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
void meteorRain(uint32_t t, CRGB* leds, uint16_t len,const struct CRGB& c1, const struct CRGB& c2, uint16_t meteorSize, uint16_t meteorTrailDecay, boolean meteorRandomDecay, int* jIndex, int* iIndex) {  
//   setAll(leds, len, 0,0,0);
  
//   for(int i = 0; i < len+len; i++) {
    (*iIndex) ++;
    if((*iIndex) >= len){
        (*iIndex) = 0;
    }
     (*jIndex) ++;
    if((*jIndex) >= len){
        (*jIndex) = 0;
    }
   
   
    // fade brightness all LEDs one step
    for(int j=0; j<len; j++) {
      if( (!meteorRandomDecay) || (random() * 10>2)) {
        fadeToBlack(leds, len, j, meteorTrailDecay );        
      }
    }
   
    // draw meteor
    for(int j = 0; j < meteorSize; j++) {
      if( ( (*iIndex)-j <len) && ((*iIndex)-j>=0) ) {
        setPixel(leds, len, (*iIndex)-j, c1.r, c1.g, c1.b);
      }
    }

    for(int j=0; j<len; j++) {
      if( (!meteorRandomDecay) || (random() * 10>5)) {
        fadeToBlack(leds, len, j, meteorTrailDecay );        
      }
    }
   
    // draw meteor
    for(int j = 0; j < meteorSize; j++) {
      if( ( (*jIndex)-j <len) && ((*jIndex)-j>=0) ) {
        setPixel(leds, len, (*jIndex)-j, c2.r, c2.g, c2.b);
      }
    }

//   }
}
void meteorRainLoop(uint32_t t, CRGB* leds, uint16_t len, int* jIndex, int* iIndex)
{               
    // fill_solid( leds, len, CRGB(38, 231, 31));
 // meteorRain - Color (red, green, blue), meteor size, trail decay, random trail decay (true/false), speed delay
 meteorRain(t,leds,len, CRGB(175, 231, 248), CRGB(255, 130, 249), len/10, 1, true, jIndex, iIndex); 
                                               //  20 for testing 100 leds / 10 for 200 leds?
} 
//======================================================================

//*Animations End*


void loop(uint32_t t, CRGB* leds, uint16_t len) {
    EVERY_N_MILLISECONDS( 20) {
        meteorRainLoop(gValue,leds,segments[0],&(jIndex[0]), &(iIndex[0]));//first
        int offset = 0;
        for(gCount = 1; gCount<segCount; gCount++){
            offset = offset + segments[gCount-1];
            meteorRainLoop(gValue,&(leds[offset]),segments[gCount],&(jIndex[gCount]),&(iIndex[gCount])); // others
        }
        
  }
  
}
void setup(CRGB* leds, uint16_t len) {
  gValue = 10;
  for(gCount = 0; gCount<segCount; gCount ++){
      iIndex[gCount] = 0;
      jIndex[gCount] = segments[gCount]/3;
  }
  fill_solid( leds, len, CRGB(0, 0, 0));
}
