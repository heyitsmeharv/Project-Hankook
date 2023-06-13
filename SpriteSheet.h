#pragma once

#include <string>
#include <vector>
#include <SDL_rect.h>

namespace hk
{
	class Texture;

	class SpriteSheet
	{
	public:
		 SpriteSheet();
		~SpriteSheet();

		bool Load(const std::string& image_path);
		bool Load(const std::string& image_path, const std::string& metadata_path);

		void Destroy();

		void DrawFrame(const int frame_index) const;

		int NumOfFrames() const { return static_cast<int>(m_frames.size()); }

	private:
		bool LoadTexture(const std::string& image_path);
		bool LoadSpriteSheet(const std::string& metadata_path);

	private:
		//Future: Do not own this
		const Texture*			m_texture;
		std::vector<SDL_Rect>	m_frames;
	};
}