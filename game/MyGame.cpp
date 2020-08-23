// IMAGE CREDITS-
// --------------
// Marble and peg images: created myself using GIMP
// Main menu background image: created myself using GIMP
// Blimp level background image: ILLUSTRATE - X (https://dribbble.com/shots/1863169-Airship)
// Cat level background image: picture of my own cat, Yuki :)
// Abstract level background image: Jonathan Tipton-King (https://dribbble.com/shots/4167712-Abstract-Render)
// Adventure Time treehouse level background image: Alex Riegert-Waters (https://dribbble.com/shots/2763824-Finn-Jake-s-Treehouse)
// Pink and white swirl level background image: created myself using GIMP
// White polka dots level background image: created myself using GIMP
// SFX on / off icons: Wikimedia (https://commons.wikimedia.org/wiki/File:Speaker_Icon.svg)
//	(off icon is an edited version)
// BGM on / off icons: Iconfinder (https://www.iconfinder.com/icons/172510/music_icon)
//	(off icon is an edited version)


// SOUND EFFECTS AND MUSIC CREDITS-
// --------------------------------
// Hit and fail sounds (beginning notes of Fur Elise): Peter PlutaX - Fur Elise (https://www.youtube.com/watch?v=t3oKcDQCiiw)
//	(fail sounds are the same as hit sounds, just pitched down)
// Game over music: Toms Mucenieks - Dark Fur Elise (https://www.youtube.com/watch?v=aKPqxo_UnLw)
// Victory music: LEAF XCEED Music Division - Fur Elise (https://www.youtube.com/watch?v=1P8-hNp-Wxw)
// Main menu music: ITaaffe - Fur Elise (https://www.youtube.com/watch?v=tdYBpEUXy1U)
// Blimp level background music: Pixelated Quality - Drift Away (https://www.youtube.com/watch?v=AQ-hAlBghJY ... 13:56 - 17:03)
// Cat level background music: C418 - Cat (https://www.youtube.com/watch?v=9lX-hVpvN3E)
// Abstract level background music: NeXsard IsOnFire - I'm just your problem (https://www.youtube.com/watch?v=tacKqHuHjVw)
// Adventure Time treehouse level background music: 8 Bit Universe - Come Along With Me (Island Song) (https://www.youtube.com/watch?v=4XD_AO6vZUo)
// Pink and white swirl level background music: James Roach - The Crystal Gems (https://www.youtube.com/watch?v=94yYC-SFCzs)
// White polka dots level background music: Pixelated Quality - Other Friends (https://www.youtube.com/watch?v=AQ-hAlBghJY ... 6:53 - 8:56)

#include "stdafx.h"
#include "MyGame.h"

CMyGame::CMyGame(void):
	marble(384, 575, "marble.png", 0),
	bgBlimp(400, 300, "bgBlimp.png", 0),
	bgYuki(400, 300, "bgYuki.png", 0),
	bgAbstract(400, 300, "bgAbstract.png", 0),
	bgAT(400, 300, "bgAT.png", 0),
	bgSwirl(400, 300, "bgSwirl.png", 0),
	bgPolka(400, 300, "bgPolka.png", 0),
	bgGameOver(400, 300, "gameOver.png", 0),
	bgVictory(400, 300, "victory.png", 0),
	bgMainMenu(400, 300, "mainMenu.png", 0),
	bgTutorial(400, 300, "tutorialScreen.png", 0),
	sfxIcon(784, 16, "sfxOn.png", 0),
	bgmIcon(752, 16, "bgmOn.png", 0),
	howToPlay(400, 29, "howToPlay.png", 0) {

}

CMyGame::~CMyGame(void) {

}

void CMyGame::OnUpdate() {
	Uint32 t = GetTime();

	if (IsMenuMode() && !tutorialScreen) {
		bgMainMenu.Update(t);
		bgBlimp.Update(t);
		bgYuki.Update(t);
		bgAbstract.Update(t);
		bgAT.Update(t);
		bgSwirl.Update(t);
		bgPolka.Update(t);
		howToPlay.Update(t);
	} else if (IsMenuMode() && tutorialScreen) {
		bgTutorial.Update(t);
	} else if (!IsGameOver()) {
		if (level == 1) bgBlimp.Update(t);
		else if (level == 2) bgYuki.Update(t);
		else if (level == 3) bgAbstract.Update(t);
		else if (level == 4) bgAT.Update(t);
		else if (level == 5) bgSwirl.Update(t);
		else if (level == 6) bgPolka.Update(t);

		// pegs
		for (CSprite* peg : redPegs) {
			CVector v = marble.GetVelocity();
			CVector d = marble.GetPosition() - peg->GetPosition();
			if (Length(d) < 32 && Dot(v, d) < 0) {
				marble.SetVelocity(Reflect(marble.GetVelocity(), Normalise(marble.GetPosition() - peg->GetPosition())));
				marble.SetYVelocity(marble.GetYVelocity() / 1.3);
				peg->SetProperty("frames", (int)peg->GetProperty("frames") + 1);
				if ((int)peg->GetProperty("frames") == 1) {
					score += 500;
					if (++hits > 17) hits = 1;
					if (sfxOn) sfx.Play("hit" + to_string(hits) + ".wav");
					peg->SetImageFromFile("redPegHit.png");
				}
			}
			if ((int)peg->GetProperty("frames") > 30) {
				peg->Delete();
			}
			peg->Update(t);
		};
		redPegs.delete_if(deleted);

		for (CSprite* peg : purplePegs) {
			CVector v = marble.GetVelocity();
			CVector d = marble.GetPosition() - peg->GetPosition();
			if (Length(d) < 32 && Dot(v, d) < 0) {
				marble.SetVelocity(Reflect(marble.GetVelocity(), Normalise(marble.GetPosition() - peg->GetPosition())));
				marble.SetYVelocity(marble.GetYVelocity() / 1.3);
				peg->SetProperty("frames", (int)peg->GetProperty("frames") + 1);
				if ((int)peg->GetProperty("frames") == 1) {
					score += 1000;
					if (++hits > 17) hits = 1;
					if (sfxOn) sfx.Play("hit" + to_string(hits) + ".wav");
					peg->SetImageFromFile("purplePegHit.png");
				}
			}
			if ((int)peg->GetProperty("frames") > 30) {
				peg->Delete();
			}
			peg->Update(t);
		};
		purplePegs.delete_if(deleted);

		for (CSprite* peg : bluePegs) {
			CVector v = marble.GetVelocity();
			CVector d = marble.GetPosition() - peg->GetPosition();
			if (Length(d) < 32 && Dot(v, d) < 0) {
				marble.SetVelocity(Reflect(marble.GetVelocity(), Normalise(marble.GetPosition() - peg->GetPosition())));
				marble.SetYVelocity(marble.GetYVelocity() / 1.3);
				peg->SetProperty("frames", (int)peg->GetProperty("frames") + 1);
				if ((int)peg->GetProperty("frames") == 1) {
					score += 100;
					if (++hits > 17) hits = 1;
					if (sfxOn) sfx.Play("hit" + to_string(hits) + ".wav");
					peg->SetImageFromFile("bluePegHit.png");
				}
			}
			if ((int)peg->GetProperty("frames") > 30) {
				peg->Delete();
			}
			peg->Update(t);
		};
		bluePegs.delete_if(deleted);

		// marble
		if (marble.GetX() < marble.GetWidth() / 2) { // left
			marble.SetX(marble.GetWidth() / 2);
			marble.SetVelocity(-marble.GetXVelocity(), marble.GetYVelocity());
		}
		if (marble.GetX() > GetWidth() - marble.GetWidth() / 2) { // right
			marble.SetX(GetWidth() - marble.GetWidth() / 2);
			marble.SetVelocity(-marble.GetXVelocity(), marble.GetYVelocity());
		}
		if (marble.GetY() < -marble.GetHeight() / 2) { // bottom / die / lose marble
			for (CSprite* peg : redPegs) {
				if ((int)peg->GetProperty("frames") > 0) {
					peg->Delete();
				}
			}
			redPegs.delete_if(deleted);

			for (CSprite* peg : bluePegs) {
				if ((int)peg->GetProperty("frames") > 0) {
					peg->Delete();
				}
			}
			bluePegs.delete_if(deleted);

			for (CSprite* peg : purplePegs) {
				if ((int)peg->GetProperty("frames") > 0) {
					peg->Delete();
				}
			}
			purplePegs.delete_if(deleted);

			if (redPegs.size() == 0) {
				marble.SetSpeed(0);
				gameOverWin = true;
				GameOver();
			} else if (--marbles < 0) {
				marble.SetSpeed(0);
				gameOverWin = false;
				GameOver();
			} else {
				if (++hits > 17) hits = 1;
				if (sfxOn) sfx.Play("fail" + to_string(hits) + ".wav");
				hits = 0;
				marble.SetSpeed(0);
				marble.SetPosition(384, 575);
			}
		}
		if (marble.GetY() > GetHeight() - marble.GetHeight() / 2) { // top
			marble.SetY(GetHeight() - marble.GetHeight() / 2);
			marble.SetVelocity(marble.GetXVelocity(), -marble.GetYVelocity());
		}

		// MAP EDITING (COMMENT OUT)
		if (!mapMaker && marble.GetSpeed() != 0) marble.Accelerate(0, -10);

		marble.SetOmega(marble.GetXVelocity() * 2);

		marble.Update(t);
	} else {
		bgGameOver.Update(t);
	}

	sfxIcon.Update(t);
	bgmIcon.Update(t);
}

void CMyGame::OnDraw(CGraphics* g) {
	if (IsMenuMode() && !tutorialScreen) {
		bgMainMenu.Draw(g);
		bgBlimp.Draw(g);
		bgYuki.Draw(g);
		bgAbstract.Draw(g);
		bgAT.Draw(g);
		bgSwirl.Draw(g);
		bgPolka.Draw(g);
		howToPlay.Draw(g);
	} else if (IsMenuMode() && tutorialScreen) {
		bgTutorial.Draw(g);
	} else if (!IsGameOver()) {
		if (level == 1) bgBlimp.Draw(g);
		else if (level == 2) bgYuki.Draw(g);
		else if (level == 3) bgAbstract.Draw(g);
		else if (level == 4) bgAT.Draw(g);
		else if (level == 5) bgSwirl.Draw(g);
		else if (level == 6) bgPolka.Draw(g);

		for (CSprite* peg : redPegs) peg->Draw(g);
		for (CSprite* peg : purplePegs) peg->Draw(g);
		for (CSprite* peg : bluePegs) peg->Draw(g);
		marble.Draw(g);

		// this will print the game time
		//*g << bottom << left << "Time elapsed: " << timetext(GetTime());

		// MAP EDITING
		if (mapMaker) *g << bottom << left << marble.GetX() << ", " << marble.GetY();
	} else {
		if (!gameOverWin) bgGameOver.Draw(g);
		else bgVictory.Draw(g);
	}

	if (!IsMenuMode()) {
		if (IsGameOver()) {
			if (gameOverWin) *g << color(CColor::LightGreen());
			else *g << color(CColor::LightRed());
		} else if (IsGameMode()) {
			if (level == 3 || level == 6 || level == 2) *g << color(CColor::White());
			else *g << color(CColor::Black());
		}

		*g << top << left << "Marbles: " << marbles;
		*g << top << right << "Score: " << score;
	}

	sfxIcon.Draw(g);
	bgmIcon.Draw(g);
}

void CMyGame::OnInitialize() {

}

void CMyGame::OnDisplayMenu() {
	if (bgmOn) bgm.Play("mainMenu.wav", -1);
	bgm.Volume(1);
	bgmVolume = 1;

	bgBlimp.SetSize(200, 150);
	bgBlimp.SetPosition(135, 417);

	bgYuki.SetSize(200, 150);
	bgYuki.SetPosition(401, 417);

	bgAbstract.SetSize(200, 150);
	bgAbstract.SetPosition(666, 417);

	bgAT.SetSize(200, 150);
	bgAT.SetPosition(135, 182);

	bgSwirl.SetSize(200, 150);
	bgSwirl.SetPosition(401, 182);

	bgPolka.SetSize(200, 150);
	bgPolka.SetPosition(666, 182);
}

// called when a new game is started
// as a second phase after a menu or a welcome screen
void CMyGame::OnStartGame() {
	bgBlimp.SetSize(800, 600);
	bgBlimp.SetPosition(400, 300);

	bgYuki.SetSize(800, 600);
	bgYuki.SetPosition(400, 300);

	bgAbstract.SetSize(800, 600);
	bgAbstract.SetPosition(400, 300);

	bgAT.SetSize(800, 600);
	bgAT.SetPosition(400, 300);

	bgSwirl.SetSize(800, 600);
	bgSwirl.SetPosition(400, 300);

	bgPolka.SetSize(800, 600);
	bgPolka.SetPosition(400, 300);

	hits = 0;
	score = 0;
	redPegs.clear();
	purplePegs.clear();
	bluePegs.clear();
	marble.SetSpeed(0);
	marble.SetPosition(384, 575);
	marble.SetVelocity(0, 0);

	if (level == 3) marbles = 12;
	else if (level == 4) marbles = 11;
	else if (level == 6) marbles = 6;
	else marbles = 10;

	vector<CVector> pegs;
	int x, y;
	fstream file;
	file.open("level" + to_string(level) + ".txt");
	bool notEOF;
	Uint32 t = GetTime();
	do {
		file >> x >> y;
		notEOF = file.good();
		if (notEOF) {
			pegs.push_back(CVector(x, y));
		}
	} while (notEOF);
	file.close();

	// shuffle pegs (FISHER-YATES SHUFFLE)
	int n = pegs.size();
	for (int i = 0; i < n - 1; i++) {
		int j = i + rand() % (n - i);
		swap(pegs[i], pegs[j]);
	}

	n = pegs.size();
	int nPurple = (float)n / 100 * 5;
	int nRed = (float)n / 100 * 25;
	for (int i = 0; i < n; i++) {
		if (nPurple > 0) {
			CSprite* peg = new CSprite(pegs[i], "purplePeg.png", t);
			peg->AddProperty("frames", 0);
			peg->Rotate(rand() % 360);
			purplePegs.push_back(peg);
			nPurple--;
		} else if (nRed > 0) {
			CSprite* peg = new CSprite(pegs[i], "redPeg.png", t);
			peg->AddProperty("frames", 0);
			peg->Rotate(rand() % 360);
			redPegs.push_back(peg);
			nRed--;
		} else {
			CSprite* peg = new CSprite(pegs[i], "bluePeg.png", t);
			peg->AddProperty("frames", 0);
			peg->Rotate(rand() % 360);
			bluePegs.push_back(peg);
		}
	}
}

// called when a new level started - first call for nLevel = 1
void CMyGame::OnStartLevel(Sint16 nLevel) {

}

// called when the game is over
void CMyGame::OnGameOver() {
	if (!gameOverWin) {
		bgm.Play("gameOver.wav", -1);
		if (bgmOn) bgm.Volume(1);
		bgmVolume = 1;
	}
	else {
		bgm.Play("victory.wav", -1);
		if (bgmOn) bgm.Volume(0.75);
		bgmVolume = 0.75;
	}
}

// one time termination code
void CMyGame::OnTerminate() {

}

void CMyGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
	if (IsMenuMode() && sym == SDLK_INSERT) {
		mapMaker = true;
		level = 6;
		StartGame();
	}
	if (sym == SDLK_F4 && (mod & (KMOD_LALT | KMOD_RALT)))
		StopGame();
	if (sym == SDLK_SPACE)
		PauseGame();
	if (sym == SDLK_F2)
		NewGame();
}

void CMyGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {

}

void CMyGame::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle) {
	if (bgmIcon.HitTest(x, y) || sfxIcon.HitTest(x, y)) SetCursor(LoadCursor(NULL, IDC_HAND));

	if (IsMenuMode() && !tutorialScreen) {
		if (bgBlimp.HitTest(x, y) ||
			bgYuki.HitTest(x, y) ||
			bgAbstract.HitTest(x, y) ||
			bgAT.HitTest(x, y) ||
			bgSwirl.HitTest(x, y) ||
			bgPolka.HitTest(x, y) ||
			howToPlay.HitTest(x, y))
				SetCursor(LoadCursor(NULL, IDC_HAND));
	}
}

void CMyGame::OnLButtonDown(Uint16 x,Uint16 y) {
	if (bgmIcon.HitTest(x, y)) {
		bgmOn = !bgmOn;
		if (bgmOn) {
			bgm.Volume(bgmVolume);
			bgmIcon.SetImageFromFile("bgmOn.png");
		} else {
			bgmIcon.SetImageFromFile("bgmOff.png");
			bgm.Volume(0);
		}
		return;
	}
	if (sfxIcon.HitTest(x, y)) {
		sfxOn = !sfxOn;
		if (sfxOn) {
			sfxIcon.SetImageFromFile("sfxOn.png");
			sfx.Volume(1);
		} else {
			sfxIcon.SetImageFromFile("sfxOff.png");
			sfx.Volume(0);
		}
		return;
	}
	if (IsMenuMode() && !tutorialScreen) {
		// LEVEL SELECT
		if (bgBlimp.HitTest(x, y)) {
			level = 1;
			bgm.Play("bgmBlimp.wav", -1);
			if (bgmOn) bgm.Volume(0.5);
			bgmVolume = 0.5f;
		} else if (bgYuki.HitTest(x, y)) {
			level = 2;
			bgm.Play("bgmYuki.wav", -1);
			if (bgmOn) bgm.Volume(0.5);
			bgmVolume = 0.5f;
		} else if (bgAbstract.HitTest(x, y)) {
			level = 3;
			bgm.Play("bgmAbstract.wav", -1);
			if (bgmOn) bgm.Volume(0.15);
			bgmVolume = 0.15f;
		} else if (bgAT.HitTest(x, y)) {
			level = 4;
			bgm.Play("bgmAT.wav", -1);
			if (bgmOn) bgm.Volume(0.1);
			bgmVolume = 0.1f;
		} else if (bgSwirl.HitTest(x, y)) {
			level = 5;
			bgm.Play("bgmSwirl.wav", -1);
			if (bgmOn) bgm.Volume(0.1);
			bgmVolume = 0.1f;
		} else if (bgPolka.HitTest(x, y)) {
			level = 6;
			bgm.Play("bgmPolka.wav", -1);
			if (bgmOn) bgm.Volume(0.5);
			bgmVolume = 0.5f;
		} else if (howToPlay.HitTest(x, y)) {
			tutorialScreen = true;
			return;
		} else return;

		StartGame();
	} else if (IsMenuMode() && tutorialScreen) {
		tutorialScreen = false;
	} else if (IsGameOver()) {
		gameOverWin = false;
		NewGame();
	} else if (marble.GetSpeed() == 0 && marble.GetPosition() == CVector(384, 575)) {
		// MAP EDITING (COMMENT OUT)
		if (!mapMaker) {
			marble.SetVelocity(x - marble.GetX(), y - marble.GetY());
			marble.SetSpeed(450);
		}
	}
	
	// MAP EDITING
	if (mapMaker) marble.SetPosition(x, y);
}

void CMyGame::OnLButtonUp(Uint16 x,Uint16 y) {

}

void CMyGame::OnRButtonDown(Uint16 x,Uint16 y) {
	// MAP EDITING
	if (mapMaker && IsGameMode()) {
		CSprite* peg = new CSprite(marble.GetX(), marble.GetY(), "bluePeg.png", GetTime());
		bluePegs.push_back(peg);
	}
}

void CMyGame::OnRButtonUp(Uint16 x,Uint16 y) {

}

void CMyGame::OnMButtonDown(Uint16 x,Uint16 y) {

}

void CMyGame::OnMButtonUp(Uint16 x,Uint16 y) {

}
