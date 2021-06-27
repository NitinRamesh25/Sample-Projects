import express from "express";

const events = ["Comicon", "Concert"];

const router = express.Router();

router.get("/", (_, response) => {
  response.send(events);
});

export { router as EventController };
