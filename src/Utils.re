let rec range = (~start: int=0, end_: int) =>
  if (start >= end_) {
    [];
  } else {
    [start, ...range(~start=start + 1, end_)];
  };

let repeat = (times, l) =>
  Belt.Array.map(ArrayLabels.of_list(range(times)), _ => l);

let cycle = (times, l) => Belt.List.concatMany(repeat(times, l));
