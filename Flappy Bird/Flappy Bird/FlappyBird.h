#pragma once
#include "raylib.h"
#include <iostream>
#include <vector>
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
				active = true;
			else
				active = false;

			//Draw within bounds
			if (active)
			{
				DrawRectangleRec(topRect, col);
				DrawRectangleRec(botRect, col);
			}
		}
		void Move()
		{
			topRect.x -= 1;
			botRect.x -= 1;
		}

	}Pipe;
#pragma endregion

	Bird bird;
	vector<Pipe> pipes;
};

