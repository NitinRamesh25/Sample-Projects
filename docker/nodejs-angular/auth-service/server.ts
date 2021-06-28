import express from "express";

const app = express();

app.get("/", (req, res) => {
    res.send(true);
})

app.listen(8001, "0.0.0.0", () => {
    console.log(`auth-service listening on port: ${8001}`);
})