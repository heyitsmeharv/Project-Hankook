#include "TextureManager.h"

#include <filesystem>

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
			printf("This is really bad, we have no default texture, things are going to crash! \n");
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

		auto [itr, _] = m_textures.emplace(init_info.filepath, init_info);

		//If the texture fails to load, we don't want a bad entry hanging around
		//so remove it from the list so we can't find it and reference it later
		if (itr->second.LoadTexture() == false)
		{
			m_textures.erase(itr);
			return false;
		}

		return true;
	}

	void TextureManager::LoadDirectory(const std::string& directory)
	{
		//for (const auto& directory_entry : std::filesystem::recursive_directory_iterator(directory))
		//{
		//	directory_entry.path().extension()
		//}
	}

	const hk::Texture& TextureManager::GetTexture(const std::string& filepath) const
	{
		const auto& itr = m_textures.find(filepath);
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