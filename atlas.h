#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <vector>
#include <string>

class Atlas
{
public:
	Atlas() = default;
	~Atlas() {
		for (SDL_Texture* texture : texture_list) {
			SDL_DestroyTexture(texture);
		}
	}

	void load(SDL_Renderer* renderer, const char* path_template, int num) {
		for (int i = 0; i < num; i++) {
			char path_file[256];
			sprintf_s(path_file, path_template, i + 1);
			// NOTE: 1. SDL中要渲染图像,首先根据图像生成对应的SDL_surface存在内存中,如果要使用硬件加速则需要根据surface生成SDL_texture存在显存中,如果不需要关心surface的存在的话可以直接用loadtexture不过这一步依然需要先生成surface
			SDL_Texture* texture = IMG_LoadTexture(renderer, path_file);
			texture_list.push_back(texture);
		}
	}

	void clear() {
		texture_list.clear();
	}

	int get_size() const {
		return (int)texture_list.size();
	}

	SDL_Texture* get_texture(int index) {
		if (index < 0 || index >= get_size()) {
			return nullptr;
		}

		return texture_list[index];
	}

	void add_textrue(SDL_Texture* texture) {
		texture_list.push_back(texture);
	}
private:
	std::vector<SDL_Texture*> texture_list;
};
