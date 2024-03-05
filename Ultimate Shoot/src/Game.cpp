#include "../include/Game.hpp"
#include "../include/Randomer.hpp"


SDL_Window* Game::window = NULL;
SDL_Renderer* Game::renderer = NULL;
bool Game::running = false;
SDL_Event event;

Player* Game::player = new Player();

int Game::playerPositions[14] = { 0, 60, 120, 180, 240, 300, 360, 420, 480, 540, 600, 660, 720, 735 };

std::vector<Enemy> Game::enemyList;
std::vector<Bullet> Game::bulletList;
std::vector<Particle> Game::particleList;

int Game::maxEnemies = 6;

Uint32 Game::EnemySpawnTimeout = 3;

int Game::Ammo = 10;
int Game::maxAmmo = 10;

Uint32 Game::PlayerFireDelay = 400;

bool Game::enableShoot = false;

SDL_Color Game::ScoreTextColor = {255, 255, 255};
SDL_Texture* Game::ScoreTextTexture;
SDL_Rect Game::ScoreTextDest;

SDL_Color Game::ScoreIntTextColor = {255, 255, 255};
SDL_Texture* Game::ScoreIntTextTexture;
SDL_Rect Game::ScoreIntTextDest;


SDL_Color Game::AmmoTextColor = { 255, 255, 255 };
SDL_Texture* Game::AmmoTextTexture;
SDL_Rect  Game::AmmoTextDest;

SDL_Color  Game::AmmoIntTextColor = { 255, 255, 255 };
SDL_Texture* Game::AmmoIntTextTexture;
SDL_Rect  Game::AmmoIntTextDest;


SDL_Color Game::GameOverTextColor = {255, 10, 30};
SDL_Texture* Game::GameOverTextTexture;
SDL_Rect Game::GameOverTextDest;

int Game::score = 0;

int Game::gameSpeed = 3;


bool Game::isGameOver = false;


std::string Game::savePath;
std::ofstream Game::saveFile;

void Game::startEngine()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL FAILED TO INITALIZE";
	}
	
	else
	{
		TTF_Init();
		window = SDL_CreateWindow("ULTIMATE SHOOT", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

		if (!window)
		{
			std::cout << "WINDOW FAILED TO INITALIZE";
		}
		
		else
		{
			renderer = SDL_CreateRenderer(window, -1, 0);
			
			if (!renderer)
			{
				std::cout << "RENDERER FAILED TO INITALIZE";
			}

			else
			{
				SDL_SetRenderDrawColor(renderer, 0,0,0 ,255);

				running = true;
			}
		}
	}

	Init();

	const int FPS = 60;
	const int FrameDelay = 1000 / FPS; //16,666

	Uint32 FrameStart;
	int FrameTime;

	while (running)
	{

		


		FrameStart = SDL_GetTicks();
		Update();
		HandleEvent();

		FrameTime = SDL_GetTicks() - FrameStart;


		if (FrameDelay > FrameTime)
		{
			SDL_Delay(FrameDelay - FrameTime);
		}
	}


	Clean();
}



void Game::Init()
{
	
	player->Init();







	savePath = getenv("appdata");
	std::cout << "appdata=" << savePath << std::endl;
	savePath += "UltimateShoot\Score.txt";
	std::cout << "path=" << savePath << std::endl;

	saveFile.open(savePath.c_str());

	if (saveFile)
	{
		std::cout << "VARMIS";
	}

	//saveFile << "test" << std::endl;
	//saveFile.close();


}


void Game::Update()
{
	SDL_RenderClear(renderer);


	player->Update();


	if (SDL_TICKS_PASSED(SDL_GetTicks(), EnemySpawnTimeout))
	{
		std::cout << "testtt" << std::endl;
		EnemySpawnTimeout += 3000;
		if (maxEnemies > enemyList.size() && isGameOver == false)
		{
			SpawnEnemy();
		}
	}

	for (int i = 0; i < enemyList.size(); i++) {
		enemyList[i].Update();
		enemyList[i].UpdateEnemy();


		if (enemyList[i].y >= 450)
		{
			enemyList.erase(enemyList.begin() + i);

			GameOver();
		}
	}

	
	for (int i = 0; i < bulletList.size(); i++) {
		bulletList[i].Update();
		bulletList[i].UpdateBullet();

		if (bulletList[i].y <= -20)
		{
			bulletList.erase(bulletList.begin() + i);
		}
	}

	
	for (int i = 0; i < particleList.size(); i++) {
		particleList[i].draw();

		
	}

	CheckBulletCollision();
	
	DisplayScoreText();
	DisplayAmmoText();


	if (isGameOver)
	{
		DisplayGameOverText();
	}


	SDL_RenderPresent(renderer);
}


void Game::HandleEvent()
{
	SDL_Event event;
	
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			running = false;
		}
		
		if (event.type == SDL_KEYDOWN && !isGameOver)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_LEFT:

				if (player->x == 735)
				{
					player->x = 700;
				}

				else if (player->x > 40)
				{
					player->x -= 60;
				}

				else
				{
					player->x = 0;
				}
				



				std::cout << player->x << std::endl;
				break;


			case SDLK_RIGHT:
				if (player->x < 700)
				{
					player->x += 60;
				}

				else
				{
					player->x = 735;
				}

				std::cout << player->x << std::endl;


				break;


			case SDLK_UP:
				if (Ammo != 0)
				{
					if (SDL_TICKS_PASSED(SDL_GetTicks(), PlayerFireDelay + 500) && !enableShoot)
					{
						PlayerFire();
						PlayerFireDelay = SDL_GetTicks();
					}

					break;
				}
			}
		}
	}

}


void Game::Clean()
{
	
}



void Game::SpawnEnemy()
{
	Enemy enemy;
	
	
	enemy.y = -65;
	
	enemy.speed = gameSpeed;

	int randomN = Randomer::RandomRangei(1, 14);

	enemy.x = playerPositions[randomN];

	std::cout << randomN << std::endl;

	if (randomN != 13 && randomN != 12)
	{
		enemy.x += 35;
	}
	
	enemy.Init();
	enemyList.push_back(enemy);

}


void Game::PlayerFire()
{
	Bullet bullet;
	
	
	bullet.y = player->y - 25;
	bullet.x = player->x + 26;

	Ammo -= 1; 

	bullet.speed = gameSpeed;
	
	bullet.Init();
	bulletList.push_back(bullet);
}



void Game::CheckBulletCollision()
{


	for (int i = 0; i < enemyList.size(); i++) {
		for (int j = 0; j < bulletList.size(); j++) {
			if (Collision::AABB(bulletList[j].dest, enemyList[i].dest) == true)
			{
					std::cout << "CARPISTI";
					EnemyDeathParticle(enemyList[i]);
					enemyList.erase(enemyList.begin() + i);
					bulletList.erase(bulletList.begin() + j);
					score += 1;
			}
		}
	}


	//TODO o hatayla ilgilen
}



void Game::EnemyDeathParticle(Enemy enemy)
{
	Particle enemyDeathParticle;
	Color4F color;

	color.a = 1;
	color.b = 0.16;
	color.g = 0.06;
	color.r = 1;

	enemyDeathParticle.setRenderer(renderer);                   
	enemyDeathParticle.setPosition(enemy.x, enemy.y);
	enemyDeathParticle.setStyle(Particle::GALAXY);
	enemyDeathParticle.setStartColor(color);
	enemyDeathParticle.setStartSpin(0);
	enemyDeathParticle.setStartSpinVar(90);
	enemyDeathParticle.setEndSpin(90);
	enemyDeathParticle.setStartSpinVar(90);
	enemyDeathParticle.setLife(1);
	enemyDeathParticle.setDuration(1);

	particleList.push_back(enemyDeathParticle);
}



void Game::GameOver()
{
	//saveFile.open(savePath.c_str(), std::ios::out | std::ios::app);
	std::cout << "Game Over";
	saveFile << score << std::endl;

	isGameOver = true;

	enemyList.clear();

}



void Game::DisplayScoreText()
{
	TTF_Font* font = TTF_OpenFont("assets/TeleSys.ttf", 28);

	std::string t = std::to_string(score);
	char const* n_char = t.c_str();


	SDL_Surface* text_surface = TTF_RenderText_Solid(font, "Score: ", ScoreTextColor);
	SDL_Surface* inttext_surface = TTF_RenderText_Solid(font, n_char, ScoreIntTextColor);	
	if (!font)
	{
		std::cout << "OLMADI";
	}
	Game::ScoreTextTexture = SDL_CreateTextureFromSurface(renderer, text_surface);
	Game::ScoreIntTextTexture = SDL_CreateTextureFromSurface(renderer, inttext_surface);

	Game::ScoreTextDest.x = 60 - (text_surface->w / 2.0f);
	Game::ScoreTextDest.y = 550;
	Game::ScoreTextDest.w = text_surface->w;
	Game::ScoreTextDest.h = text_surface->h;
	
	Game::ScoreIntTextDest.x = 110 - (inttext_surface->w / 2.0f);
	Game::ScoreIntTextDest.y = 550;
	Game::ScoreIntTextDest.w = inttext_surface->w;
	Game::ScoreIntTextDest.h = inttext_surface->h;

	//SDL_DestroyTexture(Game::ScoreTextTexture);
	SDL_FreeSurface(text_surface);
	SDL_FreeSurface(inttext_surface);

	SDL_RenderCopy(renderer, ScoreTextTexture, NULL, &ScoreTextDest);
	SDL_RenderCopy(renderer, ScoreIntTextTexture, NULL, &ScoreIntTextDest);
}



void Game::DisplayAmmoText()
{
	TTF_Font* font = TTF_OpenFont("assets/TeleSys.ttf", 28);

	std::string t = std::to_string(Ammo);
	char const* n_char = t.c_str();


	SDL_Surface* text_surface = TTF_RenderText_Solid(font, "Ammo: ", AmmoTextColor);
	SDL_Surface* inttext_surface = TTF_RenderText_Solid(font, n_char, AmmoIntTextColor);
	if (!font)
	{
		std::cout << "OLMADI";
	}


	Game::AmmoTextTexture = SDL_CreateTextureFromSurface(renderer, text_surface);
	Game::AmmoIntTextTexture = SDL_CreateTextureFromSurface(renderer, inttext_surface);

	
	Game::AmmoTextDest.x = 724 - (text_surface->w / 2.0f);
	Game::AmmoTextDest.y = 550;
	Game::AmmoTextDest.w = text_surface->w;
	Game::AmmoTextDest.h = text_surface->h;


	Game::AmmoIntTextDest.x = 774 - (inttext_surface->w / 2.0f);
	Game::AmmoIntTextDest.y = 550;
	Game::AmmoIntTextDest.w = inttext_surface->w;
	Game::AmmoIntTextDest.h = inttext_surface->h;
	

	SDL_FreeSurface(text_surface);
	SDL_FreeSurface(inttext_surface);

	SDL_RenderCopy(renderer, AmmoTextTexture, NULL, &AmmoTextDest);
	SDL_RenderCopy(renderer, AmmoIntTextTexture, NULL, &AmmoIntTextDest);
}


void Game::DisplayGameOverText()
{

	TTF_Font* font = TTF_OpenFont("assets/TeleSys.ttf", 48);



	SDL_Surface* text_surface = TTF_RenderText_Solid(font, "GameOver\n", GameOverTextColor);
	if (!font)
	{
		std::cout << "OLMADI";
	}


	Game::GameOverTextTexture = SDL_CreateTextureFromSurface(renderer, text_surface);

	
	Game::GameOverTextDest.x = 400 - (text_surface->w / 2.0f);
	Game::GameOverTextDest.y = 250;
	Game::GameOverTextDest.w = text_surface->w;
	Game::GameOverTextDest.h = text_surface->h;





	SDL_FreeSurface(text_surface);


	SDL_RenderCopy(renderer, GameOverTextTexture, NULL, &GameOverTextDest);
}



