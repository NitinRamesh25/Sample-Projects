const { Given, When, Then } = require("@cucumber/cucumber");
const { Person } = require("../../src/shouty");
const assert = require("assert");

Given("Luccy is within {int} meters from Sean", (distance) => {
  this.luccy = new Person();
  this.sean = new Person();
  this.luccy.moveTo(distance);
});

When("Sean shouts {string}", (message) => {
  this.sean.shout(message);
  this.message = message;
});

Then("Luccy hears Sean's message", () => {
  assert(
    JSON.stringify(this.luccy.messagesHeard()) ===
      JSON.stringify([this.message])
  );
});
