let component = ReasonReact.statelessComponent("Card");

module Styles = {
  open Css;
  let card = [
    backgroundColor(white),
    display(flexBox),
    flexDirection(column),
    justifyContent(spaceBetween),
    boxShadow(~y=px(4), ~blur=px(6), rgba(0, 0, 0, 0.3)),
    borderStyle(solid),
    borderRadius(px(5)),
    borderWidth(px(3)),
    padding(px(10)),
    minWidth(px(75)),
    backfaceVisibility(`hidden),
  ];

  let cardFlipped =
    style(
      List.concat([
        card,
        [
          transition(~duration=1500, "transform"),
          transformStyle(`preserve3d),
          transform(rotateY(deg(0))),
        ],
      ]),
    );

  let cardUnFlipped =
    style(
      List.concat([
        card,
        [
          transition(~duration=1500, "transform"),
          transformStyle(`preserve3d),
          transform(rotateY(deg(180))),
        ],
      ]),
    );

  let topStyle = style([display(flexBox)]);

  let middleStyle =
    style([display(flexBox), justifyContent(center), fontSize(px(100))]);

  let bottomStyle = style([display(flexBox), justifyContent(flexEnd)]);

  let actionButton = disabled =>
    style([
      background(disabled ? darkgray : white),
      color(black),
      border(px(1), solid, black),
      borderRadius(px(3)),
    ]);
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

let component = ReasonReact.statelessComponent("Card");
let make = (~suit, ~cardStyle, ~flipped=true, ~showFace=true, _children) => {
  ...component,
  render: _self =>
    <div
      className={if (flipped) {Styles.cardFlipped} else {Styles.cardUnFlipped}}>
      <div className=Styles.topStyle>
        <div> {ReasonReact.string(styleToString(cardStyle))} </div>
        <div> {ReasonReact.string(suitToSymbol(suit))} </div>
      </div>
      <div className=Styles.middleStyle>
        {ReasonReact.string(suitToSymbol(suit))}
      </div>
      <div className=Styles.bottomStyle>
        <div> {ReasonReact.string(styleToString(cardStyle))} </div>
        <div> {ReasonReact.string(suitToSymbol(suit))} </div>
      </div>
    </div>,
};
