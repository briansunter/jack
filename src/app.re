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

let rec range = (~start: int=0, end_: int) =>
  if (start >= end_) {
    [];
  } else {
    [start, ...range(~start=start + 1, end_)];
  };

let repeat = (times, l) =>
  Belt.Array.map(ArrayLabels.of_list(range(times)), _ => l);

let cycle = (times, l) => Belt.List.concatMany(repeat(times, l));

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
