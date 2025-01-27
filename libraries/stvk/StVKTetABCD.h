/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 4.0                               *
 *                                                                       *
 * "StVK" library , Copyright (C) 2007 CMU, 2009 MIT, 2018 USC           *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code author: Jernej Barbic                                            *
 * http://www.jernejbarbic.com/vega                                      *
 *                                                                       *
 * Research: Jernej Barbic, Hongyi Xu, Yijing Li,                        *
 *           Danyong Zhao, Bohan Wang,                                   *
 *           Fun Shing Sin, Daniel Schroeder,                            *
 *           Doug L. James, Jovan Popovic                                *
 *                                                                       *
 * Funding: National Science Foundation, Link Foundation,                *
 *          Singapore-MIT GAMBIT Game Lab,                               *
 *          Zumberge Research and Innovation Fund at USC,                *
 *          Sloan Foundation, Okawa Foundation,                          *
 *          USC Annenberg Foundation                                     *
 *                                                                       *
 * This library is free software; you can redistribute it and/or         *
 * modify it under the terms of the BSD-style license that is            *
 * included with this library in the file LICENSE.txt                    *
 *                                                                       *
 * This library is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the file     *
 * LICENSE.TXT for more details.                                         *
 *                                                                       *
 *************************************************************************/

#ifndef VEGAFEM_STVKTETABCD_H
#define VEGAFEM_STVKTETABCD_H

#include "StVKElementABCD.h"
#include "tetMesh.h"

namespace vegafem
{

/*
  This class stores the St.Venant-Kirchhoff A,B,C,D coefficients for a tetrahedral element.
  This is the low-memory version (the version that we use most often).
  See also StVKInternalForces.h .
*/

class StVKTetABCD : public StVKElementABCD
{
public:

  // computes the ABCD coefficients 
  StVKTetABCD(TetMesh * tetMesh);

  virtual Mat3d A(void * elementIterator, int i, int j);
  virtual double B(void * elementIterator, int i, int j);
  virtual Vec3d C(void * elementIterator, int i, int j, int k);
  virtual double D(void * elementIterator, int i, int j, int k, int l);

  typedef struct
  {
    double volume;
    Vec3d Phig[4]; // gradient of a basis function
  } elementData;

  typedef struct
  {
    elementData * elementPointer;
    double dots[4][4];
  } ElementCache;

  void AllocateElementIterator(void ** elementIterator);
  void ReleaseElementIterator(void * elementIterator);
  void PrepareElement(int el, void * elementIterator); // must call each time before accessing an element

  virtual ~StVKTetABCD();

protected:

  elementData * elementsData;

  // creates the elementData structure for a tet
  void StVKSingleTetABCD(Vec3d vertices[4], elementData * target);
};


}//namespace vegafem

#endif


