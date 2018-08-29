type action =
  | Tick
  | Click;

type game = {
  /* board: Logic.board, */
  deck: Logic.deck,
  /* playerBet: int,  */
};

type state = {
  time: int,
  timerId: ref(option(Js.Global.intervalId)),
  count: int,
  game: game,
};

let res =
  Js.Promise.(
    Fetch.fetch("https://www.google.com")
    |> then_(Fetch.Response.text)
    |> then_(text => Js.log(text) |> resolve)
  );

[@bs.val] external alert : string => unit = "alert";

let component = ReasonReact.reducerComponent("MyCounter");

let make = _children => {
  ...component,
  initialState: () => {time: 0, timerId: ref(None), count: 0, game: {deck: Logic.defaultDeck}},
  reducer: (action, state) =>
    switch (action) {
    | Tick => ReasonReact.Update({...state, time: state.time + 1})
    | Click =>
      let oldCount = state.count;
      let newCount = oldCount + 1;
      ReasonReact.UpdateWithSideEffects(
        {...state, count: newCount},
        (({state: {count}}) => alert({j|Updating counter to $count|j})),
      );
    },
  didMount: self =>
    self.state.timerId :=
      Some(Js.Global.setInterval(() => self.send(Tick), 1000)),
  render: ({send, state: {time, count, game}}) => {
    <div>
      <Board playerHand=Belt.List.toArray(game.deck) 
      dealerHand=Belt.List.toArray(Logic.testHand)/>
    </div>;
  },
};