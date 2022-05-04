#include "Renderer.h"

#include "DLLExport.h"

#include "openGLObjects/GL_Context.h"

#include "openGLObjects/GL_VertexAttribute.h"

#include "Matrix.h"
#include "Transform.h"

GL_Context* context;

RENDERER_API bool initRenderer(HWND dummyWindowHandle,HWND windowHandle) {
    LOGGER->info("Initializing renderer.");

    context = new GL_Context(dummyWindowHandle,windowHandle);

    vertexShader= new GL_Shader("Shader_Color2D.vert");
    fragmentShader = new GL_Shader("Shader_Color.frag");

    pipeline = new GL_Pipeline("Color_2D", vertexShader, fragmentShader);
    pipeline->addVertexAttribute(GL_VertexAttribute::POS2);
    pipeline->addUniformLocation("color");
    pipeline->addUniformLocation("projectionMatrix");
    pipeline->addUniformLocation("modelMatrix");
    pipeline->create();

    GLfloat vertices[] = 
    {
        0.0f,0.0f,
        0.0f,1.0f,
        1.0f,1.0f,
        1.0f,0.0f
    };

    GLuint indices[] = 
    {
        0,1,2,
        0,2,3
    };

    vertexBuffer = new GL_VBO(GL_ARRAY_BUFFER);
    vertexBuffer->loadData(sizeof(float)*8,vertices,GL_STATIC_DRAW);

    indexBuffer = new GL_VBO(GL_ELEMENT_ARRAY_BUFFER);
    indexBuffer->loadData(sizeof(int) * 6, indices, GL_STATIC_DRAW);

    vao = new GL_VAO(vertexBuffer,indexBuffer);
    vao->addVertexAttribute(GL_VertexAttribute::POS2);

    Mat4 orthographicProjectionMatrix = Mat4();
    orthographicProjectionMatrix.setToOrthographicProjection(800.0f, 600.0f, -1.0f, 1.0f);

    Transform2D transform = Transform2D(10.0f,10.0f,100.0f,100.0f,0.0f);

    Mat4 modelMatrix = Mat4();
    modelMatrix.setToIdentity();
    modelMatrix.transform(transform);

    pipeline->bind();
    pipeline->loadUniform("projectionMatrix", &orthographicProjectionMatrix);
    pipeline->loadUniform("modelMatrix", &modelMatrix);
    pipeline->unbind();

    return true;
}

RENDERER_API bool render() {
    glClearColor(0.0f,0.0f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    pipeline->bind();
    pipeline->loadUniform("color",1.0f,0.0f,0.0f);
    vao->bind();
    vao->draw();
    vao->unbind();
    pipeline->unbind();

    context->swapBuffers();

    return true;
}

RENDERER_API bool cleanUpRenderer() {
    LOGGER->info("Cleanning up renderer.");

    delete vao;
    delete indexBuffer;
    delete vertexBuffer;
    delete pipeline;
    delete vertexShader;
    delete fragmentShader;

    delete context;

    return true;
}