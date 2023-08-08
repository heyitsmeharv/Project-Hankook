#pragma once

#include "ImGuiUser.h"

namespace hk
{
	class SpriteSheet;

	class SpriteAnimation : public IImGuiUser
	{
	public:
		 SpriteAnimation();
		~SpriteAnimation();

		void Update	(const double delta_time);
		void Draw	() const;
		
		void SetSpriteSheet(const SpriteSheet* sprite_sheet);

		void AddToImGui() override;

	private:
		int		m_current_frame_index;
		bool	m_is_paused;
		double	m_current_anim_time;
		double	m_playback_speed;

		const SpriteSheet* m_sprite_sheet;
	};
}