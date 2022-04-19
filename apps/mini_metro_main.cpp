#include "../include/simulator.h"

using minimetro::MiniMetroApp;

void prepareSettings(MiniMetroApp::Settings* settings) {
    settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(MiniMetroApp, ci::app::RendererGl, prepareSettings);