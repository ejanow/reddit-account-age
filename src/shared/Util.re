[@bs.val] external requireCss : string => unit = "require";

type void = unit => unit;

let thenResolve = (fn, p) =>
  Js.Promise.then_(value => Js.Promise.resolve(fn(value)), p);

let thenIgnore = (fn, p) => thenResolve(fn, p) |> ignore;

let catchResolve = (fn, p) =>
  Js.Promise.catch(value => Js.Promise.resolve(fn(value)), p);

let catchIgnore = (fn, p) => catchResolve(fn, p) |> ignore;

let singletonList: 'a => list('a) = item => [item];

let throttle = (callback: unit => 'a, delay: int) : void => {
  let timeout: ref(option(Js.Global.timeoutId)) = ref(None);
  let later = () => {
    let _ = callback();
    timeout := None;
  };
  () =>
    if (Js.Option.isNone(timeout^)) {
      timeout := Some(Js.Global.setTimeout(later, delay));
    };
};
