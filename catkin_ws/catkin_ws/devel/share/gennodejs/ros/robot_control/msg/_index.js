
"use strict";

let rigid = require('./rigid.js');
let state = require('./state.js');
let newtactile = require('./newtactile.js');
let fsrInput = require('./fsrInput.js');
let coord = require('./coord.js');
let contact = require('./contact.js');
let tactile = require('./tactile.js');
let accelerometr = require('./accelerometr.js');

module.exports = {
  rigid: rigid,
  state: state,
  newtactile: newtactile,
  fsrInput: fsrInput,
  coord: coord,
  contact: contact,
  tactile: tactile,
  accelerometr: accelerometr,
};
