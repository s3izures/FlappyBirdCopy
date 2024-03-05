#pragma once
#include "raylib.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class FlappyBird
{
public:
	void Main();

private:
	void Start();
	void Update();
	void EvalFrame();
	void DrawFrame();

	void InitPipes();
	void InitBird();

	static const int screenX = 800;
	static const int screenY = 450;
	static const int gap = 200;
	bool gameOver = false;
	
	int score = 0;
	int highScore = 0;

#pragma region Structs
	typedef struct Bird {
		//VARIABLES
		Vector2 pos;
		int radius = 10;
		Color col = YELLOW;

		//FUNCTIONS
		void Draw()
		{
			DrawCircleV(pos, radius, YELLOW);
		}
		void Move()
		{
			if (IsKeyDown(KEY_SPACE))
				pos.y -= 5;
			else
				pos.y += 3;
		}
	}Bird;


	typedef struct Pipe {
		//VARIABLES
		float x;
		float width = 80;
		float heightTop, heightBot;
		float yBot;
		Color col = LIME;
		Rectangle topRect, botRect;
		bool passed = false;
		bool active = true;

		//FUNCTIONS
		Pipe(float x)
		{
			this->x = x;

			this->heightTop = GetRandomValue(175, 275);
			this->yBot = heightTop + 100;
			this->heightBot = screenY - yBot;

			topRect = Rectangle{ x,0,width,heightTop };
			botRect = Rectangle{ x,yBot,width,heightBot };
		}
		void Draw()
		{
			//Check boundaries
			if (x + width > 0 && x < screenX)
			{
				active = true;
			}
			else
			{
				active = false;
			}

			//Draw within bounds
			if (active)
			{
				DrawRectangleRec(topRect, col);
				DrawRectangleRec(botRect, col);
			}
		}
		void Move()
		{
			x -= 1;
			topRect.x = x;
			botRect.x = x;
		}
		int Pass(Bird bird, int& score)
		{
			if (x + width < bird.pos.x - bird.radius && !passed)
			{
				col = GREEN;
				passed = true;
				score++;
			}
			return passed;
		}
		bool BirdCollision(Bird bird)
		{
			return CheckCollisionCircleRec(bird.pos, bird.radius, topRect) || CheckCollisionCircleRec(bird.pos, bird.radius, botRect);
		}
		bool OOB()
		{
			return x + width < 0;
		}

	}Pipe;
#pragma endregion

	vector<Pipe>pipes;
	Bird bird;
};

