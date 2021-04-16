
"use strict";

let GetWaypointByIndex = require('./GetWaypointByIndex.js')
let GetWaypointByName = require('./GetWaypointByName.js')
let SaveWaypoints = require('./SaveWaypoints.js')
let AddNewWaypoint = require('./AddNewWaypoint.js')
let GetNumOfWaypoints = require('./GetNumOfWaypoints.js')
let GetChargerByName = require('./GetChargerByName.js')

module.exports = {
  GetWaypointByIndex: GetWaypointByIndex,
  GetWaypointByName: GetWaypointByName,
  SaveWaypoints: SaveWaypoints,
  AddNewWaypoint: AddNewWaypoint,
  GetNumOfWaypoints: GetNumOfWaypoints,
  GetChargerByName: GetChargerByName,
};
