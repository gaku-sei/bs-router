/** [r --> h] is used to connect a route pattern [r] to a function [h] that gets called
    if this pattern is successfully matched.*/
let (-->): (Segment.t('a, 'b), 'a) => Path.t('b);

/** [l / r] joins two segment match patterns [l] and [r] into a pattern sequence, parse l followed by parse r.
    Example: If we want to define a route that matches a string followd by
    a constant "foo" and then an integer, we'd use the [/] operator like below:
    {[
      let route = () => Router.(str / s("foo") / int /? nil);
    ]} */
let (/): (Segment.t('a, 'b) => 'c, 'd => Segment.t('a, 'b), 'd) => 'c;

/** [l /? r] is used to express the sequence of, parse l followed by parse r and then stop parsing.
    This is used at the end of the route pattern to define how a route should end. The right hand parameter
    [r] should be a pattern definition that cannot be used in further chains joined by [/] (One such operator is [nil]). */
let (/?): (Segment.t('a, 'b) => 'c, Segment.t('a, 'b)) => 'c;
