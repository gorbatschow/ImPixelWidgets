#pragma once
#include "imgui.h"
#include <imgui.h>
#include <stdexcept>
#include <vector>

class IPixelGrid {
  class NotImplementedException : public std::logic_error {
  public:
    NotImplementedException(const std::string &func_name)
        : std::logic_error{"IPixelGrid::" + func_name + " not implemented"} {}
  };

public:
  virtual ~IPixelGrid() = default;

  // Index
  //----------------------------------------------------------------------------
  // to Pixel
  virtual const std::vector<std::size_t> &
  indexToPixel(std::size_t index) const {
    throw NotImplementedException(__func__);
    return _emptyPixel;
  };

  // Node
  //----------------------------------------------------------------------------
  // to Pixel
  virtual const std::vector<std::size_t> &nodeToPixel(std::size_t dim_1,
                                                      std::size_t dim_2) const {
    throw NotImplementedException(__func__);
    return _emptyPixel;
  };

  // Grid Size
  virtual std::size_t gridSize(std::size_t dim = 0) const {
    throw NotImplementedException(__func__);
    return 0;
  }

  // Pixel
  //----------------------------------------------------------------------------
  // Pixel Width
  virtual std::size_t pixelWidth() const {
    throw NotImplementedException(__func__);
    return 0;
  }

  // Pixel Height
  virtual std::size_t pixelHeight() const {
    throw NotImplementedException(__func__);
    return 0;
  }

  // Polar
  //----------------------------------------------------------------------------
  // to Pixel
  virtual const std::vector<std::size_t> &polarToPixel(double r,
                                                       double phi) const {
    throw NotImplementedException(__func__);
    return _emptyPixel;
  };

  // Sector to Pixel
  virtual bool
  sectorToPixel(double r, double phi_min, double phi_max,
                std::vector<std::vector<std::size_t>> &pixel_list) const {
    throw NotImplementedException(__func__);
    return false;
  }

  // to Index
  virtual void polarToIndex(double r, double phi, std::size_t &index) const {
    throw NotImplementedException(__func__);
  }

  // to Node
  virtual void polarToNode(double r, double phi, std::size_t &dim_1,
                           std::size_t &dim_2) const {
    throw NotImplementedException(__func__);
  }

  // Distance Nodes
  virtual const std::vector<double> &distanceNodes(double bearing = 0) const {
    throw NotImplementedException(__func__);
    return _emptyNodes;
  }

  // Bearing Nodes
  virtual const std::vector<double> &bearingNodes(double distance = 0) const {
    throw NotImplementedException(__func__);
    return _emptyNodes;
  }

  // Distance Bounds
  virtual bool distanceBounds(double r, double &min, double &max) const {
    throw NotImplementedException(__func__);
    return false;
  }

  // Bearing Bounds
  virtual bool bearingBounds(double phi, double &min, double &max) const {
    throw NotImplementedException(__func__);
    return false;
  }

  // Polar Contains
  virtual bool polarContains(double r, double phi) const {
    throw NotImplementedException(__func__);
    return false;
  }

  // Make Polar Mesh
  virtual void makePolarMesh(std::vector<double> &r,
                             std::vector<double> &phi) const {
    throw NotImplementedException(__func__);
  }

  // Cartesian
  //----------------------------------------------------------------------------
  // to Pixel
  virtual const std::vector<std::size_t> &cartesianToPixel(double x,
                                                           double y) const {
    throw NotImplementedException(__func__);
    return _emptyPixel;
  };

  // to Index
  virtual void cartesianToIndex(double x, double y, std::size_t &index) const {
    throw NotImplementedException(__func__);
  }

  // to Node
  virtual void cartesianToNode(double x, double y, std::size_t &dim_1,
                               std::size_t &dim_2) const {
    throw NotImplementedException(__func__);
  }

  // Cartesian Bounds Min
  virtual ImVec2 cartesianBoundsMin() const {
    throw NotImplementedException(__func__);
    return {0, 0};
  };

  // Cartesian Bounds Max
  virtual ImVec2 cartesianBoundsMax() const {
    throw NotImplementedException(__func__);
    return {0, 0};
  };

  // Make Cartesian Mesh
  virtual void makeCartesianMesh(std::vector<double> &x,
                                 std::vector<double> &y) const {
    throw NotImplementedException(__func__);
  }

  // Cartesian Contains
  virtual bool cartesianContains(double x, double y) const {
    throw NotImplementedException(__func__);
    return false;
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
