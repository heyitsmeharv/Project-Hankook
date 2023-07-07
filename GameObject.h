#pragma once

#include "Drawable.h"
#include "Transformable.h"

namespace hk
{
	class Texture;

	class GameObject	: public Drawable
						, public Transformable
	{
	public:
		GameObject(const Texture* texture, Vector2i position);

		void Draw() const override;

	protected:
		const Texture* m_texture;

	};
}