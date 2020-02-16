open Router;
open! Infix;
open Segment;

type req = {target: string};

let idx = (_: req) => "Root";

let getUser = (id: int, req: req) =>
  "Received request from "
  ++ req.target
  ++ " to fetch id: "
  ++ string_of_int(id);

let searchUser = (_name: string, _city: string, _req: req) => "Search for user";

let router =
  Router.make([
    nil --> idx,
    s("user") / int /? nil --> getUser,
    s("user") / str / str /? trail --> searchUser,
  ]);

let req = {target: "/user/12"};

// Returns "No match"
switch (router |> match'(~target="/some/url")) {
| None => "No match"
| Some(r) => r(req)
};

// Returns "Received request from /user/12 to fetch id: 12"
switch (router |> match'(~target=req.target)) {
| None => "No match"
| Some(r) => r(req)
};

// Returns "Search for user"
switch (router |> match'(~target="/user/hello/world/")) {
| None => "No match"
| Some(r) => r(req)
};

// Returns "No match because of missing trailing slash"
switch (router |> match'(~target="/user/hello/world")) {
| None => "No match because of missing trailing slash"
| Some(r) => r(req)
};

// let myFancyRoute = () => s("user") / int / s("add") /? nil;

// let stringifyRoute = Path.stringify(myFancyRoute());

// // Returns "/user/12/add"
// stringifyRoute(12);
