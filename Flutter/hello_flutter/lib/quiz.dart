import 'package:flutter/material.dart';
import './question.dart';
import './answer.dart';

class Quiz extends StatelessWidget {
  final String questionText;
  final List<Map<String, String>> answersAndScores;
  final Function answerOnPressedFunction;

  Quiz({
    @required this.questionText,
    @required this.answersAndScores,
    @required this.answerOnPressedFunction,
  });

  @override
  Widget build(BuildContext context) {
    return Column(
      children: <Widget>[
        Question(
          questionText: this.questionText,
        ),

        // ... is a spread operator, takes each individual element of a list
        // map function used below lets us iterate over a list
        ...(this.answersAndScores).map((answerScoreMap) {
          return Answer(
            text: answerScoreMap["text"],
            score: int.parse(answerScoreMap["score"]),
            textColor: Colors.white,
            backColor: Colors.blue,
            onPressedFunction: answerOnPressedFunction,
          );
        }).toList(),
      ],
    );
  }
}
