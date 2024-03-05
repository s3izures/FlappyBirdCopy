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
	for (Pipe& p : pipes)
	{
		p.Move(bird);
	}
	bird.Move();
}

void FlappyBird::DrawFrame()
{
	//ACTORS
	for (Pipe p : pipes)
	{
		p.Draw();
	}
	bird.Draw();

	//SCORE
	DrawText(TextFormat("Score: %02i", score), 20, 20, 16, BLACK);
	DrawText(TextFormat("High Score: %02i", highScore), 20, 40, 16, YELLOW);
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
