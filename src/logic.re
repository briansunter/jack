/* Caesars Palace	7	0.26	6	1.3	100	10000	s17,ds,ls,rsa */
open Utils;

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

type deck = list(card);

let suits = [Hearts, Clubs, Diamonds, Spades];
let faceCards = [Ace, King, Queen, Jack];
let simpleCards: list(style) =
  List.map(i => Simple(i), range(~start=2, 10));
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
  playerBet: float,
  playerTotal: float,
};

let calculatePayout = (game: game): float =>
  switch (game.gameState) {
  | Push => game.playerBet
  | Blackjack => game.playerBet *. 3.0 /. 2.0
  | PlayerWin
  | DealerBust => game.playerBet *. 2.0
  | _ => 0.0
  };

let dealInitialCards = game => {
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

  let dealtGameState = {
    ...game,
    deck: restDeck,
    gameState: initialGameState,
    board: {
      playerHand,
      dealerHand,
    },
  };
  {
    ...dealtGameState,
    playerTotal:
      dealtGameState.playerTotal
      +. calculatePayout(dealtGameState)
      -. dealtGameState.playerBet,
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
    Push;
  } else if (playerTotal > maxValue) {
    PlayerBust;
  } else if (dealerTotal > maxValue) {
    DealerBust;
  } else if (playerTotal > dealerTotal) {
    PlayerWin;
  } else {
    DealerWin;
  };
};

type actions =
  | Deal
  | Hit
  | Stand
  | Split;

let runPlayerTurn = (game: game, action) =>
  switch (action) {
  | Deal => dealInitialCards(game)
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

    let gameResult =
      if (dealerGame.gameState == DealerBust) {
        dealerGame;
      } else {
        let winner = findWinner(dealerGame.board);
        {...dealerGame, gameState: winner};
      };
    {
      ...gameResult,
      playerTotal: game.playerTotal +. calculatePayout(gameResult),
    };
  };

let canHit = (game: game): bool =>
  switch (game.gameState) {
  | PlayerTurn => true
  | _ => false
  };

let canStand = (game: game): bool =>
  switch (game.gameState) {
  | PlayerTurn => true
  | _ => false
  };

let canDeal = (game: game): bool =>
  switch (game.gameState) {
  | PlayerTurn => false
  | _ => true
  };
