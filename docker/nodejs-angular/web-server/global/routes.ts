import express from "express";
import { EventController } from "@controllers/event-manager";

export const router = express.Router();

router.use("/event", EventController);
