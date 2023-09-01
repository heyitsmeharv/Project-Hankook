#pragma once

#include "DrawRequest.h"
#include "TextureInfos.h"

namespace hk
{
	class Texture;

	struct TextureDrawRequest final : public DrawRequest
	{
		void HandleRequest() const override;

		const Texture*	texture;
		TextureDrawInfo draw_info;
	};
}