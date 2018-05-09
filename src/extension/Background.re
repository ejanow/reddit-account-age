open Chrome;

BrowserAction.addOnClickedListener(tab =>
  Tabs.executeScript(tab##id, {"file": "Inject.bs.js"})
);
