#pragma once

#include <string>
#include "Drawable.h"

namespace hk
{
	class Texture;

	class Sprite : public Drawable
	{
	public:
		 Sprite(const std::string& image_path);
		~Sprite();

		void Draw() const override;

	private:
		const Texture* m_texture;

	};
}