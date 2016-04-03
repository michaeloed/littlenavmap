/*****************************************************************************
* Copyright 2015-2016 Alexander Barthel albar965@mailbox.org
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#ifndef ROUTEMAPOBJECT_H
#define ROUTEMAPOBJECT_H

#include "common/maptypes.h"
#include "fs/pln/flightplanentry.h"

class MapQuery;

class RouteMapObject
{
public:
  RouteMapObject();
  RouteMapObject(atools::fs::pln::FlightplanEntry *planEntry, MapQuery *query,
                 const RouteMapObject *predRouteMapObj, int *userIdentIndex = nullptr);
  ~RouteMapObject();

  void update(const RouteMapObject *predRouteMapObj, int *userIdentIndex = nullptr);

  int getId() const;
  const atools::geo::Pos& getPosition() const;
  const QString& getIdent() const;
  const QString& getRegion() const;
  const QString& getName() const;
  int getFrequency() const;
  float getMagvar() const;
  int getRange() const;

  const atools::fs::pln::FlightplanEntry *getFlightplanEntry() const
  {
    return entry;
  }

  maptypes::MapObjectTypes getMapObjectType() const
  {
    return type;
  }

  bool isUser()
  {
    return entry->getWaypointType() == atools::fs::pln::entry::USER;
  }

  const maptypes::MapAirport& getAirport() const
  {
    return airport;
  }

  const maptypes::MapVor& getVor() const
  {
    return vor;
  }

  const maptypes::MapNdb& getNdb() const
  {
    return ndb;
  }

  const maptypes::MapWaypoint& getWaypoint() const
  {
    return waypoint;
  }

  bool hasPredecessor() const
  {
    return predecessor;
  }

  float getDistanceTo() const
  {
    return distanceTo;
  }

  float getDistanceToRhumb() const
  {
    return distanceToRhumb;
  }

  float getCourseTo() const
  {
    return courseTo;
  }

  float getCourseToRhumb() const
  {
    return courseRhumbTo;
  }

private:
  atools::fs::pln::FlightplanEntry *entry;
  QString userIdent;
  maptypes::MapObjectTypes type = maptypes::NONE;
  maptypes::MapAirport airport;
  maptypes::MapVor vor;
  maptypes::MapNdb ndb;
  maptypes::MapWaypoint waypoint;
  bool predecessor = false;

  float distanceTo = 0.f, distanceToRhumb = 0.f, courseTo = 0.f, courseRhumbTo = 0.f;
  void setUserIdent(int *userIdentIndex);
  void updateDistAndCourse(const RouteMapObject *predRouteMapObj);

};

#endif // ROUTEMAPOBJECT_H
