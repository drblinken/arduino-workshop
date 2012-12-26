#ifndef DICE_H
#define DICE_H

class Die{
public:
  Die(int numberleds, int pins[]);
  void roll();
  void showNumber(int number);

private:
  int* pins;
  int numberleds;
};
#endif
