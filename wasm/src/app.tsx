import { useState, useEffect } from "react";

let sayHello: CallableFunction = () => {};

function App() {
  const [ready, setReady] = useState(false);

  const load = async () => {
    const wasmPath: string =
      "http://localhost:3000/hello-world/pkg/hello_world_bg.wasm";

    console.log("a");
    const response = await fetch(wasmPath);
    console.log("b");
    // const buffer = await response.arrayBuffer();
    // console.log("c");
    var importObject = {
      imports: { imported_func: (arg: any) => console.log(arg) },
    };
    const wasm = await WebAssembly.instantiateStreaming(response, importObject);
    console.log("d");
    sayHello = wasm.instance.exports.say_hello as CallableFunction;
    console.log("e");
    console.log(sayHello());
    setReady(true);
  };

  // executes one time
  useEffect(() => {
    load();
  }, []);

  return ready ? <div>{sayHello()}</div> : <div>Loading...</div>;
}

export default App;
