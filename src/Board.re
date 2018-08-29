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

let make = (~playerHand, ~dealerHand, _children) => {
  ...component,
  render: _self =>
    <div className=Styles.board>
    <Hand hand=dealerHand />
    <Hand hand=playerHand />
    </div>
};