import 'package:flutter/material.dart';

class Answer extends StatelessWidget {
  final String text;
  final Color backColor;
  final Color textColor;
  final Function onPressedFunction;

  Answer(
      {String text = "Sample",
      Color backColor = Colors.black,
      Color textColor = Colors.white,
      Function onPressedFunction})
      : text = text,
        backColor = backColor,
        textColor = textColor,
        onPressedFunction = onPressedFunction;

  @override
  Widget build(BuildContext context) {
    return Container(
      width: double.infinity,
      child: RaisedButton(
        color: backColor,
        onPressed: onPressedFunction,
        child: Text(
          text,
          style: TextStyle(color: textColor),
        ),
      ),
    );
  }
}
