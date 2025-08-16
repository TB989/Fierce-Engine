#pragma once

#include "src/Color.h"

#include "GraphicsContext.h"

#include <string>

namespace Fierce{
	class GUIPanel{
	public:
		void setBackgroundColor(float r,float g,float b) {
			m_backgroundColor->setR(r);
			m_backgroundColor->setG(g);
			m_backgroundColor->setB(b);
		}

		void setForegroundColor(float r, float g, float b) {
			m_foregroundColor->setR(r);
			m_foregroundColor->setG(g);
			m_foregroundColor->setB(b);
		}

		void setFont(std::string fontName) {
			m_font = fontName;
		}

		void setFontSize(int fontSize) {
			m_fontSize = fontSize;
		}

		void setX(int x) {
			m_x = x;
		}

		void setY(int y) {
			m_y = y;
		}

		void draw(GraphicsContext* g);

	protected:
		float m_x=0.0f;
		float m_y=0.0f;
		float m_width=0.0f;
		float m_height=0.0f;

		float m_preferredWidth=0.0f;
		float m_preferredHeight=0.0f;

		Color3f* m_backgroundColor=new Color3f(1,1,1);
		Color3f* m_foregroundColor=new Color3f(0,0,0);

		std::string m_font="TimesNewRoman";
		int m_fontSize=20;
	};
}