#include "Common.h"

#include <stdexcept>

#define GL_CONTEXT_ERROR 0x0555

class GL_Exception :public std::runtime_error {
public:
	GL_Exception(std::string message) :runtime_error(message) {}
};

inline void CHECK_GL(GLenum result, std::string message) {
	std::string errorString;
	switch (result) {
	case GL_NO_ERROR:
		return;

	case GL_INVALID_ENUM:
		errorString = "GL Error: GL_INVALID_ENUM";
		break;
	case GL_INVALID_VALUE:
		errorString = "GL Error: GL_INVALID_VALUE";
		break;
	case GL_INVALID_OPERATION:
		errorString = "GL Error: GL_INVALID_OPERATION";
		break;
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		errorString = "GL Error: GL_INVALID_FRAMEBUFFER_OPERATION";
		break;
	case GL_OUT_OF_MEMORY:
		errorString = "GL Error: GL_OUT_OF_MEMORY";
		break;
	case GL_STACK_UNDERFLOW:
		errorString = "GL Error: GL_STACK_UNDERFLOW";
		break;
	case GL_STACK_OVERFLOW:
		errorString = "GL Error: GL_STACK_OVERFLOW";
		break;
	case GL_CONTEXT_ERROR:
		errorString = "GL Error: GL_CONTEXT_ERROR";
		break;
	default:
		errorString = "GL Error: GL_UNKNOWN_ERROR";
	}

	std::wstring temp1 = std::wstring(message.begin(), message.end());
	std::wstring temp2 = std::wstring(errorString.begin(), errorString.end());
	MessageBox(NULL, temp1.c_str(), temp2.c_str(), MB_ICONERROR);
	throw GL_Exception(message.c_str());
}