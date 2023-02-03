#pragma once
#include "imgui.h"
#include <imgui.h>
#include <vector>

class IPixelGrid {
public:
  virtual ~IPixelGrid() = default;

  // Index
  //----------------------------------------------------------------------------
  // to Pixel
  virtual const std::vector<std::size_t> &
  indexToPixel(std::size_t index) const {
    return _emptyPixel;
  };

  // Node
  //----------------------------------------------------------------------------
  // to Pixel
  virtual const std::vector<std::size_t> &nodeToPixel(std::size_t dim_1,
                                                      std::size_t dim_2) const {
    return _emptyPixel;
  };

  // Grid Size
  virtual std::size_t gridSize(std::size_t dim = 0) const { return 0; }

  // Pixel
  //----------------------------------------------------------------------------
  // Pixel Width
  virtual std::size_t pixelWidth() const { return 0; }

  // Pixel Height
  virtual std::size_t pixelHeight() const { return 0; }

  // Polar
  //----------------------------------------------------------------------------
  // to Pixel
  virtual const std::vector<std::size_t> &polarToPixel(double r,
                                                       double phi) const {
    return _emptyPixel;
  };

  // Sector to Pixel
  virtual bool
  sectorToPixel(double r, double phi_min, double phi_max,
                std::vector<std::vector<std::size_t>> &pixel_list) const {
    return false;
  }

  // to Index
  virtual void polarToIndex(double r, double phi, std::size_t &index) const {}

  // to Node
  virtual void polarToNode(double r, double phi, std::size_t &dim_1,
                           std::size_t &dim_2) const {}

  // Distance Nodes
  virtual const std::vector<double> &distanceNodes(double bearing = 0) const {
    return _emptyNodes;
  }

  // Bearing Nodes
  virtual const std::vector<double> &bearingNodes(double distance = 0) const {
    return _emptyNodes;
  }

  // Distance Bounds
  virtual bool distanceBounds(double r, double &min, double &max) const {
    return false;
  }

  // Bearing Bounds
  virtual bool bearingBounds(double phi, double &min, double &max) const {
    return false;
  }

  // Polar Contains
  virtual bool polarContains(double r, double phi) const { return false; }

  // Make Polar Mesh
  virtual void makePolarMesh(std::vector<double> &r,
                             std::vector<double> &phi) const {}

  // Cartesian
  //----------------------------------------------------------------------------
  // to Pixel
  virtual const std::vector<std::size_t> &cartesianToPixel(double x,
                                                           double y) const {
    return _emptyPixel;
  };

  // to Index
  virtual void cartesianToIndex(double x, double y, std::size_t &index) const {}

  // to Node
  virtual void cartesianToNode(double x, double y, std::size_t &dim_1,
                               std::size_t &dim_2) const {}

  // Cartesian Bounds Min
  virtual ImVec2 cartesianBoundsMin() const { return {0, 0}; };

  // Cartesian Bounds Max
  virtual ImVec2 cartesianBoundsMax() const { return {0, 0}; };

  // Make Cartesian Mesh
  virtual void makeCartesianMesh(std::vector<double> &x,
                                 std::vector<double> &y) const {}

  // Cartesian Contains
  virtual bool cartesianContains(double x, double y) const { return false; }

protected:
  inline const std::vector<std::size_t> &emptyPixel() const {
    return _emptyPixel;
  }

  inline const std::vector<double> &emptyNodes() const { return _emptyNodes; }

private:
  const std::vector<std::size_t> _emptyPixel{};
  const std::vector<double> _emptyNodes{};
};
