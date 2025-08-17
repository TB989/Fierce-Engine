#include "RenderBatchFont.h"

namespace Fierce {

	RenderBatchFont::RenderBatchFont(VK_Device* device, Font* font, int fontSize):RenderBatch(device){
		m_font = font;
		m_fontSize = fontSize;
	}
}