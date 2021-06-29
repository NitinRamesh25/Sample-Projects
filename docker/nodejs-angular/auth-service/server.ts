import express from "express";
import cors from "cors";
import bodyParser from "body-parser";

const app = express();

app.use(cors());
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

app.get("/", (req, res) => {
  res.send(true);
});

app.listen(8001, "0.0.0.0", () => {
  console.log(`auth-service listening on port: ${8001}`);
});
