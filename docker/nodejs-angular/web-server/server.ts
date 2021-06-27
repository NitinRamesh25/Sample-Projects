require("module-alias/register");

import express from "express";
import cors from "cors";
import bodyParser from "body-parser";
import { router } from "@global/routes";

const app = express();
app.use(cors());
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

app.use(router);

const port = 8000;
const hostname = "0.0.0.0";
app.listen(port, hostname, () => {
  console.log(`Server listening at port: ${port} and host: ${hostname}`);
});
