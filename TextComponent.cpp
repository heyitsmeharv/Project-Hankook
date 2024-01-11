#include "TextComponent.h"
#include "ErrorManager.h"

namespace hk
{
	TextComponent::TextComponent(SDL_Renderer* renderer)
	{
		TextureInitInfo init_info;
		init_info.renderer = renderer;

		texture = Texture(init_info);
	}

	void TextComponent::SetText(const std::string& new_text)
	{
		this->text = new_text;

		if (texture.CreateTextureFromText(font, text, colour) == false)
		{
			hk::Fault(hk::ErrorCategory::GFX, "Failed to update text for text component with text: %s", text.data());
		}
	}

	const std::string& TextComponent::GetText() const
	{
		return text;
	}
}