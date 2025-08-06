#pragma once

#include "src/vulkanObjects/VK_Buffer.h"

#include "RenderBatch.h"

#include "src/utils/Font.h"

namespace Fierce {

	class RenderBatchFont : public RenderBatch {

	public:
		RenderBatchFont(VK_Device* device,Font* font,int fontSize);
		virtual ~RenderBatchFont() {};

		Font* getFont() { return m_font; }
		int getFontSize() { return m_fontSize; }

	private:
		Font* m_font = nullptr;
		int m_fontSize=0;
	};
}