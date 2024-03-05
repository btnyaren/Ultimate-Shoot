#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
#include "Entity.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include <vector>
#include "Bullet.hpp"
#include "Collision.hpp"
#include "ParticleSystem.hpp"
#include "ParticleExample.hpp"
#include <fstream>
#include <Windows.h>
#include <lmcons.h>
#include <shlwapi.h>
#pragma comment(lib,"shlwapi.lib")
#include "shlobj.h"
#include <tchar.h>
#include <conio.h>
#include <sys/stat.h>



#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

class Game
{
public:
	
	static bool running;

	static SDL_Window* window;
	static SDL_Renderer* renderer;
	


	static void startEngine();
	
	
	//other vars
	static int playerPositions[14];
	static std::vector<Enemy> enemyList;
	static std::vector<Bullet> bulletList;
	static std::vector<Particle> particleList;
	static int maxEnemies;
	static Uint32 EnemySpawnTimeout;
	static int Ammo;
	static int maxAmmo;
	static Uint32 PlayerFireDelay;
	static bool enableShoot;
	static int score;
	static int gameSpeed;
	static bool isGameOver;


	//entities
	static Player* player;


	//texts
	static SDL_Color ScoreTextColor;
	static SDL_Texture* ScoreTextTexture;
	static SDL_Rect ScoreTextDest;

	static SDL_Color ScoreIntTextColor;
	static SDL_Texture* ScoreIntTextTexture;
	static SDL_Rect ScoreIntTextDest;


	static SDL_Color AmmoTextColor;
	static SDL_Texture* AmmoTextTexture;
	static SDL_Rect AmmoTextDest;

	static SDL_Color AmmoIntTextColor;
	static SDL_Texture* AmmoIntTextTexture;
	static SDL_Rect AmmoIntTextDest;


	static SDL_Color GameOverTextColor;
	static SDL_Texture* GameOverTextTexture;
	static SDL_Rect GameOverTextDest;
	
	//system
	static std::string savePath;
	static std::ofstream saveFile;

private:
	//main functs
	static void Init();
	static void Update();
	static void HandleEvent();
	static void Clean();


	//game events
	static void SpawnEnemy();
	static void PlayerFire();
	static void CheckBulletCollision();
	static void EnemyDeathParticle(Enemy enemy);
	static void UpdateTexts();
	static void DisplayScoreText();
	static void DisplayAmmoText();
	static void GameOver();
	static void DisplayGameOverText();


};

