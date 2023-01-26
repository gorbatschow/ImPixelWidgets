#include "RadarWidget.h"

RadarWidget::RadarWidget() {}

void RadarWidget::paint() {
  const auto flags_plt{ImPlotFlags_NoTitle | ImPlotFlags_NoLegend |
                       ImPlotFlags_NoMenus | ImPlotFlags_NoBoxSelect |
                       ImPlotFlags_Equal};

  if (ImPlot::BeginPlot("Plot", {-1, -1}, flags_plt)) {
    if (_pixelGrid) {
      ImPlot::PlotImage("Pixels", _pixelData.imID(), _boundsMin, _boundsMax);
    }

    if (_displayScatter) {
      ImPlot::PlotScatter("Nodes", _pixelGrid->xNodes2D(),
                          _pixelGrid->yNodes2D(), _pixelGrid->nodeSize());
    }

    ImPlot::EndPlot();
  }
}

void RadarWidget::setPixelGrid(std::shared_ptr<IPixelGrid> grid) {
  _pixelGrid.swap(grid);
  _pixelData.resize(_pixelGrid->pixelWidth(), _pixelGrid->pixelHeight());
  _pixelData.fill(ColorRGBA_Aqua);
  _pixelData.loadTexture();

  _boundsMin = _pixelGrid->boundsMin();
  _boundsMax = _pixelGrid->boundsMax();
}
