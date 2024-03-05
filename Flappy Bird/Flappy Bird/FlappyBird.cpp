#include "FlappyBird.h"


void FlappyBird::Main()
{
	InitWindow(screenX, screenY, "Flappy Bird Bootleg");
	SetTargetFPS(60);

	Start();

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(SKYBLUE);
		Update();
		EndDrawing();
	}

	CloseWindow();
}

void FlappyBird::Start()
{
	gameOver = false;
	if (score > highScore)
		highScore = score;
	score = 0;
	pipes.clear();

	InitPipes();
	InitBird();

	//Object Pooling : active or inactive
}

void FlappyBird::Update()
{
	EvalFrame();
	DrawFrame();
}

void FlappyBird::EvalFrame()
{
	int passedPipe = 0;
	for (int i = 0; i < pipes.size(); i++)
	{
		pipes[i].Move();
		if (pipes[i].BirdCollision(bird) || bird.pos.y < 0 || bird.pos.y > screenY)
		{
			gameOver = true;
		}
		if (pipes[i].Pass(bird, score))
		{
			passedPipe = i;
		}
	}

	if (IsKeyPressed(KEY_A))
	{
		float time = GetFrameTime();
		while (GetFrameTime() == time + 10)
		{
			int targetTop = pipes[passedPipe].yBot - bird.radius * 2;
			int targetBot = pipes[passedPipe].heightTop + bird.radius * 2;
			if (bird.pos.y > targetTop)
				bird.pos.y -= 5;
			else if (bird.pos.y < targetBot)
				bird.pos.y += 3;
		}
	}
	else
	{
		bird.Move();
	}

	if (gameOver)
	{
		if (IsKeyPressed(KEY_ENTER))
			Start();
		return;
	}
}

void FlappyBird::DrawFrame()
{
	if (!gameOver)
	{
		//ACTORS
		for (int i = 0; i < pipes.size(); i++)
		{
			if (pipes[i].OOB())
			{
				pipes[i].col = LIME;
				pipes[i].active = true;
				pipes[i].passed = false;
				pipes[i].heightTop = GetRandomValue(175, 275);
				pipes[i].x = pipes[pipes.size() - 1].x + gap;
				rotate(pipes.begin(), pipes.begin() + 1 + i, pipes.end());
			}
		}

		for (Pipe p : pipes)
		{
			p.Draw();
		}

		bird.Draw();

		//SCORE
		DrawText(TextFormat("Score: %02i", score), 20, 20, 16, BLACK);
		DrawText(TextFormat("High Score: %02i", highScore), 20, 40, 16, YELLOW);
	}
	else
	{
		DrawText("Game Over, press enter to restart", screenX / 2 - MeasureText("Game Over, press enter to restart", 24) / 2, screenY / 2 - 12, 24, BLACK);
	}
}

void FlappyBird::InitPipes()
{
	for (int i = 0; i < 5; i++)
	{
		float x = 300 + gap * i;
		Pipe p = Pipe(x);
		pipes.push_back(p);
	}
}

void FlappyBird::InitBird()
{
	bird.pos = { 100,(float)GetRandomValue(100, screenY - 100) };
}
