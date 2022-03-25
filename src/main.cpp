#include <iostream>
#include "SDL2/SDL.h"

int main(int argc, char* args[]) {
	auto drivers_count = SDL_GetNumVideoDrivers();
	std::cout << "drivers: " << drivers_count << std::endl;

	for (int i = 0; i < drivers_count; i++) {
		std::cout << '\t' << SDL_GetVideoDriver(i) << std::endl;
	}

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	auto displays_count = SDL_GetNumVideoDisplays();
	std::cout << "displays: " << displays_count << std::endl;

	for (int i = 0; i < displays_count; i++) {
		SDL_DisplayMode mode;
		SDL_GetDesktopDisplayMode(i, &mode);
		auto bytes = mode.format & 0xFF;
		auto bits = (mode.format >> 8) & 0xFF;

		std::cout << '\t' << "desktop display mode: " << mode.w << 'x' << mode.h << 'x' << bits << "bits/" << bytes
				  << "bytes" << '@' << mode.refresh_rate << "Hz" << std::endl;

		auto display_modes_count = SDL_GetNumDisplayModes(i);
		std::cout << '\t' << "display modes: " << display_modes_count << std::endl;
		for (int j = 0; j < display_modes_count; j++) {
			SDL_DisplayMode mode;
			SDL_GetDisplayMode(i, j, &mode);
			auto bytes = mode.format & 0xFF;
			auto bits = (mode.format >> 8) & 0xFF;

			std::cout << '\t' << '\t' << mode.w << 'x' << mode.h << 'x' << bits << "bits/" << bytes << "bytes" << '@'
					  << mode.refresh_rate << "Hz" << std::endl;
		}
		std::cout << '\t' << "driver: " << SDL_GetVideoDriver(i) << std::endl;
	}

	SDL_Quit();
	return 0;
}
