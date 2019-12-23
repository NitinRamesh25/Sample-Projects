import 'package:flutter/material.dart';

import './question.dart';
import './answer.dart';

void main() => runApp(MyApp());

class MyApp extends StatefulWidget {
  @override
  State<StatefulWidget> createState() {
    return _MyAppState();
  }
}

class _MyAppState extends State<MyApp> {
  int _questionIndex = 0;

  final List questionsAnswers = [
    {
      "questionText": "What is your favourite color?",
      "answers": ["Red", "Green", "Blue"],
    },
    {
      "questionText": "What is your favourite animal?",
      "answers": ["Cat", "Dog", "Horse"],
    },
  ];

  void _answerQuestion() {
    setState(() {
      _questionIndex = ++_questionIndex % questionsAnswers.length;
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
          Question(questionsAnswers[_questionIndex]["questionText"]),

          // ... is a spread operator, takes each individual element of a list
          // map function used below lets us iterate over a list
          ...(questionsAnswers[_questionIndex]["answers"] as List<String>)
              .map((answerText) {
            return Answer(
              text: answerText,
              textColor: Colors.white,
              backColor: Colors.blue,
              onPressedFunction: _answerQuestion,
            );
          }).toList(),
        ],
      ),
    );

    return MaterialApp(
      home: mainWidget,
      theme: ThemeData(primarySwatch: Colors.blue),
    );
  }
}
