type action =
  | Deal
  | HitMe;


type state = {
  game: Logic.game
};

let component = ReasonReact.reducerComponent("MyCounter");

let appReducer = (action, state) => {
  switch(action) {
    | Deal => ReasonReact.Update({...state,game:Logic.dealInitialcards(state.game)})
    | HitMe => ReasonReact.Update({...state,game:Logic.runPlayerTurn(state.game,Logic.Hit)})
  }
};

let make = _children => {
  ...component,
  initialState: () => {
    let shuffledDeck = Belt.List.shuffle(Logic.defaultDeck);
    {game: 
    {deck: shuffledDeck, board: Logic.emptyBoard, gameState:Logic.NewGame}}},
  reducer: appReducer,
  render: ({state: {game},send}) => {
    <div>
      <Board playerHand=(Belt.List.toArray(game.board.playerHand))
      dealerHand=(Belt.List.toArray(game.board.dealerHand))/>
      <div>
      <button onClick=(_ => send(Deal))>
      (ReasonReact.string("Deal Cards"))
    </button> 
      </div>
      <div>
      <button onClick=(_ => send(HitMe))>
      (ReasonReact.string("Hit Me"))
    </button> 
      </div>
    </div>;
  },
};