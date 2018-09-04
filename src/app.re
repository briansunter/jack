type action =
  | Deal
  | HitMe
  | Stand;

type state = {game: Logic.game};

let component = ReasonReact.reducerComponent("MyCounter");

let appReducer = (action, state) =>
  switch (action) {
  | Deal =>
    ReasonReact.Update({...state, game: Logic.dealInitialcards(state.game)})
  | HitMe =>
    ReasonReact.Update({
      ...state,
      game: Logic.runPlayerTurn(state.game, Logic.Hit),
    })
  | Stand =>
    ReasonReact.Update({
      ...state,
      game: Logic.runPlayerTurn(state.game, Logic.Stand),
    })
  };
  let gameStateToString = (state:Logic.gameState):string => 
  switch(state) {
  | NewGame => "New Game"
  | PlayerTurn => "Player Turn"
  | Blackjack => "Blackjack"
  | Push => "Push"
  | PlayerBust => "Player Bust"
  | DealerBust => "Dealer Bust"
  | DealerTurn => "Dealer Turn"
  | PlayerWin => "Player Win"
  | DealerBlackjack => "Dealer Blackjack"
  | DealerWin => "Dealer Win";
  };

let make = _children => {
  ...component,
  initialState: () => {
    let shuffledDeck = Belt.List.shuffle(Logic.defaultDeck);
    {
      game: {
        deck: shuffledDeck,
        board: Logic.emptyBoard,
        gameState: Logic.NewGame,
      },
    };
  },
  reducer: appReducer,
  render: ({state: {game}, send}) =>
    <div>
      <Board
        playerHand={Belt.List.toArray(game.board.playerHand)}
        dealerHand={Belt.List.toArray(game.board.dealerHand)}
      />
      <div> 
          {ReasonReact.string(gameStateToString(game.gameState))}
     </div>
      <div>
        <button onClick={_ => send(Deal)}>
          {ReasonReact.string("Deal Cards")}
        </button>
      </div>
      <div>
        <button onClick={_ => send(HitMe)} disabled={! Logic.canHit(game.gameState)}>
          {ReasonReact.string("Hit Me")}
        </button>
      </div>
      <div>
        <button onClick={_ => send(Stand)} disabled={! Logic.canStand(game.gameState)}>
          {ReasonReact.string("Stand")}
        </button>
      </div>
    </div>,
};
