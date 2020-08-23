#pragma once

class CMyGame : public CGame
{
	// Define sprites and other instance variables here
	CSprite marble;	// Sample sprite
	CSpriteList redPegs;
	CSpriteList purplePegs;
	CSpriteList bluePegs;

	CSprite bgBlimp;
	CSprite bgYuki;
	CSprite bgAbstract;
	CSprite bgAT;
	CSprite bgSwirl;
	CSprite bgPolka;
	CSprite bgGameOver;
	CSprite bgVictory;
	CSprite bgMainMenu;
	CSprite bgTutorial;
	CSprite sfxIcon;
	CSprite bgmIcon;
	CSprite howToPlay;

	int level = 1;
	int score;
	int hits;
	int marbles;

	CSoundPlayer sfx;
	CSoundPlayer bgm;

	float bgmVolume = 1;

	bool gameOverWin = false;
	bool mapMaker = false;
	bool bgmOn = true;
	bool sfxOn = true;
	bool tutorialScreen = false;

public:
	CMyGame(void);
	~CMyGame(void);

	// Per-Frame Callback Funtions (must be implemented!)
	virtual void OnUpdate();
	virtual void OnDraw(CGraphics* g);

	// Game Life Cycle
	virtual void OnInitialize();
	virtual void OnDisplayMenu();
	virtual void OnStartGame();
	virtual void OnStartLevel(Sint16 nLevel);
	virtual void OnGameOver();
	virtual void OnTerminate();

	// Keyboard Event Handlers
	virtual void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	virtual void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

	// Mouse Events Handlers
	virtual void OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle);
	virtual void OnLButtonDown(Uint16 x,Uint16 y);
	virtual void OnLButtonUp(Uint16 x,Uint16 y);
	virtual void OnRButtonDown(Uint16 x,Uint16 y);
	virtual void OnRButtonUp(Uint16 x,Uint16 y);
	virtual void OnMButtonDown(Uint16 x,Uint16 y);
	virtual void OnMButtonUp(Uint16 x,Uint16 y);
};
