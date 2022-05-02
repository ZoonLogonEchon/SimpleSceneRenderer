#ifndef RENDERERWIDGET_HPP
#define RENDERERWIDGET_HPP
#include "../glad/glad.h"
#include <QOpenGLWidget>
#include <QOpenGLContext>

#include "../Renderer/renderer.hpp"

class RendererWidget : public QOpenGLWidget
{
public:
    RendererWidget(QWidget* parent) : QOpenGLWidget(parent) 
    { 
        renderer = std::make_shared<Renderer>();
    }

    void setScene(std::shared_ptr<Scene> new_scene)
    {
        scene = new_scene;
    }

protected:
    void initializeGL() override
    {
        QSize size = this->size();
        gladLoadGL();
        renderer->init(scene, size.width(), size.height());
    }

    void resizeGL(int w, int h) override
    {
        renderer->resize(scene, w, h);
    }

    void paintGL() override
    {
        renderer->render(scene);
    }
private:
    std::shared_ptr<Renderer> renderer;
    std::shared_ptr<Scene> scene;
};

#endif // RENDERERWIDGET_HPP
