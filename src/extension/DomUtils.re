open Webapi.Dom;

module Styles = {
  open Css;
  let tooltip =
    style([
      visibility(hidden),
      zIndex(2),
      backgroundColor(black),
      opacity(0.8),
    ]);
  let raa =
    style([
      marginLeft @@ px(8),
      height @@ px(20),
      fontWeight(400),
      maxWidth @@ px(255),
      borderRadius @@ px(4),
      alignItems(center),
      textAlign(center),
      padding2(~v=px(0), ~h=px(8)),
      color(white) |> important,
      fontSize @@ px(11),
      selector(":hover ." ++ tooltip, [visibility(visible)]),
      selector(
        "& ." ++ tooltip,
        [
          position(absolute),
          padding2(~v=px(2), ~h=px(8)),
          height @@ px(16),
          width @@ px(50),
          pointerEvents(none),
        ],
      ),
    ]);
};

let getUsernameToElementArrayDict = () : Types.userDict =>
  Document.querySelectorAll(".author:not(.raa-dirty)", document)
  |> NodeList.toArray
  |> Js.Array.reduce(
       (dict, node) => {
         let username = Webapi.Dom.Node.innerText(node);
         switch (dict |. Js.Dict.get(username)) {
         | None => Js.Dict.set(dict, username, [|node|])
         | Some(nodes) => Js.Array.push(node, nodes) |> ignore
         };
         dict;
       },
       Js.Dict.empty(),
     );

let getAccountAge = (user: Types.user) : (int, int) => {
  let msYear = 31536000.0;
  let msDay = 86400.0;
  let delta = Js.Date.now() /. 1000.0 -. user.created_utc;
  let years = Js.Math.floor_float(delta /. msYear);
  let days = Js.Math.floor_float((delta -. years *. 365.0 *. msDay) /. msDay);
  (int_of_float(years), int_of_float(days));
};

let getBadgeInnerText = ((years, days)) : string =>
  switch (years < 1, days < 180) {
  | (true, _) => {j|$(days)d|j}
  | (_, true) => {j|$(years)y|j}
  | _ => {j|$(years).5y|j}
  };

let createTooltip = ((years, days)) => {
  let tooltip =
    Webapi.Dom.Document.createElement("span", Webapi.Dom.document);
  let raa = Styles.raa;
  let tooltipStyle = Styles.tooltip;
  Webapi.Dom.Element.setClassName(tooltip, {j|$raa $tooltipStyle|j});
  Webapi.Dom.Element.setInnerText(tooltip, {j|$(years)y $(days)d|j});
  tooltip;
};

let createElement = (user: Types.user) => {
  let age = getAccountAge(user);
  let ele = Webapi.Dom.Document.createElement("span", Webapi.Dom.document);
  let color = Color.getColor(age);
  let raa = Styles.raa;
  Webapi.Dom.Element.setClassName(ele, {j|$raa $color|j});
  getBadgeInnerText(age) |> Webapi.Dom.Element.setInnerText(ele);
  createTooltip(age) |. Webapi.Dom.Element.appendChild(ele);
  ele;
};

let addDirtyClassName = node =>
  switch (node |> Webapi.Dom.Element.ofNode) {
  | None => ignore()
  | Some(ele) =>
    Webapi.Dom.Element.setClassName(
      ele,
      Webapi.Dom.Element.className(ele) ++ " raa-dirty",
    )
  };

let insertElement = (authorNode, user) => {
  addDirtyClassName(authorNode);
  let badge = user |> createElement;
  let parent = authorNode |> Webapi.Dom.Node.parentElement |> Js.Option.getExn;
  let nextSibling: Dom.node =
    Webapi.Dom.Node.nextSibling(authorNode)
    |> Js.Nullable.fromOption
    |> Obj.magic;
  Webapi.Dom.Element.insertBefore(badge, nextSibling, parent) |> ignore;
};
