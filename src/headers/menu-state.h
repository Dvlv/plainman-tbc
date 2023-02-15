#pragma once

class MenuState {
public:
  MenuState();

  // vars
  bool isFinished;
  int highlightedOption;
  int chosenOption;

  // funcs
  void update();
  void draw();

  void drawHowToPlay();
  void drawCredits();
  void drawButtons();
};
