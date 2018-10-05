let component = ReasonReact.statelessComponent("Board");

module Styles = {
  open Css;

  let board =
    style([
      display(flexBox),
      flexDirection(column),
      justifyContent(center),
      backgroundColor(darkolivegreen),
      minHeight(px(500)),
    ]);

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

let shouldHideDealerCard = gameState =>
  switch (gameState) {
  | Logic.PlayerTurn => true
  | _ => false
  };

let make = (~playerHand, ~dealerHand, ~gameState, _children) => {
  ...component,
  render: _self =>
    <div className=Styles.board>
      <Hand
        hand=dealerHand
        hideSecondCard={shouldHideDealerCard(gameState)}
      />
      <Hand hand=playerHand />
    </div>,
};
