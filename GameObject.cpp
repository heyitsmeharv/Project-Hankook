#include "GameObject.h"

#include "Texture.h"

namespace hk
{
	GameObject::GameObject(const Texture* texture, Vector2i position)
		: Transformable(position)
		, m_texture(texture)
	{
		
	}

	void GameObject::Draw() const
	{
		if (m_texture)
		{
			hk::TextureDrawInfo draw_info = {};
			draw_info.position = m_position;
			draw_info.flip = m_flip;
			draw_info.angle_in_deg = m_rotation_in_deg;

			m_texture->Draw(draw_info);
		}
	}
}