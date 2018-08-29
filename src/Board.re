let component = ReasonReact.statelessComponent("Board");

module Styles = {
  open Css;

  let board = style([
    display(flexBox),
    flexDirection(column),
    justifyContent(center),
    backgroundColor(darkolivegreen),
    margin(px(10))
 ]);

  let topStyle = style([
    display(flexBox),
  ]);

  let middleStyle = style([
    display(flexBox),
    justifyContent(center),
    fontSize(px(100))
  ]);

  let bottomStyle= style([
    display(flexBox),
    justifyContent(flexEnd),
  ]);

  let actionButton = disabled =>
    style([
      background(disabled ? darkgray : white),
      color(black),
      border(px(1), solid, black),
      borderRadius(px(3)),
    ])
};

let styleToString = style =>
  switch (style) {
  | Logic.Jack => "Jack"
  | Logic.Simple(x) => string_of_int(x)
  | _ => "Other"
  };

  let suitToSymbol = suit =>
  switch (suit) {
  | Logic.Hearts => {js|\u2665|js}
  | Logic.Clubs =>  {js|\u2663|js}
  | Logic.Spades => {js|\u2660|js}
  | Logic.Diamonds => {js|\u2666|js} 
  };

let make = (~playerHand, ~dealerHand, _children) => {
  ...component,
  render: _self =>
    <div className=Styles.board>
    <Hand hand=dealerHand />
    <Hand hand=playerHand />
    </div>
};