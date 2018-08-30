type suit =
  | Hearts
  | Diamonds
  | Spades
  | Clubs;

type style =
  | Ace
  | King
  | Queen
  | Jack
  | Simple(int);

type card = {
  suit,
  style,
};

type hand = list(card);

let faceCardValue = 10;

let cardValue = ({style}) =>
  switch (style) {
  | Simple(value) => value
  | _ => faceCardValue;
  };

let aceHighValue = 11;
let aceLowValue = 1;
let maxValue = 21;

let addAces = (sumSoFar,aces) => {
  Belt.List.reduce(aces,sumSoFar, (a,_) => {
    if (a + aceHighValue <= maxValue) {
      a + aceHighValue;
    } else {
      a + aceLowValue;
    }
  });
};

let calculateHand = hand => {
  let aces: hand = List.filter(({style}) => style == Ace, hand);
  let noAceHand: hand = List.filter(({style}) => style != Ace, hand);
  let sumWithoutAces:int = noAceHand |> List.map(cardValue) |. Belt.List.reduce(0, (+));
  addAces(sumWithoutAces,aces);
};

let testHand:hand = [{suit: Hearts, style: Jack}, {suit: Hearts, style: Simple(1)}];

let rec range = (start: int, end_: int) =>
  if (start >= end_) {
    [];
  } else {
    [start, ...range(start + 1, end_)];
  };

type deck = list(card);

let suits = [Hearts,Clubs,Diamonds,Spades];
let simpleCards:list(style) = List.map(i => Simple(i),range(2,10));
let styles:list(style) = List.append([Ace,King,Queen,Jack],simpleCards);

let defaultDeck:deck = Belt.List.reduce(suits, [], (a,suit) => List.append(a, Belt.List.map(styles, style => {suit,style})));

type board = {
  playerHand: hand,
  dealerHand: hand,
};

let emptyBoard = {playerHand: [], dealerHand:[]};

type gameState = NewGame | PlayerTurn | PlayerBust | PlayerWin | DealerWin;

type game = {
  board,
  deck,
  gameState
};

let dealInitialcards = game => {
  let [playerCard1, playerCard2, dealerCard, ...restDeck] = game.deck;
  {...game, 
    deck:restDeck,
    gameState: PlayerTurn,
      board:{
    playerHand:[playerCard1,playerCard2],
    dealerHand: [dealerCard]}};
};

type players = Player | Dealer;

let findWinner = board => {
  let playerTotal = calculateHand(board.playerHand);
  let dealerTotal = calculateHand(board.dealerHand);
  if (playerTotal > dealerTotal) {
    if (playerTotal < maxValue) {
      Player
    } else {
      Dealer
    }
  } else {
    if (dealerTotal < maxValue) {
      Dealer
    } else {
      Player
    }
  };
};

let dealerHitValue = 17;

let dealerCanPlay = hand => (calculateHand(hand) <= dealerHitValue);

type actions = Hit | Stand | Split;

let runPlayerTurn = (game:game, action) => {
    switch(action) {
    | Hit => {
      let [newCard, ...restDeck] = game.deck;
      let newPlayerHand =[newCard, ...game.board.playerHand]; 
      if (calculateHand(newPlayerHand) <= maxValue) {
        {...game, deck:restDeck, gameState: PlayerTurn, board:{...game.board, playerHand:newPlayerHand}}
      } else {
        {...game, deck:restDeck, gameState: PlayerBust, board:{...game.board, playerHand:newPlayerHand}}
      };
      }
      | _ => game;
    }
    };