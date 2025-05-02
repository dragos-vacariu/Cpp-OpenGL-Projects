#ifndef HUD_H
#define HUD_H

//Classes inclusion:
#include "../include/text_label.h"

class hud
{
    public:
        hud(SDL_Window* window);
        virtual ~hud();

        //Public Functions:
        void updateScore(int Score);
        void updateHighestScore();
        void showGamePausedLabel();
        void showExitGameDialog();
        void showGameOverDialog();
        void updateSpeedLabel(int speed);
        void updateDamageLabel(float damage);

    protected:

    private:
        //Private variables:
        text_label* scoreLabel;
        text_label* highScoreLabel;
        text_label* gamePausedLabel;
        text_label* exitGameLabel;
        text_label* gameOverLabel;
        text_label* speedLabel;
        text_label* damageLabel;
};

#endif // GAME_HUD_H
