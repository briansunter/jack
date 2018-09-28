let component = ReasonReact.statelessComponent("ToolBar");

module Styles = {
  open Css;

  let toolBar = style([display(flexBox), flexDirection(column)]);

  let toolBarRow =
    style([
      display(flexBox),
      flexDirection(row),
      justifyContent(center),
      backgroundColor(darkolivegreen),
      minHeight(pt(50)),
      margin(px(10)),
    ]);

  let toolBarItem =
    style([
      display(`flex),
      flexDirection(`column),
      alignItems(`center),
      justifyContent(`center),
      flexGrow(1),
      width(pct(100.0)),
      minHeight(pt(50)),
      backgroundColor(white),
      textAlign(center),
      alignItems(center),
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

let gameStateToString = (state: Logic.gameState): string =>
  switch (state) {
  | NewGame => "New Game"
  | PlayerTurn => "Player Turn"
  | Blackjack => "Blackjack"
  | Push => "Push"
  | PlayerBust => "Player Bust"
  | DealerBust => "Dealer Bust"
  | DealerTurn => "Dealer Turn"
  | PlayerWin => "Player Win"
  | DealerBlackjack => "Dealer Blackjack"
  | DealerWin => "Dealer Win"
  };

let make = (~send: Logic.actions => unit, ~game: Logic.game, _children) => {
  ...component,
  render: _self =>
    <div className=Styles.toolBarRow>
      /* <Hand hand=dealerHand />
         <Hand hand=playerHand /> */

        <div className=Styles.toolBarItem>
          <h3> {ReasonReact.string(gameStateToString(game.gameState))} </h3>
          <h3>
            {
              ReasonReact.string(
                string_of_int(Logic.calculateHand(game.board.playerHand)),
              )
            }
          </h3>
        </div>
        <div className=Styles.toolBarItem>
          <button
            className=Styles.toolBarItem onClick={_ => send(Logic.Deal)}>
            <h3> {ReasonReact.string("Deal Cards")} </h3>
          </button>
        </div>
        <div className=Styles.toolBarItem>
          <button
            className=Styles.toolBarItem
            onClick={_ => send(Logic.Hit)}
            disabled={!Logic.canHit(game)}>
            <h3> {ReasonReact.string("Hit Me")} </h3>
          </button>
        </div>
        <div className=Styles.toolBarItem>
          <button
            className=Styles.toolBarItem
            onClick={_ => send(Logic.Stand)}
            disabled={!Logic.canStand(game)}>
            <h3> {ReasonReact.string("Stand")} </h3>
          </button>
        </div>
      </div>,
};
