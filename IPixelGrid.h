#pragma once
#include "imgui.h"
#include <imgui.h>
#include <vector>

class IPixelGrid {
public:
  virtual ~IPixelGrid() = default;

  // Linear Node To Pixel
  virtual const std::vector<std::size_t> &nodeToPixel(std::size_t dim_0) const {
    return _emptyPixel;
  };

  // Node To Pixel
  virtual const std::vector<std::size_t> &nodeToPixel(std::size_t dim_1,
                                                      std::size_t dim_2) const {
    return _emptyPixel;
  };

  // Polar To Pixel
  virtual const std::vector<std::size_t> &polarToPixel(double r,
                                                       double phi) const {
    return _emptyPixel;
  };

  // Polar To Linear Node
  virtual void polarToNode(double r, double phi, std::size_t &dim_0) const {}

  // Polar To Node
  virtual void polarToNode(double r, double phi, std::size_t &dim_1,
                           std::size_t &dim_2) const {}

  // Cartesian To Pixel
  virtual const std::vector<std::size_t> &cartesianToPixel(double x,
                                                           double y) const {
    return _emptyPixel;
  };

  // Cartesian To Linear Node
  virtual void cartesianToNode(double x, double y, std::size_t &dim_0) const {}

  // Cartesian To Node
  virtual void cartesianToNode(double x, double y, std::size_t &dim_1,
                               std::size_t &dim_2) const {}

  // Sector To Pixel
  virtual bool
  sectorToPixel(double r, double phi_min, double phi_max,
                std::vector<std::vector<std::size_t>> &pixel_list) const {
    return false;
  }

  // Cartesian Bounds Min
  virtual ImVec2 cartesianBoundsMin() const { return {0, 0}; };

  // Cartesian Bounds Max
  virtual ImVec2 cartesianBoundsMax() const { return {0, 0}; };

  // Make Cartesian Mesh
  virtual void makeCartesianMesh(std::vector<double> &x,
                                 std::vector<double> &y) const {}

  // Make Polar Mesh
  virtual void makePolarMesh(std::vector<double> &r,
                             std::vector<double> &phi) const {}

  // Grid Size
  virtual std::size_t gridSize(std::size_t dim = 0) const { return 0; }

  // Polar Contains
  virtual bool polarContains(double r, double phi) const { return false; }

  // Cartesian Contains
  virtual bool cartesianContains(double x, double y) const { return false; }

  // Pixel Size
  virtual std::size_t pixelWidth() const { return 0; }
  virtual std::size_t pixelHeight() const { return 0; }

  // Distance Bounds
  virtual bool distanceBounds(double r, double &min, double &max) const {
    return false;
  }

  // Bearing Bounds
  virtual bool bearingBounds(double phi, double &min, double &max) const {
    return false;
  }

  // Distance Nodes
  virtual const std::vector<double> &distanceNodes(double bearing = 0) const {
    return _emptyNodes;
  }

  // Bearing Nodes
  virtual const std::vector<double> &bearingNodes(double distance = 0) const {
    return _emptyNodes;
  }

protected:
  inline const std::vector<std::size_t> &emptyPixel() const {
    return _emptyPixel;
  }

  inline const std::vector<double> &emptyNodes() const { return _emptyNodes; }

private:
  const std::vector<std::size_t> _emptyPixel{};
  const std::vector<double> _emptyNodes{};
};
