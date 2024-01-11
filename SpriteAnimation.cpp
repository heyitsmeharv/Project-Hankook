#include "SpriteAnimation.h"
#include "SpriteSheet.h"

#include <cmath>

namespace hk
{
	SpriteAnimation::SpriteAnimation()
		: m_current_frame_index(0)
		, m_is_paused(false)
		, m_current_anim_time(0.0)
		, m_playback_speed(1.0)
		, m_sprite_sheet(nullptr)
	{
	}

	SpriteAnimation::~SpriteAnimation()
	{
		m_sprite_sheet = nullptr;
	}

	void SpriteAnimation::Update(const double delta_time)
	{
		if (m_sprite_sheet && m_is_paused == false)
		{
			m_current_anim_time += (delta_time * m_playback_speed);
			m_current_anim_time = m_current_anim_time > m_sprite_sheet->DefaultAnimTime() ? 0.0 : m_current_anim_time;

			const double frame_length = m_sprite_sheet->FrameLength();
			const int new_frame = static_cast<int>(std::floor(m_current_anim_time / frame_length));

			if (new_frame != m_current_frame_index)
			{
				++m_current_frame_index;
				m_current_frame_index = m_current_frame_index % m_sprite_sheet->NumOfFrames();
			}
		}
	}

	void SpriteAnimation::Draw() const
	{
		if (m_sprite_sheet)
		{
			m_sprite_sheet->DrawFrame(m_current_frame_index);
		}
	}

	void SpriteAnimation::SetSpriteSheet(const SpriteSheet* sprite_sheet)
	{
		m_sprite_sheet = sprite_sheet;
	}

	void SpriteAnimation::AddToImGui()
	{
		if (m_sprite_sheet)
		{
			std::string id = "Sprite Animation##" + m_sprite_sheet->Id();

			if (ImGui::TreeNode(m_sprite_sheet->Id().data()))
			{

				ImGui::Checkbox("Is Paused", &m_is_paused);
				ImGui::InputDouble("Playback Speed", &m_playback_speed);
				ImGui::SliderInt("Current Frame", &m_current_frame_index, 0, m_sprite_sheet->NumOfFrames() - 1);

				ImGui::TreePop();
			}
		}
	}
}