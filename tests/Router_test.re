open Jest;
open Expect;
open! Operators;

open Router;
open! Infix;

describe("Router", () => {
  describe("Empty router has no match", () => {
    let router = make([]);

    test("Empty router has no match", () =>
      expect(router |> match'(~target="/foo/bar")) == None
    );

    test("Empty router has no match for empty target", () =>
      expect(router |> match'(~target="")) == None
    );
  });

  describe("Can extract path parameters", () => {
    let router =
      make(
        Segment.[
          s("foo") / str /? nil --> (x => x),
          s("numbers")
          / int
          / int
          / int
          /? nil
          --> ((a, b, c) => {j|$a-$b-$c|j}),
        ],
      );

    test("Can extract a string and an integer", () =>
      expect(router |> match'(~target="foo/Movie")) == Some("Movie")
    );

    test("Can extract multiple path parameters", () =>
      expect(router |> match'(~target="/numbers/1/2/3")) == Some("1-2-3")
    );
  });

  describe("Segment", () => {
    testAll(
      "Can stringify properly",
      Segment.[
        (s("") /? nil, "/"),
        (s("foo") /? trail, "/foo/"),
        (s("foo") / s("bar") /? nil, "/foo/bar"),
      ],
      ((segment, expected)) =>
      expect(Segment.stringify(segment)) == expected
    );

    testAll(
      "Can stringify properly complex segments",
      Segment.[
        (s("foo") / str / bool /? nil, "/foo/:string/:bool"),
        (s("foo") / str / bool /? trail, "/foo/:string/:bool/"),
      ],
      ((segment, expected)) =>
      expect(Segment.stringify(segment)) == expected
    );
  });

  describe("Path", () =>
    testAll(
      "Can stringify properly",
      Segment.[
        (s("") /? nil, "/"),
        (s("foo") /? trail, "/foo/"),
        (s("foo") / s("bar") /? nil, "/foo/bar"),
      ],
      ((segment, expected)) =>
      expect(Path.stringify(segment --> (x => x))) == expected
    )
  );
});
