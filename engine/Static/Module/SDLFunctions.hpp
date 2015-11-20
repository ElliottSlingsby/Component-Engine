#pragma once

#include <SDL.h>
#include <memory>

typedef unsigned char PixelFormat;

PixelFormat getPixel(SDL_Surface* surface, unsigned int x, unsigned int y){
	PixelFormat* pixels = (PixelFormat*)surface->pixels;

	int offset = y * (surface->pitch / sizeof(PixelFormat));
	return pixels[offset + x];
}

void putPixel(SDL_Surface* surface, unsigned int x, unsigned int y, PixelFormat pixel){
	PixelFormat* pixels = (PixelFormat*)surface->pixels;

	int offset = y * (surface->pitch / sizeof(PixelFormat));
	pixels[offset + x] = pixel;
}

// https://gist.github.com/codespear/5859474

SDL_Surface* flipVertical(SDL_Surface* surface) {
	SDL_Surface* flipped = SDL_CreateRGBSurface(surface->flags, surface->w, surface->h, surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask);

	SDL_LockSurface(flipped);

	const int pitch = surface->pitch;
	const int pixelLength = pitch * surface->h;

	PixelFormat* pixels = (PixelFormat*)(surface->pixels) + pixelLength;
	PixelFormat* pixelsFlipped = (PixelFormat*)(flipped->pixels);

	for (int i = 0; i < surface->h; i++) {
		memcpy(pixelsFlipped, pixels, pitch);

		pixels -= pitch;
		pixelsFlipped += pitch;
	}

	return flipped;
}