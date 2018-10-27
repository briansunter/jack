open Utils;

type actions =
  | Move(Logic.actions);

type state = {
  game: Logic.game,
  playerBet: int,
};

let component = ReasonReact.reducerComponent("Blackjack");

let appReducer = (action: actions, state) =>
  switch (action) {
  | Move(a) =>
    ReasonReact.Update({...state, game: Logic.runPlayerTurn(state.game, a)})
  };

let make = _children => {
  ...component,
  initialState: () => {
    let shuffledDeck = Belt.List.shuffle(cycle(100, Logic.defaultDeck));
    {
      game: {
        deck: shuffledDeck,
        board: Logic.emptyBoard,
        gameState: Logic.NewGame,
        playerBet: 200.0,
        playerTotal: 10000.0,
      },
      playerBet: 200,
    };
  },
  reducer: appReducer,
  render: ({state: {game}, send}) => {
    let sendW = a => send(Move(a));
    <div> <Game game send=sendW /> </div>;
  },
};
