#define DIGIT_WIDTH 3  // Each digit is 3 pixels across
#define DIGIT_HEIGHT 5 // Each digit is 5 pixels high

struct Digit {
  bool pixels[DIGIT_HEIGHT][DIGIT_WIDTH];
  bool showPixel(int x, int y) {
    // The LEDGrid x/y coordinates start at the bottom left, but these numbers
    // are defined starting at the top. They are also defined by row first and
    // then by column, rather than the standard (x, y) (col, row)
    return pixels[DIGIT_HEIGHT - y - 1][x];
  }
};

// clang-format off
Digit zero = { { {1,1,1},
                 {1,0,1},
                 {1,0,1},
                 {1,0,1},
                 {1,1,1} } };

Digit one = { { {0,1,0},
                {1,1,0},
                {0,1,0},
                {0,1,0},
                {1,1,1} } };

Digit two = { { {1,1,1},
                {0,0,1},
                {0,1,0},
                {1,0,0},
                {1,1,1} } };

Digit three = { { {1,1,1},
                  {0,0,1},
                  {0,1,1},
                  {0,0,1},
                  {1,1,1} } };

Digit four = { { {1,0,1},
                 {1,0,1},
                 {1,1,1},
                 {0,0,1},
                 {0,0,1} } };

Digit five = { { {1,1,1},
                 {1,0,0},
                 {1,1,1},
                 {0,0,1},
                 {1,1,1} } };

Digit six = { { {1,1,0},
                {1,0,0},
                {1,1,1},
                {1,0,1},
                {1,1,1} } };

Digit seven = { { {1,1,1},
                  {0,0,1},
                  {0,1,0},
                  {0,1,0},
                  {0,1,0} } };

Digit eight = { { {1,1,1},
                  {1,0,1},
                  {1,1,1},
                  {1,0,1},
                  {1,1,1} } };

Digit nine = { { {1,1,1},
                 {1,0,1},
                 {1,1,1},
                 {0,0,1},
                 {0,0,1} } };

Digit digits[] = {zero, one, two, three, four, five, six, seven, eight, nine};
// clang-format on
