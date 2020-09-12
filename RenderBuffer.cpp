#include "RenderBuffer.h"

RenderBuffer::RenderBuffer(unsigned int _width, unsigned int _height, Color _clearColor) :
	width(_width), height(_height), clearColor(_clearColor)
{
	size = (size_t)width * (size_t)height;
	buffer = new Uint32[size];
}

RenderBuffer::~RenderBuffer()
{
	delete[] buffer;
}

void RenderBuffer::SetBufferAt(unsigned int x, unsigned int y, Color color)
{
	if (x < width && y < height)
	{
		buffer[y * width + x] = color;
	}
}

void RenderBuffer::ClearBuffer()
{
	for (size_t i = 0; i < size; ++i)
	{
		buffer[i] = clearColor;
	}
}
