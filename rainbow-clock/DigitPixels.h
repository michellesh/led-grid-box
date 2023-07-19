#define DIGIT_WIDTH 3  // Each digit is 3 pixels across
#define DIGIT_HEIGHT 5 // Each digit is 5 pixels high

struct DigitPixels {
  bool pixels[DIGIT_HEIGHT][DIGIT_WIDTH];
};

// clang-format off
DigitPixels zero = { { {1,1,1},
                       {1,0,1},
                       {1,0,1},
                       {1,0,1},
                       {1,1,1} } };

DigitPixels one = { { {0,1,0},
                      {1,1,0},
                      {0,1,0},
                      {0,1,0},
                      {1,1,1} } };

DigitPixels two = { { {1,1,1},
                      {0,0,1},
                      {0,1,0},
                      {1,0,0},
                      {1,1,1} } };

DigitPixels three = { { {1,1,1},
                        {0,0,1},
                        {0,1,1},
                        {0,0,1},
                        {1,1,1} } };

DigitPixels four = { { {1,0,1},
                       {1,0,1},
                       {1,1,1},
                       {0,0,1},
                       {0,0,1} } };

DigitPixels five = { { {1,1,1},
                       {1,0,0},
                       {1,1,1},
                       {0,0,1},
                       {1,1,1} } };

DigitPixels six = { { {1,1,0},
                      {1,0,0},
                      {1,1,1},
                      {1,0,1},
                      {1,1,1} } };

DigitPixels seven = { { {1,1,1},
                        {0,0,1},
                        {0,1,0},
                        {0,1,0},
                        {0,1,0} } };

DigitPixels eight = { { {1,1,1},
                        {1,0,1},
                        {1,1,1},
                        {1,0,1},
                        {1,1,1} } };

DigitPixels nine = { { {1,1,1},
                       {1,0,1},
                       {1,1,1},
                       {0,0,1},
                       {0,0,1} } };

DigitPixels digits[] = {zero, one, two, three, four, five, six, seven, eight, nine};
// clang-format on
