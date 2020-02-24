import 'package:flutter/material.dart';

class Answer extends StatelessWidget {
  final String text;
  final int score;
  final Color backColor;
  final Color textColor;
  final Function onPressedFunction;

  Answer(
      {this.text = "Sample",
      this.score = 0,
      this.backColor = Colors.black,
      this.textColor = Colors.white,
      @required this.onPressedFunction});

  @override
  Widget build(BuildContext context) {
    return Container(
      width: 200,
      child: RaisedButton(
        color: backColor,
        onPressed: () => onPressedFunction(this.score),
        child: Text(
          text,
          style: TextStyle(color: textColor),
        ),
      ),
    );
  }
}
