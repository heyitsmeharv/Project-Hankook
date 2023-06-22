#include "SpriteSheet.h"

//STD
#include <fstream>
#include <sstream>
#include <rapidjson/document.h>

#include "ErrorManager.h"
#include "TextureManager.h"

namespace hk
{
	SpriteSheet::SpriteSheet()
		: m_texture(nullptr)
	{
	}

	SpriteSheet::~SpriteSheet()
	{
		Destroy();
	}

	void SpriteSheet::Destroy()
	{
		m_frames.clear();
		m_texture = nullptr;
	}

	void SpriteSheet::DrawFrame(const int frame_index) const
	{
		if (m_texture)
		{
			hk::TextureDrawInfo draw_info;
			draw_info.clip = m_frames[frame_index];

			m_texture->Draw(draw_info);
		}
	}

	bool SpriteSheet::Load(const std::string& image_path)
	{
		size_t index = image_path.rfind(".");
		if (index == -1)
		{
			return false;
		}

		const std::string json_path = image_path.substr(0, index) + ".json";
		return Load(image_path, json_path);
	}
	
	bool SpriteSheet::Load(const std::string& image_path, const std::string& metadata_path)
	{
		if (LoadTexture(image_path) == false)
		{
			return false;
		}

		return LoadSpriteSheet(metadata_path);
	}

	bool SpriteSheet::LoadTexture(const std::string& image_path)
	{
		hk::TextureInitInfo init_info;
		init_info.filepath = image_path;

		if (hk::TextureManager::Instance().LoadTexture(init_info) == false)
		{
			return false;
		}
		
		m_texture = &hk::TextureManager::Instance().GetTexture(image_path);
		return true;
	}

	bool SpriteSheet::LoadSpriteSheet(const std::string& metadata_path)
	{
		std::ifstream contents(metadata_path);        
		if (contents.is_open() == false)
		{
			return false;
		}

		std::stringstream buffer;
		buffer << contents.rdbuf();

		rapidjson::Document doc;
		doc.Parse(buffer.str().c_str());

		if (doc.HasParseError() || doc.IsNull())
		{
			hk::Warn(hk::ErrorCategory::GFX, "Failed to parse keybindings file for controller, all keybindings will be blank");
			return false;
		}

		int num_of_sprites = 0;
		int sprite_width = 0;
		int sprite_height = 0;

		if (doc.HasMember("num_of_sprites"))
		{
			num_of_sprites = doc["num_of_sprites"].GetInt();
		}
		if (doc.HasMember("sprite_width"))
		{
			sprite_width = doc["sprite_width"].GetInt();
		}
		if (doc.HasMember("sprite_height"))
		{
			sprite_height = doc["sprite_height"].GetInt();
		}

		SDL_Rect current_rect;
		current_rect.w = sprite_width;
		current_rect.h = sprite_height;

		int num_of_columns = m_texture->GetWidth() / sprite_width;
		int num_of_rows = m_texture->GetHeight() / sprite_height;

		int current_column = 0;
		int current_row = 0;

		for (int i = 0; i < num_of_sprites; ++i)
		{
			current_column = i % num_of_rows;
			current_row = i / num_of_columns;

			current_rect.x = current_column * sprite_width;
			current_rect.y = current_row * sprite_height;

			m_frames.push_back(current_rect);
		}

		return true;
	}
}