open Axios;

open Util;

let inst = Instance.create(makeConfig(~baseURL=Constants.apiUrl, ()));

let getStatus = () : Js.Promise.t(Types.getStatusResponse) =>
  Instance.get(inst, "/status") |> thenResolve(res => res##data);

let getUsers =
    (usernames: list(string))
    : Js.Promise.t(Types.getUsersResponse) =>
  Types.{usernames: usernames}
  |> Obj.magic
  |> Instance.postData(inst, "/users")
  |> thenResolve(res => res##data);

let deleteErrors = () : Js.Promise.t(Types.deleteErrorsResponse) =>
  Instance.delete(inst, "/errors") |> thenResolve(res => res##data);
