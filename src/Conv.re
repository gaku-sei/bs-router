type t('a) = {
  from: string => option('a),
  label: string,
  to_: 'a => string,
};

let make = (~label, ~from, ~to_) => {from, label, to_};
