import 'dart:developer';

import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:state_management/block/counter_block.dart';
import 'package:state_management/screens/home_screen.dart';

void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    // If multiple blocs are needed then use MultiProvider and mention all providers in a list
    return ChangeNotifierProvider<CounterBlock>(
      create: (_) => CounterBlock(),
      child: MaterialApp(
        title: "state management <>app",
        home: HomeScreen(),
      ),
    );
  }
}
