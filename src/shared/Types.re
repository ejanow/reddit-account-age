type user = {
  name: string,
  created_utc: float,
  link_karma: int,
  comment_karma: int,
  id: string,
  is_suspended: bool,
};

type userDict = Js.Dict.t(Js.Array.t(Dom.node));

type cacheState =
  | Cache
  | Queue
  | Error;

type cacheUser = {
  name: string,
  state: cacheState,
  user: Js.Nullable.t(user),
};

type getUsersRequest = {usernames: list(string)};

type getUsersResponse = {users: Js.Dict.t(cacheUser)};

type getStatusResponse = {
  queue: array(string),
  errors: array(string),
  queueCount: int,
  errorsCount: int,
  cacheCount: int,
};

type deleteErrorsResponse = {success: bool};

type count = {count: int};

module Decode = {
  open! Json.Decode;
  let user = (json: Js.Json.t) : user => {
    name: json |> field("name", string),
    created_utc: json |> (field("created_utc", float) |> withDefault(0.0)),
    link_karma: json |> (field("link_karma", int) |> withDefault(0)),
    comment_karma: json |> (field("comment_karma", int) |> withDefault(0)),
    id: json |> (field("id", string) |> withDefault("")),
    is_suspended:
      json |> (field("is_suspended", bool) |> withDefault(false)),
  };
  let count = (json: Js.Json.t) : count => {
    count: json |> (field("count", int) |> withDefault(0)),
  };
};

module Encode = {
  open! Json.Encode;
  let user = (user: user) : Js.Json.t =>
    object_([
      ("name", user.name |> string),
      ("created_utc", user.created_utc |> float),
      ("link_karma", user.link_karma |> int),
      ("comment_karma", user.comment_karma |> int),
      ("id", user.id |> string),
      ("is_suspended", user.is_suspended |> bool),
    ]);
};
