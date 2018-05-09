// Generated by BUCKLESCRIPT VERSION 3.0.0, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var Js_option = require("bs-platform/lib/js/js_option.js");

function thenResolve(fn, p) {
  return p.then((function (value) {
                return Promise.resolve(Curry._1(fn, value));
              }));
}

function thenIgnore(fn, p) {
  thenResolve(fn, p);
  return /* () */0;
}

function catchResolve(fn, p) {
  return p.catch((function (value) {
                return Promise.resolve(Curry._1(fn, value));
              }));
}

function catchIgnore(fn, p) {
  catchResolve(fn, p);
  return /* () */0;
}

function singletonList(item) {
  return /* :: */[
          item,
          /* [] */0
        ];
}

function throttle(callback, delay) {
  var timeout = [/* None */0];
  var later = function () {
    Curry._1(callback, /* () */0);
    timeout[0] = /* None */0;
    return /* () */0;
  };
  return (function () {
      if (Js_option.isNone(timeout[0])) {
        timeout[0] = /* Some */[setTimeout(later, delay)];
        return /* () */0;
      } else {
        return 0;
      }
    });
}

exports.thenResolve = thenResolve;
exports.thenIgnore = thenIgnore;
exports.catchResolve = catchResolve;
exports.catchIgnore = catchIgnore;
exports.singletonList = singletonList;
exports.throttle = throttle;
/* No side effect */
