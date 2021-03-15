import React, { Component } from "react";
import { say_hello } from "./hello-world/pkg/hello_world";

class App extends Component {
  render() {
    return <div>{say_hello()}</div>;
  }
}
export default App;
