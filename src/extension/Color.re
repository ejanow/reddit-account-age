open Css;

/*
 * http://gka.github.io/palettes/#colors=f11712,0099f7|steps=20|bez=1|coL=1
 */
let colorList = [
  "f11712",
  "ee2921",
  "ea352e",
  "e6403a",
  "e14948",
  "dc5154",
  "d9565c",
  "d25e6a",
  "cc6476",
  "c76980",
  "c06e8a",
  "b87496",
  "b078a1",
  "a67dad",
  "9d82b7",
  "8c87c6",
  "7e8bd1",
  "6291e1",
  "4d95ea",
  "0099f7",
];

let colorListSize = List.length(colorList) - 1;

let daysPerGradient = 60;

let getGradientIndex = ((years, days)) =>
  (years * 365 + days) / daysPerGradient;

let getColor = age =>
  age
  |> getGradientIndex
  |> Js.Math.min_int(colorListSize)
  |> List.nth(colorList)
  |> hex
  |> backgroundColor
  |> Util.singletonList
  |> style;
