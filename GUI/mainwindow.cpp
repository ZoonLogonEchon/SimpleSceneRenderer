#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "rendererwidget.hpp"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    RendererWidget *r_widget = new RendererWidget(this);
    std::shared_ptr<Scene> sc = std::make_shared<Scene>("my scene");
    std::string rc_name = "test_rect";
    std::string cu_name = "test_cube";
    auto cube = sc->addCube(cu_name);
    cube->getComponent<Transform>()->scale(30.0f);
    cube->getComponent<Transform>()->translate(glm::vec3(0.0f, 0.0f, 2.0f));
    sc->getMainCamera()->getComponent<Transform>()->translate(glm::vec3(0.0f, 0.0f, 101.0f));
    r_widget->setScene(sc);
    ui->horizontalLayout->addWidget(r_widget);
    
}

