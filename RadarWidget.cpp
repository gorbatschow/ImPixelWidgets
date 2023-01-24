#include "RadarWidget.h"

RadarWidget::RadarWidget() { setGrid(_grid); }

void RadarWidget::paint() {
  const auto flags_plt{ImPlotFlags_NoTitle | ImPlotFlags_NoLegend |
                       ImPlotFlags_NoMenus | ImPlotFlags_NoBoxSelect |
                       ImPlotFlags_Equal};

  if (ImPlot::BeginPlot("Plot", {-1, -1}, flags_plt)) {
    ImPlot::PlotImage("Pixels", _pixels.imID(), _boundsMin, _boundsMax);

    if (_displayScatter) {
      ImPlot::PlotScatter("Nodes", _grid.xNodes().data(), _grid.yNodes().data(),
                          _grid.xNodes().size());
    }

    ImPlot::EndPlot();
  }
}

void RadarWidget::setGrid(const PolarGrid &grid) {
  _grid = grid;
  _pixels.resize(_grid.pixelWidth(), _grid.pixelHeight());
  _pixels.fill(ColorRGBA_Aqua);
  _pixels.loadTexture();

  const auto r{_grid.distanceMax()};
  _boundsMin = {float(-r), float(-r)};
  _boundsMax = {float(+r), float(+r)};
}
