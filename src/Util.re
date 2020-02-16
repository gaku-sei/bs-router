let splitPath = target => {
  let splitTarget = target =>
    switch (target) {
    | ""
    | "/" => []
    | _ =>
      switch (target |> Js.String.split("/") |> Belt.List.fromArray) {
      | ["", ...xs] => xs
      | xs => xs
      }
    };

  switch (Js.String.indexOf(target, "?")) {
  | i when i < 0 => splitTarget(target)
  | 0 => []
  | i => target |> Js.String.substring(~from=0, ~to_=i) |> splitTarget
  };
};
