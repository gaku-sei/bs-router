/** [t] is a combination of a segment sequence, with a function that will be
    called on a successful match. When a segment sequence matches, the patterns
    that are extracted are forwarded to said function with the types that the user
    defined.

    Example:

    {[
      let path = () => Router.(s("foo") / str / int /? nil -->
        ((a: string, b: int) =>
            Js.log2(a, b)));
    ]}
  */
type t('b) =
  | Path(Segment.t('a, 'b), 'a): t('b);

/** [make] creates a path from a segment and a handler. */
let make: (Segment.t('b, 'a), 'b) => t('a);

/** [stringify] is similar to [Segment.stringify], except it takes a path (combination of segment sequence
    and a handler) as input, instead of just a segment sequence. */
let stringify: t('a) => string;
