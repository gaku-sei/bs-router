## BsRouter

This library will help with adding typed routes to BuckleScript applications.
The goal is to have a easy to use portable library with
reasonable performance.

Users can create a list of routes, and handler function to work
on the extracted entities using the combinators provided by
the library. To perform URL matching one would just need to forward
the URL's path and query to the matcher.

#### Example

```reason
open Router;
open! Infix;
open Segment;

type req = { target: string };

let idx = (_: req) => "Root";

let getUser = (id: int, req: req) =>
  "Received request from " ++ req.target ++ " to fetch id: " ++ string_of_int(id);

let searchUser = (_name: string, _city: string, _req : req) => "Search for user";

let router = Router.make(
  [
    nil --> idx,
    (s("user") / int /? nil) --> getUser,
    (s("user") / str / str /? trail) --> searchUser
  ]
);

let req = { target: "/user/12" };

// Returns "No match"
switch (router |> match'(~target="/some/url")) {
  | None => "No match"
  | Some(r) => r(req);
};

// Returns "Received request from /user/12 to fetch id: 12"
switch (router |> match'(~target=req.target)) {
  | None => "No match"
  | Some(r) => r(req);
};

// Returns "Search for user"
switch (router |> match'(~target="/user/hello/world/")) {
  | None => "No match"
  | Some(r) => r(req);
};

// Returns "No match because of missing trailing slash"
switch (router |> match'(~target="/user/hello/world")) {
  | None => "No match because of missing trailing slash"
  | Some(r) => r(req);
};

// let myFancyRoute = () => s("user") / int / s("add") /? nil;

// let stringifyRoute = Path.stringify(myFancyRoute);

// // Returns "/user/12/add"
// stringifyRoute(12);
```

It is possible to define custom patterns that can be used for matching.

```reason
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
```

## Installation

```sh
npm install bs-router
```

or

```sh
yarn add bs-router
```

## Related Work

This project is a fork of the great [Routes' project](https://github.com/anuragsoni/routes).

The combinators are influenced by Rudi Grinberg's wonderful [blogpost](http://rgrinberg.com/posts/primitive-type-safe-routing/) about
type safe routing done via an EDSL using GADTs + an interpreted for the DSL.

Also thanks to Gabriel Radanne for feedback and for the [blog](https://drup.github.io/2016/08/02/difflists/) post showing the technique used in printf like functions.
