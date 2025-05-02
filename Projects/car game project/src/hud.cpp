#include "../include/hud.h"

hud::hud(SDL_Window* window)
{
    this->scoreLabel = new text_label(window, 24); // new keywords are usable only with pointers
    this->highScoreLabel = new text_label(window, 16);
    this->gamePausedLabel = new text_label(window, 36);
    this->exitGameLabel = new text_label(window, 26);
    this->gameOverLabel = new text_label(window, 26);
    this->speedLabel = new text_label(window, 20);
    this->damageLabel = new text_label(window, 20);
    //if scoreLabel was not a pointer I should have done it like this.
    //this->scoreLabel = hud_text_element(window);
}

hud::~hud()
{
    //Cleaning up the resources used through the pointers
    delete this->scoreLabel;
    delete this->highScoreLabel;
    delete this->gamePausedLabel;
    delete this->exitGameLabel;
    delete this->gameOverLabel;
    delete this->speedLabel;
    delete this->damageLabel;
}

void hud::updateScore(int Score)
{
    stringstream scoreText;
    scoreText << "Score: " << Score;
    this->scoreLabel->Update_Text(scoreText.str().c_str(), {255, 255, 255}, 10, 10);
}

void hud::updateHighestScore()
{
    stringstream highscoreText;
    highscoreText << "Highest Score: " << HighScore;
    this->highScoreLabel->Update_Text(highscoreText.str().c_str(), {255, 255, 255}, WINDOW_WIDTH-180, 10);
}

void hud::showGamePausedLabel()
{
    this->gamePausedLabel->Update_Text("Game Paused!", {255, 0, 0}, WINDOW_WIDTH/2-80, 240);
}

void hud::showExitGameDialog()
{
    this->exitGameLabel->Update_Text("Are you sure you want to EXIT GAME? Y/N", {0, 255, 255}, WINDOW_WIDTH/2-180, 150);
}

void hud::showGameOverDialog()
{
    this->gameOverLabel->Update_Text("GAME OVER!", {255, 0, 0}, WINDOW_WIDTH/2-50, 150);
    this->gameOverLabel->Update_Text("The car is wrecked!", {0, 255, 255}, WINDOW_WIDTH/2, 200);
    this->gameOverLabel->Update_Text("Play again? Y/N", {255, 255, 255}, WINDOW_WIDTH+50, 250);
}

void hud::updateSpeedLabel(int speed)
{
    stringstream speedText;
    speedText << speed << "KM/H";
    this->speedLabel->Update_Text(speedText.str().c_str(), {0, 0, 0}, WINDOW_WIDTH-120, WINDOW_HEIGHT-30);
}

void hud::updateDamageLabel(float damage)
{
    stringstream damageText;

    /*
    std::fixed: formats the floating-point number in fixed-point notation.
    std::setprecision(1): limits the number of digits after the decimal point to 1.
    */

    damageText << "Damage: " << std::fixed << std::setprecision(1) << damage << "%";
    this->damageLabel->Update_Text(damageText.str().c_str(), {0, 0, 0}, 10, WINDOW_HEIGHT-30);
}
