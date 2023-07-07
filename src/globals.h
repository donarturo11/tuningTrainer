#ifndef GLOBALS_H
#define GLOBALS_H

#define KEY_NUMBERS 16
#define WHITE 1
#define BLACK 0

#define AFTER_BLACK_STEP 24
#define AFTER_WHITE_STEP (AFTER_BLACK_STEP*2)
#define WHITE_KEY_WIDTH (AFTER_BLACK_STEP*3)
#define BLACK_KEY_WIDTH (AFTER_BLACK_STEP*2)

#define BLACK_KEY_HEIGHT 70
#define WHITE_KEY_HEIGHT (BLACK_KEY_HEIGHT*2)

#define FREQ_MIN 32.00
#define FREQ_MAX 2048.00

#ifdef __OS_WINDOWS__
#define __PATH_SEPARATOR__ "\\"
#else
#define __PATH_SEPARATOR__ "/"
#endif

namespace stk {
class WaveSimple;
class WaveSimpleMixer;
}
class AudioEngine;


#endif // GLOBALS_H
