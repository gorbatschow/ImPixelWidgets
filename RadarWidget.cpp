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
      ImPlot::SetNextMarkerStyle(ImPlotMarker_Asterisk, IMPLOT_AUTO,
                                 IMPLOT_AUTO_COL, IMPLOT_AUTO, {0, 0, 0, 255});
      ImPlot::PlotScatter("Nodes", _xGridNodes.data(), _yGridNodes.data(),
                          _xGridNodes.size());

      ImPlot::SetNextMarkerStyle(ImPlotMarker_Cross, IMPLOT_AUTO,
                                 IMPLOT_AUTO_COL, IMPLOT_AUTO, {0, 0, 0, 255});
      ImPlot::PlotScatter("Nodes", _xSubGridNodes.data(), _ySubGridNodes.data(),
                          _xSubGridNodes.size());
    }
    ImPlot::EndPlot();
  }
}

void RadarWidget::setPixelGrid(std::shared_ptr<IPixelGrid> grid) {
  _pixelGrid.swap(grid);
  _pixelData.clear();
  _pixelData.resize(_pixelGrid->pixelWidth(), _pixelGrid->pixelHeight());
  _pixelData.loadTexture();

  _boundsMin = _pixelGrid->cartesianBoundsMin();
  _boundsMax = _pixelGrid->cartesianBoundsMax();
  _xGridNodes.clear();
  _yGridNodes.clear();
  _pixelGrid->makeCartesianMesh(_xGridNodes, _yGridNodes);
}

void RadarWidget::setPixelSubGrid(std::shared_ptr<IPixelGrid> subgrid) {
  _pixelSubGrid.swap(subgrid);
  _xSubGridNodes.clear();
  _ySubGridNodes.clear();
  if (_pixelSubGrid) {
    _pixelSubGrid->makeCartesianMesh(_xSubGridNodes, _ySubGridNodes);
  }
}
