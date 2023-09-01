#pragma once

#include "DrawRequest.h"
#include "TextureInfos.h"

namespace hk
{
	class Texture;

	struct TileDrawRequest final : public DrawRequest
	{
		void HandleRequest() const override;

		const Texture*	texture;
		TileDrawInfo	draw_info;
	};
}