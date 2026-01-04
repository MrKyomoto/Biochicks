#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#define FPS 60

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

	SDL_Surface* suf_img = IMG_Load("resources/battery.png");
	SDL_Texture* tex_img = SDL_CreateTextureFromSurface(renderer, suf_img);
	SDL_Point pos_cursor = { 0,0 };

	TTF_Font* font = TTF_OpenFont("resources/IPix.ttf", 32);
	SDL_Color color = { 255,255,255,255 };
	SDL_Surface* suf_text = TTF_RenderUTF8_Blended(font, u8"你好SDL2", color);
	SDL_Texture* tex_text = SDL_CreateTextureFromSurface(renderer, suf_text);

	Mix_Music* music = Mix_LoadMUS("resources/bgm.mp3");

	Mix_FadeInMusic(music, -1, 1500);

	bool is_quit = false;

	SDL_Event event;
	SDL_Rect rect_img;

	rect_img.w = suf_img->w;
	rect_img.h = suf_img->h;

	SDL_Rect rect_text;

	rect_text.w = suf_text->w;
	rect_text.h = suf_text->h;

	// 动态延时控制

	// 高精度计时器跳的总次数
	Uint64 last_count = SDL_GetPerformanceCounter();
	// 每一秒高精度计时器会跳多少次
	Uint64 counter_freq = SDL_GetPerformanceFrequency();
	while (!is_quit) {
		// 获取事件
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				is_quit = true;
			}
			else if (event.type == SDL_MOUSEMOTION) {
				pos_cursor.x = event.motion.x;
				pos_cursor.y = event.motion.y;
			}
		}
		// 处理数据
		
		Uint64 current_counter = SDL_GetPerformanceCounter();
		double delta = (double)(current_counter - last_count) / counter_freq;
		last_count = current_counter;
		if (delta * 1000 < 1000.0 / FPS) {
			SDL_Delay(1000.0 / FPS - delta * 1000);
		}

		rect_img.x = pos_cursor.x;
		rect_img.y = pos_cursor.y;
		rect_text.x = pos_cursor.x + 50;
		rect_text.y = pos_cursor.y + 50;
		// 渲染绘图
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, tex_img, nullptr, &rect_img);
		SDL_RenderCopy(renderer, tex_text, nullptr, &rect_text);

		SDL_RenderPresent(renderer);
	}
	return 0;
}