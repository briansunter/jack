// Generated by BUCKLESCRIPT VERSION 3.0.0, PLEASE EDIT WITH CARE
'use strict';

var Css = require("bs-css/lib/js/src/Css.js");
var Card = require("./Card.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Logic = require("./logic.js");
var Transition = require("./Transition.js");
var ReasonReact = require("reason-react/lib/js/src/ReasonReact.js");

((require('./main.css')));

var component = ReasonReact.statelessComponent("Hand");

var hand = Css.style(/* :: */[
      Css.display(Css.flexBox),
      /* :: */[
        Css.justifyContent(Css.center),
        /* :: */[
          Css.flex(1),
          /* [] */0
        ]
      ]
    ]);

var topStyle = Css.style(/* :: */[
      Css.display(Css.flexBox),
      /* [] */0
    ]);

var middleStyle = Css.style(/* :: */[
      Css.display(Css.flexBox),
      /* :: */[
        Css.justifyContent(Css.center),
        /* :: */[
          Css.fontSize(Css.px(100)),
          /* [] */0
        ]
      ]
    ]);

var bottomStyle = Css.style(/* :: */[
      Css.display(Css.flexBox),
      /* :: */[
        Css.justifyContent(Css.flexEnd),
        /* [] */0
      ]
    ]);

function actionButton(disabled) {
  return Css.style(/* :: */[
              Css.background(disabled ? Css.darkgray : Css.white),
              /* :: */[
                Css.color(Css.black),
                /* :: */[
                  Css.border(Css.px(1), Css.solid, Css.black),
                  /* :: */[
                    Css.borderRadius(Css.px(3)),
                    /* [] */0
                  ]
                ]
              ]
            ]);
}

var Styles = /* module */[
  /* hand */hand,
  /* topStyle */topStyle,
  /* middleStyle */middleStyle,
  /* bottomStyle */bottomStyle,
  /* actionButton */actionButton
];

function make(hand$1, $staropt$star, _) {
  var hideSecondCard = $staropt$star ? $staropt$star[0] : false;
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function () {
              return ReasonReact.element(/* None */0, /* None */0, Transition.TransitionGroup[/* make */0](/* Some */[hand], /* None */0, /* array */[$$Array.mapi((function (i, h) {
                                      return ReasonReact.element(/* Some */[Logic.suitToString(h[/* suit */0]) + Logic.styleToString(h[/* style */1])], /* None */0, Transition.Transition[/* make */2](true, 20, /* None */0, (function (s) {
                                                        var flipped = s !== 0 ? true : false;
                                                        var shouldFlip = hideSecondCard && i === 1 ? false : flipped;
                                                        return ReasonReact.element(/* Some */[Logic.suitToString(h[/* suit */0]) + Logic.styleToString(h[/* style */1])], /* None */0, Card.make(h[/* suit */0], h[/* style */1], /* Some */[shouldFlip], /* None */0, /* array */[]));
                                                      })));
                                    }), hand$1)]));
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

exports.component = component;
exports.Styles = Styles;
exports.make = make;
/*  Not a pure module */
