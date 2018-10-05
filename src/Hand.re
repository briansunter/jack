[%raw {|require('./main.css')|}];

let component = ReasonReact.statelessComponent("Hand");

module Styles = {
  open Css;

  let hand = style([display(flexBox), justifyContent(center), flex(1)]);

  let topStyle = style([display(flexBox)]);

  let middleStyle =
    style([display(flexBox), justifyContent(center), fontSize(px(100))]);

  let bottomStyle = style([display(flexBox), justifyContent(flexEnd)]);

  let actionButton = disabled =>
    style([
      background(disabled ? darkgray : white),
      color(black),
      border(px(1), solid, black),
      borderRadius(px(3)),
    ]);
};

let make = (~hand, ~hideSecondCard=false, _children) => {
  ...component,
  render: _self =>
    <Transition.TransitionGroup className=Styles.hand>
      {
        ReasonReact.array(
          Array.mapi(
            (i, h: Logic.card) =>
              <Transition.Transition
                timeout=20
                in_=true
                key={
                  Logic.suitToString(h.suit) ++ Logic.styleToString(h.style)
                }>
                ...{
                     s => {
                       let flipped =
                         switch (s) {
                         | Transition.Transition.Entering => false
                         | _ => true
                         };

                       let shouldFlip =
                         if (hideSecondCard) {
                           if (i == 1) {
                             false;
                           } else {
                             flipped;
                           };
                         } else {
                           flipped;
                         };

                       <Card
                         suit={h.suit}
                         key={
                           Logic.suitToString(h.suit)
                           ++ Logic.styleToString(h.style)
                         }
                         cardStyle={h.style}
                         flipped=shouldFlip
                       />;
                     }
                   }
              </Transition.Transition>,
            hand,
          ),
        )
      }
    </Transition.TransitionGroup>,
};
/*{ReasonReact.string(Transition.Transition.stringOfState(s))} */
