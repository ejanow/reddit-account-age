// Generated by BUCKLESCRIPT VERSION 3.0.0, PLEASE EDIT WITH CARE
'use strict';


chrome.browserAction.onClicked.addListener((function (tab) {
        chrome.tabs.executeScript(tab.id, {
              file: "Inject.bs.js"
            });
        return /* () */0;
      }));

/*  Not a pure module */