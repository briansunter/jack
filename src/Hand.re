[%raw {|require('./main.css')|}];

let component = ReasonReact.statelessComponent("Hand");

module Styles = {
  open Css;

  let hand =
    style([
      display(flexBox),
      justifyContent(center),
      flex(1)
    ]);

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

let make = (~hand, _children) => {
  ...component,
  render: _self =>
<Transition.TransitionGroup className={Styles.hand}>
        {ReasonReact.array(
          Array.mapi(
            (i,h: Logic.card) => {
        <Transition.Transition timeout=30 in_=true key={string_of_int(i)}>
        ...((s) => { 
          let flipped = switch(s) {
          | Transition.Transition.Entering => false
          | _ => true
          };
              <Card suit={h.suit} key={string_of_int(i)} cardStyle={h.style} flipped=flipped />
        }
        )
        </Transition.Transition>
             }, 
            hand,
          ),
        )}
        </Transition.TransitionGroup>
};
/*{ReasonReact.string(Transition.Transition.stringOfState(s))} */