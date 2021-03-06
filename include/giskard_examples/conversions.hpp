/*
* Copyright (C) 2016 Georg Bartels <georg.bartels@cs.uni-bremen.de>
*
* This file is part of giskard_examples.
*
* giskard_examples is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef __GISKARD_CONVERSIONS_HPP__
#define __GISKARD_CONVERSIONS_HPP__

#include <functional>
#include <string>
#include <Eigen/Dense>
#include <kdl_conversions/kdl_msg.h>

namespace giskard_examples
{
  inline Eigen::VectorXd to_eigen(const std::vector<double>& v)
  {
    Eigen::VectorXd result(v.size());
    for (size_t i=0; i<v.size(); ++i)
      result[i] = v[i];
    return result;
  }

  inline Eigen::VectorXd to_eigen(const geometry_msgs::Pose& p)
  {
    Eigen::VectorXd result(6);
    result[0] = p.position.x;
    result[1] = p.position.y;
    result[2] = p.position.z;
  
    KDL::Rotation rot;
    tf::quaternionMsgToKDL(p.orientation, rot);
    rot.GetEulerZYX(result[3], result[4], result[5]);

    return result;
  }

  inline geometry_msgs::PoseStamped to_msg(const ros::Time& stamp,
      const std::string& frame_id, const KDL::Frame& pose)
  {
    geometry_msgs::PoseStamped result;
    result.header.stamp = stamp;
    result.header.frame_id = frame_id;
    tf::poseKDLToMsg(pose, result.pose);
    return result;
  }

}

#endif // __GISKARD_CONVERSIONS__HPP
