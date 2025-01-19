#pragma once

enum class Direction
{
    Up,
    Down,
    Left,
    Right
};

enum class ImageId
{
    BlockEmpty = 0,
    BlockI,
    BlockJ,
    BlockL,
    BlockO,
    BlockS,
    BlockT,
    BlockZ,
    Boundary,
    StatusLines,
    StatusLevel,
    StatusScore,
    StatusNext,
    Digits,
    Logo,
    Count // Count of ImageId entries
};