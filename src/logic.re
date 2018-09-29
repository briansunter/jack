type suit =
  | Hearts
  | Diamonds
  | Spades
  | Clubs;

type style =
  | Jack
  | Queen
  | King
  | Ace
  | Simple(int);

let styleToString = style =>
  switch (style) {
  | Jack => "Jack"
  | Queen => "Queen"
  | King => "King"
  | Ace => "Ace"
  | Simple(x) => string_of_int(x)
  };

let suitToString = style =>
  switch (style) {
  | Hearts => "Jack"
  | Diamonds => "Queen"
  | Spades => "King"
  | Clubs => "Ace"
  };

type card = {
  suit,
  style,
};

type hand = list(card);

let faceCardValue = 10;

let cardValue = ({style}) =>
  switch (style) {
  | Simple(value) => value
  | _ => faceCardValue
  };

let aceHighValue = 11;
let aceLowValue = 1;
let maxValue = 21;

let addAces = (sumSoFar, aces) =>
  Belt.List.reduce(aces, sumSoFar, (a, _) =>
    if (a + aceHighValue <= maxValue) {
      a + aceHighValue;
    } else {
      a + aceLowValue;
    }
  );

let calculateHand = hand => {
  let aces: hand = List.filter(({style}) => style == Ace, hand);
  let noAceHand: hand = List.filter(({style}) => style != Ace, hand);
  let sumWithoutAces: int = noAceHand |> List.map(cardValue) |. Belt.List.reduce(0, (+));
  addAces(sumWithoutAces, aces);
};

let testHand: hand = [
  {suit: Hearts, style: Jack},
  {suit: Hearts, style: Simple(1)},
];

let rec range = (start: int, end_: int) =>
  if (start >= end_) {
    [];
  } else {
    [start, ...range(start + 1, end_)];
  };

type deck = list(card);

let suits = [Hearts, Clubs, Diamonds, Spades];
let faceCards = [Ace, King, Queen, Jack];
let simpleCards: list(style) = List.map(i => Simple(i), range(2, 10));
let styles: list(style) = List.append(faceCards, simpleCards);

let defaultDeck: deck =
  Belt.List.reduce(suits, [], (a, suit) =>
    List.append(a, Belt.List.map(styles, style => {suit, style}))
  );

type board = {
  playerHand: hand,
  dealerHand: hand,
};

let emptyBoard = {playerHand: [], dealerHand: []};

type gameState =
  | NewGame
  | PlayerTurn
  | Blackjack
  | Push
  | PlayerBust
  | DealerBust
  | DealerTurn
  | PlayerWin
  | DealerBlackjack
  | DealerWin;

let gameStateToString = (state: gameState): string =>
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

type game = {
  board,
  deck,
  gameState,
};

let dealInitialcards = game => {
  let [playerCard1, playerCard2, dealerCard1, dealerCard2, ...restDeck] =
    game.deck;
  let playerHand = [playerCard1, playerCard2];
  let dealerHand = [dealerCard1, dealerCard2];
  let initialGameState =
    if (calculateHand(playerHand) == 21) {
      Blackjack;
    } else {
      PlayerTurn;
    };

  {
    ...game,
    deck: restDeck,
    gameState: initialGameState,
    board: {
      playerHand,
      dealerHand,
    },
  };
};

let dealerHitValue = 17;

let dealerCanPlay = hand => calculateHand(hand) < dealerHitValue;

let runDealerTurn = game: game =>
  Belt.List.reduce(
    game.deck,
    game,
    (g, _) => {
      let [newCard, ...restDeck] = game.deck;
      let newDealerHand = [newCard, ...game.board.dealerHand];
      if (dealerCanPlay(g.board.dealerHand)) {
        if (calculateHand(newDealerHand) <= maxValue) {
          {
            ...g,
            deck: restDeck,
            gameState: DealerTurn,
            board: {
              ...game.board,
              dealerHand: newDealerHand,
            },
          };
        } else {
          {
            ...g,
            deck: restDeck,
            gameState: DealerBust,
            board: {
              ...game.board,
              dealerHand: newDealerHand,
            },
          };
        };
      } else {
        g;
      };
    },
  );

let findWinner = board => {
  let playerTotal = calculateHand(board.playerHand);
  let dealerTotal = calculateHand(board.dealerHand);
  if (playerTotal == dealerTotal) {
    Push
  } else {
    if (playerTotal > maxValue) {
      PlayerBust
    } else {
      if (dealerTotal > maxValue) {
        DealerBust
      } else {
        if (playerTotal > dealerTotal) {
          PlayerWin
        } else {
          DealerWin
        }
      }
    }
  }
};

type actions = Deal
  | Hit
  | Stand
  | Split;

let runPlayerTurn = (game: game, action) =>
  switch (action) {
  | Hit =>
    let [newCard, ...restDeck] = game.deck;
    let newPlayerHand = [newCard, ...game.board.playerHand];
    if (calculateHand(newPlayerHand) <= maxValue) {
      {
        ...game,
        deck: restDeck,
        gameState: PlayerTurn,
        board: {
          ...game.board,
          playerHand: newPlayerHand,
        },
      };
    } else {
      {
        ...game,
        deck: restDeck,
        gameState: PlayerBust,
        board: {
          ...game.board,
          playerHand: newPlayerHand,
        },
      };
    };
  | Stand =>
    let dealerGame = runDealerTurn(game);

    if (dealerGame.gameState == DealerBust) {
      dealerGame;
    } else {
      let winner = findWinner(dealerGame.board);
      {
        ...dealerGame,
       gameState: winner,
      };
    };
  };

  let canHit = (game:game):bool => {
    switch(game.gameState) {
    | PlayerTurn  => true
    | _ => false
    };
  };
  let canStand = (game:game):bool => {
    switch(game.gameState) {
    | PlayerTurn => true
    | _ => false
    };
  };