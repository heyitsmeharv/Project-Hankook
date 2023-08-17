#include "TextureManager.h"

#include <filesystem>
#include <unordered_set>

#include "ErrorManager.h"

namespace
{
	std::string CleanPath(const std::string& messy_path) 
	{
		std::string clean_path = messy_path;
		std::replace(clean_path.begin(), clean_path.end(), '/', '\\');
		return clean_path;
	}
}

namespace hk
{
	TextureManager::TextureManager()
		: m_renderer(nullptr)
		, m_default_texture()
	{
	}

	TextureManager::~TextureManager()
	{
		Destroy();
	}

	bool TextureManager::Initialise(SDL_Renderer* renderer, const std::string& default_texture_path)
	{
		m_renderer = renderer;

		hk::TextureInitInfo init_info;
		init_info.filepath = default_texture_path;
		init_info.renderer = m_renderer;

		m_default_texture = hk::Texture(init_info);
		if (m_default_texture.LoadTexture() == false)
		{
			hk::Fatal(hk::ErrorCategory::GFX, "This is really bad, we have no default texture, things are going to crash! \n");
			return false;
		}

		return true;
	}

	void TextureManager::Destroy()
	{
		m_textures.clear();
		m_default_texture.Destroy();
		m_renderer = nullptr;
	}

	bool TextureManager::LoadTexture(hk::TextureInitInfo& init_info)
	{
		init_info.renderer = m_renderer;

		auto [itr, did_insert] = m_textures.emplace(CleanPath(init_info.filepath), init_info);

		//If the texture fails to load, we don't want a bad entry hanging around
		//so remove it from the list so we can't find it and reference it later
		if (did_insert && itr->second.LoadTexture() == false)
		{
			m_textures.erase(itr);
			hk::Warn(hk::ErrorCategory::GFX, "Failed to load texture: %s \n", init_info.filepath.data());
			return false;
		}

		return true;
	}

	void TextureManager::LoadDirectory(const std::string& directory)
	{
		static const std::unordered_set<std::filesystem::path> valid_file_extensions
		{
			".png",
			".jpg",
			".jpeg",
			".bmp",
			".gif"
		};

		for (const auto& directory_entry : std::filesystem::recursive_directory_iterator(directory))
		{
			if (valid_file_extensions.contains(directory_entry.path().extension()))
			{
				hk::TextureInitInfo init_info;
				init_info.filepath = directory_entry.path().string();
				init_info.renderer = m_renderer;

				if (LoadTexture(init_info) == false)
				{
					hk::Warn(hk::ErrorCategory::GFX, "Failed to load texture (%s) in directory (%s) \n", directory.data(), init_info.filepath.data());
				}
			}
		}
	}

	const hk::Texture& TextureManager::GetTexture(const std::string& filepath) const
	{
		const auto& itr = m_textures.find(CleanPath(filepath));
		if (itr != m_textures.end())
		{
			return itr->second;
		}

		return m_default_texture;
	}

	TextureManager& TextureManager::Instance()
	{
		if (m_instance == nullptr)
		{
			m_instance = new TextureManager{};
		}

		return *m_instance;
	}
}