#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

int main() {

	// Step 1: Init
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	Mix_Init(MIX_INIT_MP3);
	TTF_Init();

	// NOTE: 2. Mix 音频初始化比较特殊,还需要开放音道
	/// param: 采样率, 解码方式, 声道数(2为双声道), 音频播放缓冲区大小(较小的缓冲区会减小音频延迟但会增加处理负担)
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	// Step 2: Create window
	SDL_Window* window = SDL_CreateWindow(u8"测试中文Biochicks", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);

	/// param: 窗口, 默认-1就行, 启用硬件加速
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	bool is_quit = false;

	SDL_Event event;

	while (!is_quit) {
		// 获取事件
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				is_quit = true;
			}
		}
		// 处理数据
		
		// 渲染绘图
	}
	return 0;
}