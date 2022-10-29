/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 4.0                               *
 *                                                                       *
 * "integrator" library , Copyright (C) 2007 CMU, 2009 MIT, 2018 USC     *
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
  A base class to timestep large sparse dynamics.
  E.g., unreduced nonlinear FEM deformable dynamics.

  See also integratorBase.h .
*/

#ifndef VEGAFEM_INTEGRATORBASESPARSE_H
#define VEGAFEM_INTEGRATORBASESPARSE_H

#include "sparseMatrix.h"
#include "forceModel.h"
#include "integratorBase.h"

class IntegratorBaseSparse : public IntegratorBase
{
public:

  // constrainedDOFs is an integer array of degrees of freedom that are to be fixed to zero (e.g., to permanently fix a vertex in a deformable simulation)
  // constrainedDOFs are 0-indexed (separate DOFs for x,y,z), and must be pre-sorted (ascending)
  // damping matrix provides damping in addition to mass and stiffness damping
  IntegratorBaseSparse(int r, double timestep, SparseMatrix * massMatrix, ForceModel * forceModel, int numConstrainedDOFs=0, int * constrainedDOFs=NULL, double dampingMassCoef=0.0, double dampingStiffnessCoef=0.0);

  virtual ~IntegratorBaseSparse();

  inline virtual void SetForceModel(ForceModel * forceModel) { this->forceModel = forceModel; }

  // damping matrix provides damping in addition to mass and stiffness damping (it does not replace it)
  virtual void SetDampingMatrix(SparseMatrix * dampingMatrix);

  // add an offset to the tangent stiffness matrix (default: no offset)
  virtual void SetTangentStiffnessMatrixOffset(SparseMatrix * tangentStiffnessMatrixOffset, int reuseTopology=1); // you must use reuseTopology=0 if the offset has been previously already set, and the topology of the new tangentStiffnessMatrixOffset matrix is different from the old one
  virtual void AddTangentStiffnessMatrixOffset(SparseMatrix * tangentStiffnessMatrixOffset); // the operand must have same topology as the previously set tangent stiffness matrix
  virtual void ClearTangentStiffnessMatrixOffset();

  // performs one step of simulation (returns 0 on sucess, and 1 on failure)
  // failure can occur, for example, if you are using the positive definite solver and the system matrix has negative eigenvalues
  virtual int DoTimestep() = 0;

  // returns the execution time of the last r x r linear system solve
  inline virtual double GetSystemSolveTime() { return systemSolveTime; }
  inline virtual double GetForceAssemblyTime() { return forceAssemblyTime; }

  virtual double GetKineticEnergy();
  virtual double GetTotalMass();

protected:
  SparseMatrix * massMatrix; 
  ForceModel * forceModel;
  int ownDampingMatrix;
  SparseMatrix * dampingMatrix;
  
  SparseMatrix * tangentStiffnessMatrixOffset;

  int numConstrainedDOFs;
  int * constrainedDOFs;

  double systemSolveTime;
  double forceAssemblyTime;
};

#endif

