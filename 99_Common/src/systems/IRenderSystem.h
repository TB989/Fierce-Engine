#pragma once

#include <string>

namespace Fierce {

	class IRenderSystem{
	public:
		//########################### INTERFACE ##############################################################################
		virtual int newMesh(int numVertices, int numIndices)=0;
		virtual void meshLoadVertices(int meshId, int numVertices, float* vertices)=0;
		virtual void meshLoadIndices(int meshId, int numIndices, uint16_t* indices)=0;

		virtual int newTexture(int width, int height, int numChannels)=0;
		virtual void textureLoadData(int textureId, unsigned char* pixels)=0;

		virtual void bindPipeline(std::string name)=0;
		virtual void setOrthographicProjection(float* projectionMatrix)=0;
		virtual void setPerspectiveProjection(float* projectionMatrix)=0;
		virtual void setViewMatrix(float* viewMatrix)=0;
		virtual void loadModelMatrix(float* modelMatrix)=0;
		virtual void loadColor(float* color)=0;
		virtual void activateSampler(std::string pipeline, int texture)=0;

		virtual void startFrame()=0;
		virtual void drawMesh(int m_meshId)=0;
		virtual void endFrame()=0;

		virtual void postInit()=0;
		//########################### INTERFACE #############################################################################
	};

}//end namespace