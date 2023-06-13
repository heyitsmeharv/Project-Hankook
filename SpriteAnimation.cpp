#include "SpriteAnimation.h"
#include "SpriteSheet.h"
#include "imgui/imgui.h"

namespace hk
{
	SpriteAnimation::SpriteAnimation()
		: m_current_frame_index(0)
		, m_is_paused(false)
		, m_sprite_sheet(nullptr)
	{
	}

	SpriteAnimation::~SpriteAnimation()
	{
		m_sprite_sheet = nullptr;
	}

	void SpriteAnimation::Update()
	{
		if (m_sprite_sheet && m_is_paused == false)
		{
			m_current_frame_index = ++m_current_frame_index % m_sprite_sheet->NumOfFrames();
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
			static bool open = true;
			ImGui::Begin("Sprite Animation", &open);

			ImGui::Checkbox("Is Paused", &m_is_paused);
			ImGui::SliderInt("Current Frame", &m_current_frame_index, 0, m_sprite_sheet->NumOfFrames() - 1);

			ImGui::End();
		}
	}
}