import 'package:flutter/material.dart';

import './quiz.dart';
import './result.dart';

void main() => runApp(MyApp());

class MyApp extends StatefulWidget {
  @override
  State<StatefulWidget> createState() {
    return _MyAppState();
  }
}

class _MyAppState extends State<MyApp> {
  int _questionIndex = 0;
  int _totalScore = 0;

  final List _questionsAnswers = [
    {
      "questionText": "What is your favourite color?",
      "answers": [
        {"text": "Red", "score": "10"},
        {"text": "Green", "score": "5"},
        {"text": "Blue", "score": "2"},
      ],
    },
    {
      "questionText": "What is your favourite animal?",
      "answers": [
        {"text": "Cat", "score": "10"},
        {"text": "Dog", "score": "5"},
        {"text": "Horse", "score": "2"},
      ],
    },
  ];

  void _answerQuestion(int score) {
    setState(() {
      ++_questionIndex;
      _totalScore += score;
    });
  }

  void _restartQuiz() {
    setState(() {
      _questionIndex = 0;
      _totalScore = 0;
    });
  }

  @override
  Widget build(BuildContext context) {
    // Create the core widget to display on loading the application.
    // home arg takes widget and we create a Text widget with a content.

    Scaffold mainWidget = Scaffold(
      appBar: AppBar(
        title: Text("My First Flutter App"),
      ),
      body: (_questionIndex < _questionsAnswers.length)
          ? Quiz(
              questionText: _questionsAnswers[_questionIndex]["questionText"],
              answersAndScores: _questionsAnswers[_questionIndex]["answers"],
              answerOnPressedFunction: _answerQuestion,
            )
          : Result(
              resultScore: _totalScore,
              restartQuiz: _restartQuiz,
            ),
    );

    return MaterialApp(
      home: mainWidget,
      theme: ThemeData(primarySwatch: Colors.blue),
    );
  }
}
