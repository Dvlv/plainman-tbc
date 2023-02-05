#pragma once

enum ChosenUpgrade {
  HEALTH,
  ENERGY,
  BOTH,
};

class UpgradeState {
public:
  UpgradeState();

  // vars
  bool shouldQuit = false;
  ChosenUpgrade chosenUpgrade;
  int highlightedOption = 0;

  // functions
  void draw();
  void update();
};
