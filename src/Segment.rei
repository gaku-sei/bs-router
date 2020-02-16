/** [t] represents a sequence of path parameter patterns that are expected in a route. */
type t('a, 'b) =
  | End({trailingSlash: bool}): t('a, 'a)
  | Match(string, t('a, 'b)): t('a, 'b)
  | Conv(Conv.t('c), t('a, 'b)): t('c => 'a, 'b);

/** [int] matches a path segment if it can be successfully coerced into an integer. */
let int: t('a, 'b) => t(int => 'a, 'b);

// /** [int32] matches a path segment if it can be successfully coerced into a 32 bit integer. */
// let int32 : t('a, 'b) => path(int32 => 'a, 'b);

// /** [int64] matches a path segment if it can be successfully coerced into a 64 bit integer. */
// let int64 : t('a, 'b) => path(int64 => 'a, 'b);

let str: t('a, 'b) => t(string => 'a, 'b);
/** [str] matches any path segment and forwards it as a string. */

let bool: t('a, 'b) => t(bool => 'a, 'b);
/** [bool] matches a path segment if it can be successfully coerced into a boolean. */

/** [s word] matches a path segment if it exactly matches [word]. The matched path param is then discarded. */
let s: (string, t('a, 'b)) => t('a, 'b);

/** [nil] is used at the end of a path pattern sequence to indicate that a route
    should only match if it ends without a trailing slash. */
let nil: t('a, 'a);

/** [trail] is used at the end of a path pattern sequence to indicate that a route
    should only match if it ends with a trailing slash. */
let trail: t('a, 'a);

/** [pattern] accepts two functions, one for converting a user provided type to
    a string representation, and another to potentially convert a string to the said type.
    With these two functions, it creates a pattern that can be used for matching a path segment.
    This is useful when there is a need for types that aren't provided out of the box
    by the library.

    Example:

    {[
      type shape =
        | Square
        | Circle;

      let shapeOfString = fun
        | "square" => Some(Square)
        | "circle" => Some(Circle)
        | _ => None;

      let shapeToString = fun
        | Square => "square"
        | Circle => "circle";

      let shape = Routes.pattern(~label=":shape", from=shapeOfString, to_=shapeToString);

      /* Now the shape pattern can be used just like any
         of the built in patterns like int, bool etc */
      let route = () => s("shape") / shape / s("create") /? nil;
    ]}
  */
let pattern:
  (
    ~label: string,
    ~from: string => option('c),
    ~to_: 'c => string,
    t('a, 'b)
  ) =>
  t('c => 'a, 'b);

/** [stringify] can be used to pretty-print a path sequence. This can be useful
    to get a human readable output that indicates the kind of pattern
    that a route will match. When creating a custom pattern matcher
    using [pattern], a string label needs to be provided. This label
    is used by [stringify] when preparing the pretty-print output.

    Example:
    {[
      let r = () => Segment.(s("foo") / int / s("add") / bool /? nil);

      Segment.stringify(r);
      -: "foo/:int/add/:bool"
    ]}
  */
let stringify: t('a, 'b) => string;
