/*
 * Based on rviz/default_plugin/map_display.cpp
 * 
 * Copyright (c) 2008, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#pragma once

#ifndef Q_MOC_RUN
#include <OGRE/OgreManualObject.h>
#include <OGRE/OgreMaterialManager.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreTextureManager.h>

#include <colored_occupancy_grid/ColoredOccupancyGrid.h>
#include <rviz/message_filter_display.h>
#endif

namespace Ogre 
{
class SceneNode;
}

namespace rviz 
{
class BoolProperty;
class FloatProperty;
class IntProperty;
class VectorProperty;
class QuaternionProperty;
}

namespace colored_occupancy_grid
{

class ColoredOccupancyGridDisplay : public rviz::MessageFilterDisplay<ColoredOccupancyGrid>
{
Q_OBJECT

public:
  ColoredOccupancyGridDisplay();
  virtual ~ColoredOccupancyGridDisplay();

  virtual void onInitialize();
  virtual void fixedFrameChanged();
  virtual void reset();
  virtual void onEnable();

protected Q_SLOTS:
  void updateAlpha();
  void updateDrawBehind();
  void updateDrawColorOnlyOnOccupiedCells();
  void updateOccupancyThreshold();

protected:

  virtual void processMessage(const ColoredOccupancyGrid::ConstPtr& msg);

  void clear();

  void transformMap();

  ColoredOccupancyGrid::ConstPtr last_msg_;

  Ogre::ManualObject* manual_object_;
  Ogre::TexturePtr texture_;
  Ogre::MaterialPtr material_;
  bool loaded_;

  std::string frame_;
  geometry_msgs::Pose latest_map_pose_;

  rviz::FloatProperty* alpha_property_;
  rviz::BoolProperty* draw_behind_property_;
  rviz::FloatProperty* resolution_property_;
  rviz::VectorProperty* position_property_;
  rviz::QuaternionProperty* orientation_property_;
  rviz::IntProperty* occupancy_threshold_property_;
  rviz::BoolProperty* draw_color_only_on_occupied_cells_property_;
};

}  // end namespace colored_occupancy_grid
