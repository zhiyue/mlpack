/**
 * @file tree/dhrectperiodicbound.h
 *
 * Bounds that are useful for binary space partitioning trees.
 *
 * This file describes the interface for the DHrectPeriodicBound policy, which
 * implements a hyperrectangle bound.
 *
 * @experimental
 */

#ifndef TREE_DHRECTPERIODICBOUND_H
#define TREE_DHRECTPERIODICBOUND_H

#include <armadillo>

/**
 * Hyper-rectangle bound for an L-metric.
 *
 * Template parameter t_pow is the metric to use; use 2 for Euclidean (L2).
 */
template<int t_pow = 2>
class DHrectPeriodicBound {

  public:
    static const int PREFERRED_POWER = t_pow;

  private:
    DRange *bounds_;
    index_t dim_;
    vec& box_size__;

  public:
    /**
     * Empty constructor.
     */
    DHrectPeriodicBound();

    /**
     * Initializes to specified dimensionality with each dimension the empty
     * set.
     */
    DHrectPeriodicBound(index_t dimension);

    /**
     * Destructor: clean up memory.
     */
    ~DHrectPeriodicBound();

    /**
     * Modifies the box_size__ to the desired dimenstions.
     */
    void SetBoxSize(vec& box);

    /**
     * Returns the box_size__ vector.
     */
    long GetBoxSize();    

    /**
     * Makes this (uninitialized) box the average of the two arguments, 
     * i.e. the max and min of each range is the average of the maxes and mins 
     * of the arguments.  
     *
     * Added by: Bill March, 5/7
     */
    void AverageBoxesInit(const DHrectBound& box1, const DHrectBound& box2);

    /**
     * Resets all dimensions to the empty set.
     */
    void Reset();

    /**
     * Sets the dimensionality of the bound.
     */
    void SetSize(index_t dim);

    /**
     * Determines if a point is within this bound.
     */
    bool Contains(const arma::vec& point) const;

    /** Gets the dimensionality */
    index_t dim() const { return dim_; }

    /**
     * Gets the range for a particular dimension.
     */
    const DRange operator[](index_t i) const;

    /**
     * Calculates the maximum distance within the rectangle
     */
    double CalculateMaxDistanceSq() const;

    /** Calculates the midpoint of the range */
    void CalculateMidpoint(arma::vec& centroid) const;

    /**
     * Calculates minimum bound-to-point squared distance.
     */
    double MinDistanceSq(const arma::vec& point) const;

    /**
     * Calculates minimum bound-to-bound squared distance.
     *
     * Example: bound1.MinDistanceSq(other) for minimum squared distance.
     */
    double MinDistanceSq(const DHrectBound& other) const;

    /**
     * Calculates maximum bound-to-point squared distance.
     */
    double MaxDistanceSq(const arma::vec& point) const;

    /**
     * Calculates maximum bound-to-point squared distance.
     */
    //double MaxDistanceSq(const double *point) const;

    /**
     * Computes maximum distance.
     */
    double MaxDistanceSq(const DHrectBound& other) const;

    /**
     * Computes maximum distance with offset
     */
    double MaxDistanceSq(const DHrectBound& other, const arma::vec& offset) const;

    double MaxDelta(const DHrectBound& other, double box_width, int dim) const;
    double MinDelta(const DHrectBound& other, double box_width, int dim) const;

    /**
     * Calculates minimum and maximum bound-to-bound squared distance.
     */
    DRange RangeDistanceSq(const DHrectBound& other) const;

    /**
     * Calculates minimum and maximum bound-to-point squared distance.
     */
    DRange RangeDistanceSq(const arma::vec& point) const;

    /**
     * Calculates closest-to-their-midpoint bounding box distance,
     * i.e. calculates their midpoint and finds the minimum box-to-point
     * distance.
     *
     * Equivalent to:
     * <code>
     * other.CalcMidpoint(&other_midpoint)
     * return MinDistanceSqToPoint(other_midpoint)
     * </code>
     */
    double MinToMidSq(const DHrectBound& other) const;

    /**
     * Computes minimax distance, where the other node is trying to avoid me.
     */
    double MinimaxDistanceSq(const DHrectBound& other) const;

    /**
     * Calculates midpoint-to-midpoint bounding box distance.
     */
    double MidDistanceSq(const DHrectBound& other) const;

    /**
     * Expands this region to include a new point.
     */
    DHrectPeriodicBound& operator|=(const arma::vec& vector);

    /**
     * Expands this region to encompass another bound.
     */
    DHrectPeriodicBound& operator|=(const DHrectBound& other);

    /**
     * Expand this bounding box to encompass another point. Done to 
     * minimize added volume in periodic coordinates.
     */
    DHrectPeriodicBound& Add(const arma::vec& other, const arma::vec& size);

    /**
     * Expand this bounding box in periodic coordinates, minimizing added volume
     */
    DHrectPeriodicBound& Add(const DHrectBound& other, const arma::vec& size);
};

#include "dhrectperiodicbound_impl.h"

#endif