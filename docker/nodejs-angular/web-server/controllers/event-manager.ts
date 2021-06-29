import express from "express";
import axios from "axios";

const events = ["Comicon", "Concert"];

const router = express.Router();

router.get("/", (_, response) => {
  response.send(events);
});

router.get("/auth", (_, response) => {
  axios
    .get("http://auth-service:8001/")
    .then((res) => {
      response.send(res.data);
    })
    .catch((error) => {
      console.log(error);
      response.send(false);
    });
});

export { router as EventController };
