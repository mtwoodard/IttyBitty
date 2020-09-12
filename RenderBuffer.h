#pragma once
#include "CommonColors.h"
#include <SDL\SDL_stdinc.h>
//Only of format ABGR8888
class RenderBuffer
{
public:
	RenderBuffer() : width(0), height(0), size(0), buffer(nullptr), clearColor(COLOR_BLACK) {}
	RenderBuffer(unsigned int _width, unsigned int _height, Color _clearColor = COLOR_BLACK);
	~RenderBuffer();

	void SetBufferAt(unsigned int x, unsigned int y, Color color);
	void ClearBuffer();

	void SetClearColor(Color color) { clearColor = color; }

	Uint32* GetBuffer() { return buffer; }
	size_t GetSize() { return (size_t)width * height; }

private:
	Uint32* buffer;
	unsigned int width, height;
	size_t size;
	Color clearColor;

};

