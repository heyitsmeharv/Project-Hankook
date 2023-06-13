#include "Sprite.h"
#include "TextureManager.h"

namespace hk
{
	Sprite::Sprite(const std::string& image_path)
	{
		m_texture = &hk::TextureManager::Instance().GetTexture(image_path);
	}

	Sprite::~Sprite()
	{
		m_texture = nullptr;
	}

	void Sprite::Draw() const
	{
		if (m_texture)
		{
			hk::TextureDrawInfo info;
			info.x_pos = m_x_pos;
			info.y_pos = m_y_pos;
			info.flip = m_flip;
			info.angle_in_deg = m_rotation_in_deg;

			m_texture->Draw(info);
		}
	}
}