import React from "react";
import ReactDOM from "react-dom";
import { get_age, say_hello } from "./hello-world/pkg/hello_world_bg";

function App() {
  return (
    <div>
      {say_hello()} {get_age()}
    </div>
  );
}

ReactDOM.render(<App />, document.getElementById("root"));
