open Axios;

open Util;

let inst =
  Instance.create(makeConfig(~baseURL="https://www.reddit.com", ()));

let getUser = (username: string) : Js.Promise.t(Types.user) =>
  Instance.get(inst, {j|/user/$username/about.json|j})
  |> thenResolve(res => res##data##data)
  |> thenResolve(Types.Decode.user);
