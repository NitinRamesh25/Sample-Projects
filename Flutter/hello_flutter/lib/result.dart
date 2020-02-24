import 'package:flutter/material.dart';

class Result extends StatelessWidget {
  final int resultScore;
  final Function restartQuiz;

  Result({
    this.resultScore = 0,
    @required this.restartQuiz,
  });

  @override
  Widget build(BuildContext context) {
    return Column(
      children: [
        Text(
          "You did it! Your score Is ${this.resultScore}",
          style: TextStyle(
            fontSize: 30,
            fontWeight: FontWeight.bold,
            color: Colors.green,
          ),
          textAlign: TextAlign.center,
        ),
        FlatButton(
          onPressed: this.restartQuiz,
          child: Text("Restart"),
          textColor: Colors.blue,
        )
      ],
    );
  }
}
