
let component = ReasonReact.statelessComponent("Card");

module Styles = {
  open Css;

  let card = style([
    display(flexBox),
    flexDirection(column), 
    justifyContent(spaceBetween),
    backgroundColor(white),
    boxShadow(~y=px(4), ~blur=px(6), rgba(0, 0, 0, 0.3)),
    borderStyle(solid),
    borderRadius(px(5)),
    borderWidth(px(3)),
    padding(px(10)),
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
  | Logic.Queen => "Queen"
  | Logic.King => "King"
  | Logic.Ace => "Ace"
  | Logic.Simple(x) => string_of_int(x)
  };

let suitToSymbol = suit =>
  switch (suit) {
  | Logic.Hearts => {js|\u2665|js}
  | Logic.Clubs => {js|\u2663|js}
  | Logic.Spades => {js|\u2660|js}
  | Logic.Diamonds => {js|\u2666|js} 
  };
let make = (~suit, ~cardStyle, _children) => {
  ...component,
  render: _self =>
    <div className=Styles.card>
      <div className=Styles.topStyle>
        <div> {ReasonReact.string(styleToString(cardStyle))} </div>
        <div>{ReasonReact.string(suitToSymbol(suit))} </div>
      </div>
      <div className=Styles.middleStyle>
       {ReasonReact.string(suitToSymbol(suit))}
      </div>
      <div className=Styles.bottomStyle>
        <div>{ReasonReact.string(styleToString(cardStyle))}</div>
        <div>{ReasonReact.string(suitToSymbol(suit))}</div>
      </div>
    </div>,
};