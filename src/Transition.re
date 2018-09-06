[@bs.module "react-transition-group"]
external cssTransition : ReasonReact.reactClass = "CSSTransition";

[@bs.module "react-transition-group"]
external transitionGroup : ReasonReact.reactClass = "TransitionGroup";

[@bs.module "react-transition-group"]
external transitionClass: ReasonReact.reactClass = "Transition";

module CSSTransition = {
  let make = (~show: bool, ~timeout: int, ~classNames: string, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=cssTransition,
      ~props={"in": show, "timeout": timeout, "classNames": classNames},
      children,
    );
};

module TransitionGroup = {
  let make = (~className=?,~component=?,children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=transitionGroup,
      ~props={"component": "div", "className": className},
      children,
    );
};

module Transition = {

type state =
  | Entering
  | Entered
  | Exiting
  | Exited
  | NotTransitioning;

let stateOfString = (str) =>
  switch str {
  | "entering" => Entering
  | "entered" => Entered
  | "exiting" => Exiting
  | "exited" => Exited
  | _ => NotTransitioning
  };

  let stringOfState = (str) =>
  switch str {
  | Entering => "entering" 
  | Entered => "entered" 
  | Exiting => "exiting" 
  | Exited => "exited" 
  | _ => "Not"
  };

let make = (~in_: bool, ~timeout: int, ~className=?, children: state => ReasonReact.reactElement) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=transitionClass,
    ~props={"in": Js.Boolean.to_js_boolean(in_), "timeout": timeout, "className":className},
    (strState, _childProps) => children(stateOfString(strState))
  );
};