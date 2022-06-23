#include "Adafruit_FreeTouch.h"
#include <Keyboard.h>

Adafruit_FreeTouch qt_0 = Adafruit_FreeTouch(0, OVERSAMPLE_8, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_1 = Adafruit_FreeTouch(1, OVERSAMPLE_8, RESISTOR_50K, FREQ_MODE_NONE);

void setup() {
    qt_0.begin();
    qt_1.begin();
}

bool pressed[2];
bool lastPressed[2];
int qt[2];

int threshold = 100;
int target = 800;

char mapping[] = { 'z', 'x' };

void loop() {
    // Update values
    qt[0] = qt_0.measure();
    qt[1] = qt_1.measure();

    for (byte x=0; x<2; x++){
        // Set button state based on analog touch value
        if (qt[x] > target && pressed[x] == 0) pressed[x] = 1;
        if (qt[x] < target - threshold && pressed[x] == 1) pressed[x] = 0;

        // Press/release key on state change
        if (lastPressed[x] != pressed[x]){
            if (pressed[x] == 1) Keyboard.press(mapping[x]);
            else Keyboard.release(mapping[x]);
            lastPressed[x] = pressed[x];
        }
        
    }
}
