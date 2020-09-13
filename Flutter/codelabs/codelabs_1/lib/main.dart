/*
  This app generates a infinitely scrollable list.
  Important stuff:
    1. english_words package can be used to generate random words
    2. Divider widget can be used to draw a line between two widgets in a list view
    3. ListTile widget used to represent a row with some text and leading and trailing
 */

import 'package:codelabs_1/random_words.dart';
import 'package:flutter/material.dart';

void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: "Welcome to flutter",
      debugShowCheckedModeBanner: false,
      home: Scaffold(
        appBar: AppBar(
          title: Center(
            child: Text("Welcome to Flutter"),
          ),
        ),
        body: Center(
          child: RandomWords(),
        ),
      ),
    );
  }
}
