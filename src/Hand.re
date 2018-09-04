let component = ReasonReact.statelessComponent("Hand");

module Styles = {
  open Css;

  let hand =
    style([
      display(flexBox),
      justifyContent(center),
      backgroundColor(darkolivegreen),
      margin(px(10)),
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
    <div className=Styles.hand>
      {
        ReasonReact.array(
          Array.map(
            (h: Logic.card) => <Card suit={h.suit} cardStyle={h.style} />,
            hand,
          ),
        )
      }
    </div>,
};
