/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 4.0                               *
 *                                                                       *
 * "elasticForceModel" library , Copyright (C) 2007 CMU, 2009 MIT,       *
 *                                                       2018 USC        *
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

/*
  Reduced linear StVK force model.
*/

#ifndef VEGAFEM_REDUCEDLINEARSTVKFORCEMODEL_H
#define VEGAFEM_REDUCEDLINEARSTVKFORCEMODEL_H

#include "reducedForceModel.h"
#include "StVKReducedStiffnessMatrix.h"

class ReducedLinearStVKForceModel : public ReducedForceModel
{
public:
  ReducedLinearStVKForceModel(StVKReducedStiffnessMatrix * stVKReducedStiffnessMatrix);
  ReducedLinearStVKForceModel(int r, double * K);

  virtual void GetInternalForce(double * q, double * internalForces); 
  virtual void GetTangentStiffnessMatrix(double * q, double * tangentStiffnessMatrix);
  virtual void GetTangentHessianTensor(double * q, double * tangentHessianTensor);

protected:
  double * K;
};

#endif

