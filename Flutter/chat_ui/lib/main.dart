import "package:flutter/material.dart";

import "package:chat_ui/screens/home_screen.dart";

void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: "Messenger",
      debugShowCheckedModeBanner: false,
      theme: _themeData(),
      home: HomeScreen(),
    );
  }

  ThemeData _themeData() {
    return ThemeData(
      primaryColor: Colors.red,
      accentColor: Color(0xffecfbfc),
    );
  }
}
