#ifndef ENUMS_H
#define ENUMS_H

enum ImageId
{
    BLOCK_EMPTY = 0, // Must be zero
    BLOCK_I,
    BLOCK_J,
    BLOCK_L,
    BLOCK_O,
    BLOCK_S,
    BLOCK_T,
    BLOCK_Z,
    BOUNDARY,
    STATUS_LINES,
    STATUS_LEVEL,
    STATUS_SCORE,
    STATUS_NEXT,
    DIGITS,
    LOGO,
    NUM_OF_IMAGES
};

enum SoundId
{
    THUD = 0,
    ROTATE,
    LINE,
    START,
    GAMEOVER,
    NUM_OF_SOUNDS
};

#endif // ENUMS_H