#pragma once

#define PREMADE_SCREEN_WIDTH 768.0f
#define PREMADE_SCREEN_HEIGHT 1024.0f
#define DEFAULT_SCREEN_WIDTH 650.0f
#define DEFAULT_SCREEN_HEIGHT DEFAULT_SCREEN_WIDTH*(PREMADE_SCREEN_HEIGHT/PREMADE_SCREEN_WIDTH)
#define SCREEN_SCALE_WIDTH DEFAULT_SCREEN_WIDTH/PREMADE_SCREEN_WIDTH
#define SCREEN_SCALE_HEIGHT DEFAULT_SCREEN_HEIGHT/PREMADE_SCREEN_HEIGHT

#define SPLASH_SHOW_TIME 1.0f
#define SPLASH_PATH "Resources/res/Splash Background.png"

#define MAIN_MENU_PATH "Resources/res/sky.png"
#define GAME_TITLE_FILEPATH "Resources/res/title.png"
#define GAME_BACKGROUND_PATH "Resources/res/sky.png"
#define PLAY_BUTTON_FILEPATH "Resources/res/PlayButton.png"
#define VOLUME_ON_FILEPATH "Resources/res/volume-on.png"
#define VOLUME_OFF_FILEPATH "Resources/res/volume-off.png"
#define EFFECTS_ON_FILEPATH "Resources/res/effects-on.png"
#define EFFECTS_OFF_FILEPATH "Resources/res/effects-off.png"

#define GAME_OVER_BACKGROUND_PATH "Resources/res/sky.png"
#define GAME_OVER_TITLE_FILEPATH "Resources/res/Game-Over-Title.png"
#define GAME_OVER_BODY_FILEPATH "Resources/res/Game-Over-Body.png"
#define HIHG_SCORE_FILEPATH "Resources/HighScore.txt"
#define TIME_BEFORE_GAME_OVER 1.5f
#define BRONZE_GAME_OVER_MEDAL "Resources/res/Bronze-Medal.png"
#define SILVER_GAME_OVER_MEDAL "Resources/res/Silver-Medal.png"
#define GOLD_GAME_OVER_MEDAL "Resources/res/Gold-Medal.png"
#define PLATINUM_GAME_OVER_MEDAL "Resources/res/Platinum-Medal.png"
#define BRONZE_MEDAL_SCORE 0
#define SILVER_MEDAL_SCORE 5
#define GOLD_MEDAL_SCORE 25
#define PLATINUM_MEDAL_SCORE 100

#define LAND_FILEPATH "Resources/res/Land.png"
#define FLOOR_MOVEMENT_SPEED 2.0f

#define PIPE_MOVEMENT_SPEED 200.0f
#define PIPE_SPAWN_FRECUENCY 2.0f
#define PIPE_UP_FILEPATH "Resources/res/PipeUp.png"
#define PIPE_DOWN_FILEPATH "Resources/res/PipeDown.png"
#define PIPE_SCORING_FILEPATH "Resources/res/InvisibleScoringPipe.png"

#define BIRD_ANIMATION_DURATION 0.6f
#define BIRD_STATE_STILL 1
#define BIRD_STATE_FALLING 2
#define BIRD_STATE_FLYING 3
#define BIRD_FRAME1_FILEPATH "Resources/res/bird-01.png"
#define BIRD_FRAME2_FILEPATH "Resources/res/bird-02.png"
#define BIRD_FRAME3_FILEPATH "Resources/res/bird-03.png"
#define BIRD_FRAME4_FILEPATH "Resources/res/bird-04.png"
#define FLYING_SPEED 250.0f
#define FLYING_DURATION 0.3f
#define ROTATION_SPEED 100.0f
#define GRAVITY 350.0f

#define FLASH_SPEED 1500.0f

#define FLAPPY_FONT_FILEPATH "Resources/fonts/FlappyFont.ttf"

#define HIT_SOUND_FILEPATH "Resources/audio/Hit.wav"
#define POINT_SOUND_FILEPATH "Resources/audio/Point.wav"
#define WING_SOUND_FILEPATH "Resources/audio/Wing.wav"
#define AMBIENT_SOUND_FILEPATH "Resources/audio/Ambient music.wav"

enum GameStates { eReady, ePlaying, eGameOver };