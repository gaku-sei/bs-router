type t('b) =
  | Path(Segment.t('a, 'b), 'a): t('b);

let make = (r, handler) => Path(r, handler);

let stringify = (Path(p, _)) => Segment.stringify(p);
