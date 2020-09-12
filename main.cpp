#include <stdio.h>
#include <cmath>
#include <utility>

#include "CommonColors.h"
#include "RenderBuffer.h"
#include "Mesh.h"

#define SDL_MAIN_HANDLED
#include <SDL/SDL.h>

#define PI 3.14159

const int WIDTH = 640, HEIGHT = 640;
Color CLEAR_COLOR = 0x000000;

void DrawLine(int x0, int y0, int x1, int y1, RenderBuffer* buffer, Color color)
{
	bool steep = false;
	if (std::abs(x0 - x1) < std::abs(y0 - y1))
	{
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}

	if (x0 > x1)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	int dx = x1 - x0;
	int dy = y1 - y0;
	float derror2 = std::abs(dy)*2;
	float error2 = 0;
	int y = y0;
	for (int x = x0; x < x1; x++)
	{
		if (steep)
		{
			buffer->SetBufferAt(y, x, color);
		}
		else
		{
			buffer->SetBufferAt(x, y, color);
		}
		error2 += derror2;
		if (error2 > dx)
		{
			y += (y1 > y0 ? 1 : -1);
			error2 -= dx * 2;
		}
	}
}

int main()
{
	//***************************************************************
	// Initialize App
	//***************************************************************
	SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "1");
	
	RenderBuffer* buffer = new RenderBuffer(WIDTH, HEIGHT, 0x050505);

	SDL_Window* window = SDL_CreateWindow("IttyBitty Renderer",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH,HEIGHT,
		SDL_WINDOW_OPENGL);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Texture* texture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_ABGR8888,
		SDL_TEXTUREACCESS_STREAMING,
		WIDTH, HEIGHT);

	if (window == nullptr)
	{
		printf("Could not create SDL window: %s\n", SDL_GetError());

	}

	//***************************************************************
	// Main Loop
	//***************************************************************

	Mesh* mesh = new Mesh("Meshes/african_head.obj");
	float angle = 0.0f;
	Mat3f rotY;
	while (true)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				goto CLEANUP;
			}
		}
		
		buffer->ClearBuffer();

		for (int i = 0; i < mesh->NumberOfFaces(); ++i)
		{
			std::vector<int> face = mesh->FaceAt(i);
			for (int j = 0; j < 3; ++j)
			{
				Vec3f v0 = mesh->VertAt(face[j]);
				Vec3f v1 = mesh->VertAt(face[(j + 1) % 3]);
				v0 = rotY * v0;
				v1 = rotY * v1;

				int x0 = ((v0.x + 1.0f) * WIDTH) / 2.0f;
				int y0 = ((v0.y + 1.0f) * HEIGHT) / 2.0f;
				int x1 = ((v1.x + 1.0f) * WIDTH) / 2.0f;
				int y1 = ((v1.y + 1.0f) * HEIGHT) / 2.0f;

				Color color = COLOR_RED * ((v0.z + 1.0f) / 2.0f);
				DrawLine(x0, y0, x1, y1, buffer, color);
			}
		}

		angle += 1.0f;
		if (angle >= 360.0f) angle -= 360.0f;
		float angleRad = angle * (PI / 180.0f);
		rotY.SetAsRotY(angleRad);
		
		SDL_UpdateTexture(texture, nullptr, buffer->GetBuffer(), 4 * WIDTH);
		SDL_RenderCopyEx(renderer, texture, nullptr, nullptr, 0.0, NULL, SDL_FLIP_VERTICAL);
		SDL_RenderPresent(renderer);

		SDL_Delay(1000 / 60);
	}

	//***************************************************************
	// Cleanup
	//***************************************************************
CLEANUP:
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	delete buffer;
	SDL_Quit();
}