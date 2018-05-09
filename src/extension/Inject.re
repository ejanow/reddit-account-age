open Webapi.Dom;

let handleResponse =
    (usersResponse: Types.getUsersResponse, userDict: Types.userDict) =>
  usersResponse.users
  |> Js.Dict.entries
  |> Js.Array.filter(((_key, cacheUser)) => cacheUser.Types.state === Cache)
  |> Js.Array.forEach(((username, cacheUser): (string, Types.cacheUser)) => {
       let user = cacheUser.user |> Js.Nullable.toOption |> Js.Option.getExn;
       userDict
       |. Js.Dict.unsafeGet(username)
       |> Js.Array.forEach(authorNode =>
            DomUtils.insertElement(authorNode, user)
          );
     });

let getUsernames = (dict: Types.userDict) : list(string) =>
  Js.Dict.keys(dict) |> Array.to_list;

let main = () => {
  Js.log("[Main Fired]"); /* TODO: Remove Before Release */
  let userDict = DomUtils.getUsernameToElementArrayDict();
  let usernames = getUsernames(userDict);
  if (List.length(usernames) > 0) {
    ApiClient.getUsers(usernames)
    |> Util.thenIgnore(usersResponse =>
         handleResponse(usersResponse, userDict)
       );
  };
};

let throttledMain = Util.throttle(main, 1000 * 2);

let getNodeName = mutationRecord =>
  mutationRecord
  |> Webapi.Dom.MutationRecord.target
  |> Webapi.Dom.Node.nodeName;

let shouldIgnoreUpdate = arr =>
  arr |> Js.Array.some(x => x == "P" || x == "TIME");

Webapi.Dom.MutationObserver.(
  make((mutationRecordArray, _obs) => {
    let ignoreUpdate =
      mutationRecordArray |> Js.Array.map(getNodeName) |> shouldIgnoreUpdate;
    if (! ignoreUpdate) {
      throttledMain();
    };
  })
  |> observe(document, {"childList": true, "subtree": true})
);

throttledMain();
