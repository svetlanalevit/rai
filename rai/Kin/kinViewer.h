/*  ------------------------------------------------------------------
    Copyright (c) 2017 Marc Toussaint
    email: marc.toussaint@informatik.uni-stuttgart.de
    
    This code is distributed under the MIT License.
    Please see <root-path>/LICENSE for details.
    --------------------------------------------------------------  */

#pragma once

#include <Core/thread.h>
#include <Gui/opengl.h>
#include "kin.h"
#include <Geo/mesh.h>

//===========================================================================

void renderConfigurations(const WorldL& cs, const char* filePrefix="vid/z.", int tprefix=0, int w=-1, int h=-1, mlr::Camera *camera=NULL);

//===========================================================================

struct OrsViewer_old : Thread {
  Var<mlr::KinematicWorld> modelWorld;
  //-- outputs
  Var<byteA> modelCameraView;
  Var<floatA> modelDepthView;
  //-- internal (private)
  mlr::KinematicWorld copy;
  bool computeCameraView;

  OrsViewer_old(const char* varname="modelWorld", double beatIntervalSec=-1., bool computeCameraView=false);
  ~OrsViewer_old();
  void open();
  void step();
  void close() {}
};

//===========================================================================

struct OrsViewer : Thread {
  Var<mlr::KinematicWorld> world;
  MeshA meshesCopy;
  ProxyA proxiesCopy;
  struct OpenGL *gl;
  OrsViewer(const char* world_name="modelWorld", double beatIntervalSec=-1.);
  ~OrsViewer();
  void open();
  void step();
  void close();
};

//===========================================================================

struct OrsPathViewer : Thread {
  Var<WorldL> configurations;
  //-- internal (private)
  mlr::KinematicWorld copy;
  uint t;
  int tprefix;
  bool writeToFiles;
  mlr::String text;

  void setConfigurations(const WorldL& cs);
  void clear();

  OrsPathViewer(const char* varname, double beatIntervalSec=.2, int tprefix=0);
  ~OrsPathViewer();
  void open();
  void step();
  void close(){}
};

//===========================================================================

struct OrsPoseViewer : Thread {
  Var<mlr::KinematicWorld> modelWorld;
  mlr::Array<Var<arr>*> poses; ///< poses to be watched
  //-- internal (private)
  OpenGL gl;
  mlr::KinematicWorld copy;
  WorldL copies;

  OrsPoseViewer(const char* modelVarName, const StringA& poseVarNames, double beatIntervalSec=-1.);
  ~OrsPoseViewer();

  void recopyKinematics(const mlr::KinematicWorld& world=NoWorld);

  void open();
  void step();
  void close();
};

//===========================================================================

struct ComputeCameraView : Thread {
  Var<mlr::KinematicWorld> modelWorld;
  Var<byteA> cameraView;
  Var<uint16A> cameraDepth;
  Var<mlr::Transformation> cameraFrame;

  //-- internal (private)
  OpenGL gl;
  mlr::KinematicWorld copy;
  bool getDepth;

  ComputeCameraView(double beatIntervalSec=-1., const char* modelWorld_name="modelWorld");
  ~ComputeCameraView();
  void open();
  void step();
  void close();
};

