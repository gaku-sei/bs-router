open Router;
open Segment;
open! Infix;

let hiHandler = () => "Hello, World";

let helloHandler = () => "Hello, Routes";

let sumHandler = (a, b) =>
  "Sum of "
  ++ string_of_int(a)
  ++ " and "
  ++ string_of_int(b)
  ++ " = "
  ++ string_of_int(a + b);

let idHandler = id => "Requested user with id " ++ string_of_int(id);

let adminHandler = a => a ? "User is admin" : "User is not an admin";

let routes =
  make([
    s("hi") /? nil --> hiHandler(),
    s("hello") / s("from") / s("routes") /? nil --> helloHandler(),
    s("sum") / int / int /? nil --> sumHandler,
    s("user") / int /? nil --> idHandler,
    s("user") / bool /? nil --> adminHandler,
    s("confusing") /? nil --> "Foobar",
  ]);

let unwrapResult =
  fun
  | None => "No match"
  | Some(r) => r;

let () = {
  let targets = [
    "sum/12/127",
    "/hi",
    "/hello/from/routes",
    "/user/121",
    "user/false",
    "confusing/",
    "confusing",
  ];

  targets
  |> Belt.List.forEach(_, target =>
       routes |> match'(~target) |> unwrapResult |> Js.log
     );
};
