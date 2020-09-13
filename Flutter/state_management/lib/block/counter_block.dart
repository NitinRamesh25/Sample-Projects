import 'package:flutter/material.dart';

class CounterBlock extends ChangeNotifier {
  int _counter = 0;
  
  int get counter => _counter;
  
  set counter(int val) {
    _counter = val;
    notifyListeners();
  }

  increment() {
    // this would call the setter above
    counter = counter + 1;
  }
}