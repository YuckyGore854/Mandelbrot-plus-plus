#include<iostream>
#include<SDL.h>
#include<math.h>
#include<complex>

using namespace std;

double mandelbrot(complex<double> c);

void Draw( SDL_Renderer* renderer, int xPos, int yPos, int zoom);
Uint32 buttons;
int main(int argc, char* argv[]) {
	enum coords {
		xPos, yPos
	};
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Mandelbrot Set", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, NULL);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, NULL);
	SDL_Event event;
	int totalTime = 0;
	Uint32 startTime = 0;
	bool running = true;
	int mousePos[2] = { 0,0 };
	double zoom = 1;
	
	
	while (running) {
		while (SDL_PollEvent(&event) != 0) {

			if (event.type == SDL_QUIT) {
				SDL_Quit();
			}
			if (event.type == SDL_MOUSEWHEEL) {
				if (event.wheel.y > 0) {//scroll up
					zoom += 1;
				}
				if (event.wheel.y < 0 && zoom>1) {
					zoom-=1;
				}
				std::cout << zoom << endl;
			}
		}
		
		buttons = SDL_GetMouseState(&mousePos[xPos], &mousePos[yPos]);
		if (buttons & SDL_BUTTON_LMASK){
			Draw(renderer, mousePos[xPos], mousePos[yPos], zoom);
		}
	}
	return 0;
}

double mandelbrot(complex<double> c) {
	complex<double> z(0, 0);
	double count = 0;
	while (abs(z) < 2 && count < 80) {
		z = z * z + c;
		count++;
	}
	return count;
}

void Draw(SDL_Renderer* renderer, int xPos, int yPos, int zoom) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	xPos = xPos-400;
	yPos = yPos-400;
	double zoomLevel = zoom;
	double resolution = 0.009 /(zoomLevel);
	double t = -2;
	double m = -2;
	double lowerVertBound = -2;
	double upperVertBound = 2;

	double lowerHorizBound = -2;
	double upperHorizBound = 2;

	while (t < upperHorizBound) {
		t += resolution;
		m = lowerVertBound;
		while (m < upperVertBound) {
			m += resolution;
			
			if (t * zoomLevel * 200 + xPos + 400 > 0 && t * zoomLevel * 200 + xPos + 400 < 800 && m * zoomLevel * 200 + yPos + 400 > 0 && m * zoomLevel * 200 + yPos + 400 < 800) {
				complex<double> c(t, m);
				double num = mandelbrot(c);
				//std::cout << num << endl;
				if (num < 20) {
					//screen.set_at((int(zoomLevel * t * 200 + 400), int(zoomLevel * m * 200 + 400)), (num * 3, num * 6, num * 12))
					SDL_SetRenderDrawColor(renderer, num * 3, num * 6, num * 12, 255);
					SDL_RenderDrawPoint(renderer, int(zoomLevel * t * 200 + 400) + xPos, int(zoomLevel * m * 200 + 400) + yPos);
				}
				else if (num < 40) {
					//screen.set_at((int(zoomLevel * t * 200 + 400), int(zoomLevel * m * 200 + 400)), (num * 3, num * 6, num * 12))
					SDL_SetRenderDrawColor(renderer, num * 2, num / 4, num * 4, 255);
					SDL_RenderDrawPoint(renderer, int(zoomLevel * t * 200 + 400) + xPos, int(zoomLevel * m * 200 + 400) + yPos);
				}
				else if (num == 80) {
					SDL_SetRenderDrawColor(renderer, 2, 255, 255, 255);
					SDL_RenderDrawPoint(renderer, int(zoomLevel * t * 200 + 400) + xPos, int(zoomLevel * m * 200 + 400) + yPos);
				}
				else {
					SDL_SetRenderDrawColor(renderer, num * 3, num / 2, num * 2, 255);
					SDL_RenderDrawPoint(renderer, int(zoomLevel * t * 200 + 400) + xPos, int(zoomLevel * m * 200 + 400) + yPos);
				}
				//SDL_RenderPresent(renderer);
			}
		}
		SDL_RenderPresent(renderer);
	}
}