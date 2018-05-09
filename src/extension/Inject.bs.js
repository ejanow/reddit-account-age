// Generated by BUCKLESCRIPT VERSION 3.0.0, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var Util = require("../shared/Util.bs.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Js_dict = require("bs-platform/lib/js/js_dict.js");
var DomUtils = require("./DomUtils.bs.js");
var ApiClient = require("../shared/ApiClient.bs.js");
var Js_option = require("bs-platform/lib/js/js_option.js");
var Js_primitive = require("bs-platform/lib/js/js_primitive.js");

function handleResponse(usersResponse, userDict) {
  Js_dict.entries(usersResponse[/* users */0]).filter((function (param) {
            return param[1][/* state */1] === /* Cache */0;
          })).forEach((function (param) {
          var user = Js_option.getExn(Js_primitive.null_undefined_to_opt(param[1][/* user */2]));
          userDict[param[0]].forEach((function (authorNode) {
                  return DomUtils.insertElement(authorNode, user);
                }));
          return /* () */0;
        }));
  return /* () */0;
}

function getUsernames(dict) {
  return $$Array.to_list(Object.keys(dict));
}

function main() {
  console.log("[Main Fired]");
  var userDict = DomUtils.getUsernameToElementArrayDict(/* () */0);
  var usernames = $$Array.to_list(Object.keys(userDict));
  if (List.length(usernames) > 0) {
    return Util.thenIgnore((function (usersResponse) {
                  return handleResponse(usersResponse, userDict);
                }), ApiClient.getUsers(usernames));
  } else {
    return 0;
  }
}

var throttledMain = Util.throttle(main, 2000);

function getNodeName(mutationRecord) {
  return mutationRecord.target.nodeName;
}

function shouldIgnoreUpdate(arr) {
  return arr.some((function (x) {
                if (x === "P") {
                  return true;
                } else {
                  return x === "TIME";
                }
              }));
}

new MutationObserver((function (mutationRecordArray, _) {
          var ignoreUpdate = shouldIgnoreUpdate(mutationRecordArray.map(getNodeName));
          if (ignoreUpdate) {
            return 0;
          } else {
            return throttledMain(/* () */0);
          }
        })).observe(document, {
      childList: true,
      subtree: true
    });

throttledMain(/* () */0);

exports.handleResponse = handleResponse;
exports.getUsernames = getUsernames;
exports.main = main;
exports.throttledMain = throttledMain;
exports.getNodeName = getNodeName;
exports.shouldIgnoreUpdate = shouldIgnoreUpdate;
/* throttledMain Not a pure module */
