//
// Created by clark on 2022/4/12.
//
#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "brain.h"

namespace minimetro {

class MiniMetroApp : public ci::app::App {
public:
    MiniMetroApp();

    void draw() override;
    void update() override;
    void mouseDown(ci::app::MouseEvent event) override;
    void mouseDrag(ci::app::MouseEvent event) override;

    const int kWindowSize = 875;

private:
    Brain brain_;
};

}
