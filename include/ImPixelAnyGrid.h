#pragma once
#include "ImPixelCoordinateSystem.h"
#include <imgui.h>
#include <stdexcept>
#include <vector>

namespace ImPixel {
class AnyGrid {
  class NotImplementedException : public std::logic_error {
  public:
    NotImplementedException(const std::string &func_name)
        : std::logic_error{"IPixelGrid::" + func_name + " not implemented"} {}
  };

public:
  virtual ~AnyGrid() = default;

  // General
  //----------------------------------------------------------------------------
  template <CoordinateSystem::Type T_cs, typename T_dim>
  void toIndex(std::size_t &index, const T_dim &dim_1,
               const T_dim &dim_2 = {}) {
    if constexpr (T_cs == CoordinateSystem::Type::Index) {
    } else if constexpr (T_cs == CoordinateSystem::Type::Node) {
      nodeToIndex(index, dim_1, dim_2);
    } else if constexpr (T_cs == CoordinateSystem::Type::Cartesian) {
      cartesianToIndex(index, dim_1, dim_2);
    } else if constexpr (T_cs == CoordinateSystem::Type::Polar) {
      polarToIndex(index, dim_1, dim_2);
    } else if constexpr (T_cs == CoordinateSystem::Type::Biangular) {
    }
  }

  // Index
  //----------------------------------------------------------------------------
  // to Pixel
  virtual const std::vector<std::size_t> &
  indexToPixel(std::size_t index) const {
    throw NotImplementedException(__func__);
    return emptyPixel();
  };

  // toNode
  virtual bool indexToNode(std::size_t &dim_1, std::size_t &dim_2,
                           std::size_t index) const {
    throw NotImplementedException(__func__);
  }

  // contains
  virtual bool indexContains(std::size_t &index) const {
    throw NotImplementedException(__func__);
    return false;
  }

  // Node
  //----------------------------------------------------------------------------
  // to Pixel
  virtual const std::vector<std::size_t> &nodeToPixel(std::size_t dim_1,
                                                      std::size_t dim_2) const {
    throw NotImplementedException(__func__);
    return emptyPixel();
  };

  // to Index
  virtual bool nodeToIndex(std::size_t &index, std::size_t dim_1,
                           std::size_t dim_2) const {
    throw NotImplementedException(__func__);
  }

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
    return emptyPixel();
  };

  // Sector to Pixel
  virtual bool sectorToPixel(std::vector<std::vector<std::size_t>> &pixel_list,
                             double r, double phi_min, double phi_max) const {
    throw NotImplementedException(__func__);
    return false;
  }

  // to Index
  virtual bool polarToIndex(std::size_t &index, double r, double phi) const {
    throw NotImplementedException(__func__);
    return false;
  }

  // to Node
  virtual bool polarToNode(std::size_t &dim_1, std::size_t &dim_2, double r,
                           double phi) const {
    throw NotImplementedException(__func__);
    return false;
  }

  // Distance Nodes
  virtual const std::vector<double> &distanceNodes(double bearing = 0) const {
    throw NotImplementedException(__func__);
    return emptyNodes();
  }

  // Bearing Nodes
  virtual const std::vector<double> &bearingNodes(double distance = 0) const {
    throw NotImplementedException(__func__);
    return emptyNodes();
  }

  // Distance Bounds
  virtual bool distanceBounds(double &min, double &max, double r) const {
    throw NotImplementedException(__func__);
    return false;
  }

  // Bearing Bounds
  virtual bool bearingBounds(double &min, double &max, double phi) const {
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
    return emptyPixel();
  };

  // to Index
  virtual bool cartesianToIndex(std::size_t &index, double x, double y) const {
    throw NotImplementedException(__func__);
  }

  // to Node
  virtual bool cartesianToNode(std::size_t &dim_1, std::size_t &dim_2, double x,
                               double y) const {
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
    static const std::vector<std::size_t> emptyPixel{};
    return emptyPixel;
  }

  inline const std::vector<double> &emptyNodes() const {
    static const std::vector<double> emptyNodes{};
    return emptyNodes;
  }
};
} // namespace ImPixel
