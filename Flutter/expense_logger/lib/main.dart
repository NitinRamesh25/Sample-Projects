import "package:flutter/material.dart";

import "./transaction.dart";

void main() => runApp(ExpenseLoggerApp());

AppBar appBar() {
  return AppBar(
    title: Container(
      width: double.infinity,
      child: Text(
        "Expense Logger",
        textAlign: TextAlign.center,
      ),
    ),
  );
}

class ExpenseLoggerApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: MainPage(),
    );
  }
}

class MainPage extends StatelessWidget {
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: appBar(),
      body: Center(
        child: Transaction(),
      ),
    );
  }
}
