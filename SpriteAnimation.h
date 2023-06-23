#pragma once

#include "ImGuiUser.h"

namespace hk
{
	class SpriteSheet;

	class SpriteAnimation : public ImGuiUser
	{
	public:
		 SpriteAnimation();
		~SpriteAnimation();

		void Update	();
		void Draw	() const;
		
		void SetSpriteSheet(const SpriteSheet* sprite_sheet);

		void AddToImGui() override;

	private:
		int  m_current_frame_index;
		bool m_is_paused;

		const SpriteSheet* m_sprite_sheet;
	};
}