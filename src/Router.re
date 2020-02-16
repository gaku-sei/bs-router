type t('b) = PatternTrie.t(Path.t('b));

let rec pathPattern: type a b. Segment.t(a, b) => list(PatternTrie.Key.t) =
  fun
  | Segment.End(_) => []
  | Segment.Match(w, fmt) => [
      PatternTrie.Key.Match(w),
      ...pathPattern(fmt),
    ]
  | Segment.Conv(_, fmt) => [PatternTrie.Key.Capture, ...pathPattern(fmt)];

let parseRoute = (fmt, handler, params) => {
  let rec matchTarget:
    type a b. (Segment.t(a, b), a, list(string)) => option(b) =
    (t, f, s) =>
      switch (t, s) {
      | (Segment.End({trailingSlash}), [""]) when trailingSlash == true =>
        Some(f)
      | (Segment.End({trailingSlash}), []) when trailingSlash == false =>
        Some(f)
      | (Segment.End(_), _) => None
      | (Segment.Match(x, fmt), [x', ...xs]) when x == x' =>
        matchTarget(fmt, f, xs)
      | (Segment.Match(_, _), _) => None
      | (Segment.Conv(_, _), []) => None
      | (Segment.Conv({from, _}, fmt), [x, ...xs]) =>
        from(x) |> Belt.Option.flatMap(_, x' => matchTarget(fmt, f(x'), xs))
      };

  params |> matchTarget(fmt, handler);
};

let runRoutes = (target, router) => {
  let rec aux =
    fun
    | [] => None
    | [Path.Path(r, h), ...rs] =>
      switch (parseRoute(r, h, target)) {
      | None => aux(rs)
      | Some(_) as some => some
      };

  target |> PatternTrie.feedParams(router) |> aux;
};

let make = routes => {
  let routes = Belt.List.reverse(routes);

  routes
  |> Belt.List.reduce(
       _, PatternTrie.empty, (routes, Path.Path(r, _) as route) =>
       routes |> PatternTrie.add(pathPattern(r), route)
     );
};

let match' = (~target) => target |> Util.splitPath |> runRoutes;
