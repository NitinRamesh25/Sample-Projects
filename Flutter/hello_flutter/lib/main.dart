import 'package:flutter/material.dart';

import './question.dart';

void main() => runApp(MyApp());

class MyApp extends StatefulWidget {
  @override
  State<StatefulWidget> createState() {
    return _MyAppState();
  }
}

class _MyAppState extends State<MyApp> {
  int _questionIndex = 0;

  List questions = [
    "What is your favourite color?",
    "What is your favourite animal?",
  ];

  void _answerQuestion() {
    setState(() {
      _questionIndex = 1;
    });
  }

  @override
  Widget build(BuildContext context) {
    // Create the core widget to display on loading the application.
    // home arg takes widget and we create a Text widget with a content.

    Scaffold mainWidget = Scaffold(
      appBar: AppBar(
        title: Text("My First App"),
      ),
      body: Column(
        children: [
          Question(questions[_questionIndex]),
          RaisedButton(
            child: Text("Answer 1"),
            onPressed: _answerQuestion,
          ),
          RaisedButton(
            child: Text("Answer 2"),
            onPressed: _answerQuestion,
          ),
          RaisedButton(
            child: Text("Answer 3"),
            onPressed: _answerQuestion,
          ),
        ],
      ),
    );

    return MaterialApp(
      home: mainWidget,
      theme: ThemeData(primarySwatch: Colors.green),
    );
  }
}
