#include "SetRenderScaleDrawRequest.h"

namespace hk
{
	void SetRenderScaleDrawRequest::HandleRequest() const
	{
		SDL_RenderSetScale(renderer, scale.x, scale.y);
	}
}