
"use strict";

let RestartController = require('./RestartController.js')
let SetComplianceSlope = require('./SetComplianceSlope.js')
let SetCompliancePunch = require('./SetCompliancePunch.js')
let SetComplianceMargin = require('./SetComplianceMargin.js')
let StopController = require('./StopController.js')
let TorqueEnable = require('./TorqueEnable.js')
let SetSpeed = require('./SetSpeed.js')
let SetTorqueLimit = require('./SetTorqueLimit.js')
let StartController = require('./StartController.js')

module.exports = {
  RestartController: RestartController,
  SetComplianceSlope: SetComplianceSlope,
  SetCompliancePunch: SetCompliancePunch,
  SetComplianceMargin: SetComplianceMargin,
  StopController: StopController,
  TorqueEnable: TorqueEnable,
  SetSpeed: SetSpeed,
  SetTorqueLimit: SetTorqueLimit,
  StartController: StartController,
};
