#pragma once

namespace hk
{
	struct DrawRequest
	{
		virtual ~DrawRequest() {}

		virtual void HandleRequest() const = 0;
	};
}