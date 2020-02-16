type t('a, 'b) =
  | End({trailingSlash: bool}): t('a, 'a)
  | Match(string, t('a, 'b)): t('a, 'b)
  | Conv(Conv.t('c), t('a, 'b)): t('c => 'a, 'b);

let pattern = (~label, ~from, ~to_, r) =>
  Conv(Conv.make(~label, ~from, ~to_), r);

let s = (w, r) => Match(w, r);

let ofConv = (conv, r) => Conv(conv, r);

let int = r =>
  ofConv(
    Conv.make(~label=":int", ~from=int_of_string_opt, ~to_=string_of_int),
    r,
  );

// let int64 = r =>
//   ofConv(
//     Conv.make(
//       ~label=":int64",
//       ~from=Int64.of_string_opt,
//       ~to_=Int64.to_string,
//     ),
//     r,
//   );

// let int32 = r =>
//   ofConv(
//     Conv.make(
//       ~label=":int32",
//       ~from=Int32.of_string_opt,
//       ~to_=Int32.to_string,
//     ),
//     r,
//   );

let str = r =>
  ofConv(Conv.make(~label=":string", ~from=x => Some(x), ~to_=x => x), r);

let bool = r =>
  ofConv(
    Conv.make(~label=":bool", ~from=bool_of_string_opt, ~to_=string_of_bool),
    r,
  );

let nil = End({trailingSlash: false});

let trail = End({trailingSlash: true});

let rec stringify': type a b. t(a, b) => list(string) =
  fun
  | End({trailingSlash}) when trailingSlash => [""]
  | End(_) => []
  | Match(w, fmt) => [w, ...stringify'(fmt)]
  | Conv({label, _}, fmt) => [label, ...stringify'(fmt)];

let stringify = r =>
  stringify'(r) |> Belt.List.reduce(_, "", (acc, x) => acc ++ "/" ++ x);
