import express from "express";
import http from "http";

const events = ["Comicon", "Concert"];

const router = express.Router();

router.get("/", (_, response) => {
  response.send(events);
});

router.get("/auth", (_, response) => {
  http.get("http://localhost:8001/", (res) => {
    res.on("data", (data) => {
      if (data) {
        response.send("authenticated");
      } else {
        response.send("not-authenticated");
      }
    });
  });
});

export { router as EventController };
