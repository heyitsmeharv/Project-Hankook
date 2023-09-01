#include "TileDrawRequest.h"

#include "Texture.h"

namespace hk
{
	void TileDrawRequest::HandleRequest() const
	{
		if (texture)
		{
			texture->DrawTiles(draw_info);
		}
	}
}