
type state = {game: Logic.game};

let component = ReasonReact.reducerComponent("MyCounter");

let appReducer = (action:Logic.actions, state) =>
  switch (action) {
  | Logic.Deal =>
    ReasonReact.Update({...state, game: Logic.dealInitialcards(state.game)})
  | Logic.Hit =>
    ReasonReact.Update({
      ...state,
      game: Logic.runPlayerTurn(state.game, Logic.Hit),
    })
  | Logic.Stand =>
    ReasonReact.Update({
      ...state,
      game: Logic.runPlayerTurn(state.game, Logic.Stand),
    })
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
    <Game game=game send=send />
    </div>,
};
