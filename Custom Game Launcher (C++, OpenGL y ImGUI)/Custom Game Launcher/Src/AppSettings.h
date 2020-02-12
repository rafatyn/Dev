#pragma once

class AppSettings
{
	// Launcher variables
	float gameInitialHorizontalMargin;
	float gameInitialVerticalMargin;
	float gameLineMargin;
	float gameCoverMinSize;
	float gameCoverMargin;
	float gameCoverRatio;
	short gameCoverOrientation;
	short gameCoverBorder;
	short gameNameLength;


	// Launcher variables
	float launcherInitialHorizontalMargin;
	float launcherInitialVerticalMargin;
	float launcherCoverMinSize = 150.0f;
	float launcherCoverMargin;
	float launcherLineMargin;

	void loadCoverConfig(short config)
	{
		switch (config)
		{
		case 0:
			gameInitialHorizontalMargin = 4.5f / 100.0f;
			gameInitialVerticalMargin = 40.0f;
			gameLineMargin = 40.0f;
			gameCoverMinSize = 250.0f;
			gameCoverMargin = 2.5f / 100.0f;
			gameCoverRatio = 1.85f;
			gameCoverOrientation = 0;
			gameCoverBorder = -1;
			gameNameLength = 25;

			launcherInitialHorizontalMargin = 4.5f / 100.0f;
			launcherInitialVerticalMargin = 40.0f;
			launcherCoverMargin = 2.5f / 100.0f;
			launcherLineMargin = 40.0f;
			break;
		case 1:
			gameInitialHorizontalMargin = 4.0f / 100.0f;
			gameInitialVerticalMargin = 40.0f;
			gameLineMargin = 40.0f;
			gameCoverMinSize = 150.0f;
			gameCoverMargin = 2.5f / 100.0f;
			gameCoverRatio = 0.7067f;
			gameCoverOrientation = 1;
			gameCoverBorder = -1;
			gameNameLength = 20;

			launcherInitialHorizontalMargin = 4.0f / 100.0f;
			launcherInitialVerticalMargin = 40.0f;
			launcherCoverMargin = 2.5f / 100.0f;
			launcherLineMargin = 40.0f;
			break;
		case 2:
			gameInitialHorizontalMargin = 0.0f;
			gameInitialVerticalMargin = 0.0f;
			gameLineMargin = 0.0f;
			gameCoverMinSize = 150.0f;
			gameCoverMargin = 0.0f;
			gameCoverRatio = 0.7067f;
			gameCoverOrientation = 1;
			gameCoverBorder = 0;
			gameNameLength = 23;

			launcherInitialHorizontalMargin = 0.0f;
			launcherInitialVerticalMargin = 0.0f;
			launcherCoverMargin = 0.0f;
			launcherLineMargin = 0.0f;
			break;
		default:
			break;
		}
	}

public:
	AppSettings(short coverConfig)
	{
		loadCoverConfig(coverConfig);
	}

	void changeCoverType(short coverConfig)
	{
		loadCoverConfig(coverConfig);
	}

	inline float getGameInitialHorizontalMargin() { return gameInitialHorizontalMargin; }
	inline float getGameInitialVerticalMargin() { return gameInitialVerticalMargin; }
	inline float getGameLineMargin() { return gameLineMargin; }
	inline float getGameCoverMinSize() { return gameCoverMinSize; }
	inline float getGameCoverMargin() { return gameCoverMargin; }
	inline float getGameCoverRatio() { return gameCoverRatio; }
	inline short getGameCoverOrientation() { return gameCoverOrientation; }
	inline short getGameCoverBorder() { return gameCoverBorder; }
	inline short getGameNameLength() { return gameNameLength; }

	inline float* getGameCoverMinSizePointer() { return &gameCoverMinSize; }
	inline float* getLauncherCoverMinSizePointer() { return &launcherCoverMinSize; }

	inline float getLauncherCoverMinSize() { return launcherCoverMinSize; }
	inline float getLauncherInitialHorizontalMargin() { return launcherInitialHorizontalMargin; }
	inline float getLauncherInitialVerticalMargin() { return launcherInitialVerticalMargin; }
	inline float getLauncherCoverMargin() { return launcherCoverMargin; }
	inline float getLauncherLineMargin() { return launcherLineMargin; }
};