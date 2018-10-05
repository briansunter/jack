type actions =
  | Move(Logic.actions);

type state = {game: Logic.game};

let component = ReasonReact.reducerComponent("Blackjack");

let appReducer = (action: actions, state) =>
  switch (action) {
  | Move(a) => ReasonReact.Update({game: Logic.runPlayerTurn(state.game, a)})
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
  render: ({state: {game}, send}) => {
    let sendW = a => send(Move(a));
    <div> <Game game send=sendW /> </div>;
  },
};
