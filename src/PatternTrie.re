module Key = {
  type t =
    | Match(string): t
    | Capture: t;
};

type t('a) = {
  capture: option(t('a)),
  children: Belt.Map.String.t(t('a)),
  parsers: list('a),
};

let empty = {capture: None, children: Belt.Map.String.empty, parsers: []};

let feedParams = (t, params) => {
  let rec aux = (t, params) =>
    switch (t, params) {
    | ({parsers: [], _}, []) => []
    | ({parsers: rs, _}, []) => rs
    | ({parsers: rs, _}, [""]) => rs
    | ({children, capture, _}, [x, ...xs]) =>
      switch (children |> Belt.Map.String.get(_, x)) {
      | None =>
        switch (capture) {
        | None => []
        | Some(t') => aux(t', xs)
        }
      | Some(m') => aux(m', xs)
      }
    };

  aux(t, params);
};

let add = (k, v, t) => {
  let rec aux = (k, t) =>
    switch (k, t) {
    | ([], {parsers: x, _} as n) => {...n, parsers: [v, ...x]}
    | ([x, ...r], {children, capture, _} as n) =>
      switch (x) {
      | Key.Match(w) =>
        let t' =
          switch (children |> Belt.Map.String.get(_, w)) {
          | None => empty
          | Some(v) => v
          };

        let t'' = aux(r, t');

        {...n, children: children |> Belt.Map.String.set(_, w, t'')};
      | Key.Capture =>
        let t' =
          switch (capture) {
          | None => empty
          | Some(v) => v
          };

        let t'' = aux(r, t');

        {...n, capture: Some(t'')};
      }
    };

  aux(k, t);
};
