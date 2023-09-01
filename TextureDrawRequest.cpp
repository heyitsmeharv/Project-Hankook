#include "TextureDrawRequest.h"

#include "Texture.h"

namespace hk
{
	void TextureDrawRequest::HandleRequest() const
	{
		if (texture)
		{
			texture->Draw(draw_info);
		}
	}
}