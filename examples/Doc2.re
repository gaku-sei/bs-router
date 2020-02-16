open Router;
open! Infix;
open Segment;

type shape =
  | Circle
  | Square;

let shapeOfString =
  fun
  | "circle" => Some(Circle)
  | "square" => Some(Square)
  | _ => None;

let shapeToString =
  fun
  | Circle => "circle"
  | Square => "square";

let shape = pattern(~label=":shape", ~from=shapeOfString, ~to_=shapeToString);

let process_shape = (s: shape) => shapeToString(s);

let route = () => s("shape") / shape / s("create") /? nil;

let router = make([route() --> process_shape]);

// Return Some("circle")
router |> match'(~target="/shape/circle/create");

// Return Some("square")
router |> match'(~target="/shape/square/create");

// Return None
router |> match'(~target="/shape/triangle/create");

// // Return "/shape/:shape/create"
// Path.stringify(router);
