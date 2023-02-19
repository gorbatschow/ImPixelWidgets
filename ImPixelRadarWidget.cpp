#include "ImPixelRadarWidget.h"

namespace ImPixel {
RadarWidget::RadarWidget() {}

void RadarWidget::paint() {
  const auto flags_plt{ImPlotFlags_NoTitle | ImPlotFlags_NoLegend |
                       ImPlotFlags_NoMenus | ImPlotFlags_NoBoxSelect |
                       ImPlotFlags_Equal};

  if (ImPlot::BeginPlot("Plot", {-1, -1}, flags_plt)) {

    ImPlot::PlotImage("Pixels", _pixelData.imID(), _boundsMin, _boundsMax);

    /*
        if (_displayScatter) {
          ImPlot::SetNextMarkerStyle(ImPlotMarker_Cross, IMPLOT_AUTO,
                                     IMPLOT_AUTO_COL, IMPLOT_AUTO, {0, 0, 0,
       255}); ImPlot::PlotScatter("Nodes", _xGridNodes.data(),
       _yGridNodes.data(), _xGridNodes.size());
        }
        */
    ImPlot::EndPlot();
  }
}

void RadarWidget::fillImage(const GridData &data) {
  _pixelData.resize(data.grid().pixelWidth(), data.grid().pixelHeight());
  _boundsMin = data.grid().cartesianBoundsMin();
  _boundsMax = data.grid().cartesianBoundsMax();

  for (std::size_t dim_0{}; dim_0 != data.size(); ++dim_0) {
    _pixelData.fill(data.pixel(dim_0),
                    _colorScheme->valueToColor(data.value(dim_0)));
  }
}
} // namespace ImPixel
