let (-->) = Path.make;

let (/) = (m1, m2, r) => m1(m2(r));

let (/?) = (m1, m2) => m1(m2);
