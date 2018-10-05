let component = ReasonReact.statelessComponent("Game");

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

let make = (~game: Logic.game, ~send: Logic.actions => unit, _children) => {
  ...component,
  render: _self =>
    <div className=Styles.board>
      <Board
        playerHand={
          Belt.Array.reverse(Belt.List.toArray(game.board.playerHand))
        }
        dealerHand={
          Belt.Array.reverse(Belt.List.toArray(game.board.dealerHand))
        }
        gameState={game.gameState}
      />
      <ToolBar send game />
    </div>,
};
