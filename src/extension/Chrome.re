type tabId;

type tab = {. "id": tabId};

type script = {. "file": string};

module BrowserAction = {
  [@bs.scope "chrome.browserAction.onClicked"] [@bs.val]
  external addOnClickedListener : (tab => unit) => unit = "addListener";
};

module Tabs = {
  [@bs.scope "chrome.tabs"] [@bs.val]
  external executeScript : (tabId, script) => unit = "";
};
