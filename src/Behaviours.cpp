/*
 * Behaviours.cpp
 *
 *  Created on: Dec 29, 2016
 *      Author: sajjadmuscle
 */

#include "Behaviours.h"

using namespace au;

Behaviours::Behaviours()
{
  takeoff_cl = n.serviceClient<mavros_msgs::CommandTOL>("/mavros/cmd/takeoff");
  cl_mode = n.serviceClient<mavros_msgs::SetMode>("/mavros/set_mode");
  arming_cl = n.serviceClient<mavros_msgs::CommandBool>("/mavros/cmd/arming");
  waypoint_cl = n.serviceClient<mavros_msgs::WaypointPush>("/mavros/mission/push");
}

Behaviours::~Behaviours()
{
  // TODO Auto-generated destructor stub
}

void Behaviours::takeOff(const QString &value)
{
  srv_takeoff.request.altitude = value.toInt();
  srv_takeoff.request.latitude = 0;
  srv_takeoff.request.longitude = 0;
  srv_takeoff.request.min_pitch = 0;
  srv_takeoff.request.yaw = 0;
  if (takeoff_cl.call(srv_takeoff))
  {
    ROS_ERROR("srv_takeoff send ok");
  }
  else
  {
    ROS_ERROR("Failed Takeoff");
  }
}

void Behaviours::guidedMode()
{
  srv_setMode.request.base_mode = 0;
  srv_setMode.request.custom_mode = "GUIDED";
  if (cl_mode.call(srv_setMode))
  {
    ROS_ERROR("setmode send ok");
  }
  else
  {
    ROS_ERROR("Failed SetMode");
  }
}

void Behaviours::landMode()
{
  srv_setMode.request.base_mode = 0;
  srv_setMode.request.custom_mode = "LAND";
  if (cl_mode.call(srv_setMode))
  {
    ROS_ERROR("setmode send ok");
  }
  else
  {
    ROS_ERROR("Failed SetMode");
  }
}

void Behaviours::rtlMode()
{
  srv_setMode.request.base_mode = 0;
  srv_setMode.request.custom_mode = "RTL";
  if (cl_mode.call(srv_setMode))
  {
    ROS_ERROR("setmode send ok");
  }
  else
  {
    ROS_ERROR("Failed SetMode");
  }
}

void Behaviours::arm()
{
  srv_arm.request.value = true;
  if (arming_cl.call(srv_arm))
  {
    ROS_ERROR("ARM send ok ");
  }
  else
  {
    ROS_ERROR("Failed arming or disarming");
  }
}

void Behaviours::gotoWp(double lat, double lon, int alt)
{
  waypoint.frame = 3;
  waypoint.command = 16;
  waypoint.is_current = 2;
  waypoint.autocontinue = 0;
  waypoint.x_lat = lat;
  waypoint.param1 = 0;
  waypoint.param2 = 0;
  waypoint.param3 = 0;
  waypoint.param4 = 0;
  waypoint.y_long = lon;
  waypoint.z_alt = alt;
  waypoint_push.request.waypoints.push_back(waypoint);
  if (waypoint_cl.call(waypoint_push))
  {
    ROS_INFO("  go to waypoint  ");
  }
  else
    ROS_INFO("  cant go to waypoint  ");

}