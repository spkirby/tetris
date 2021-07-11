#pragma once

enum class Direction
{
    None = 0,
    Up = 1,
    Right = 2,
    Down = 3,
    Left = 4
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