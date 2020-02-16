/** Typed routing for BuckleScript.
    [Router] provides combinators for adding typed routing
    to OCaml/ReasonML applications. The core library will be independent
    of any particular web framework or runtime.
*/

/** [t] is a collection of multiple routes. It transforms a list of routes
    into a trie like structure, that is then used for matching an input target url.
    It works for routes that are grouped by an HTTP verb and for standalone routes
    that have no HTTP verb attached to it. */
type t('b);

/** [make] accepts a list of tuples comprised of an optional HTTP verb and a route definition
    of type [path('b)] where 'b is the type that a successful route match will return.

    It transforms the input list of routes into a trie like structure that can later be used
    to perform route matches. */
let make: list(Path.t('b)) => t('b);

/** [match'] accepts an optional HTTP verb, a router and the target url to match.
    if the HTTP verb is provided, it tries to look for a matching route that was defined
    with the specific HTTP verb provided as input. Otherwise it looks for a route
    that is not associated to any HTTP verb.
*/
let match': (~target: string, t('a)) => option('a);
